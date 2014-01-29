package server

import (
	"bytes"
	"encoding/json"
	//"errors"
	//"fmt"
	"github.com/goraft/raft"
	"github.com/gorilla/mux"
	"io/ioutil"
	"net/http"
	"path/filepath"
	"stripe-ctf.com/sqlcluster/command"
	"stripe-ctf.com/sqlcluster/log"
	"stripe-ctf.com/sqlcluster/sql"
	"stripe-ctf.com/sqlcluster/transport"
	"stripe-ctf.com/sqlcluster/util"
	//"os"
	"time"
)

type Server struct {
	name       string
	path       string
	listen     string
	router     *mux.Router
	raftServer raft.Server
	httpServer *http.Server
	sql        *sql.SQL
	client     *transport.Client
}

// Creates a new server.
func New(path, listen string) (*Server, error) {
	sqlPath := filepath.Join(path, "storage.sql")
	util.EnsureAbsent(sqlPath)

	s := &Server{
		name:    listen,
		path:    path,
		listen:  listen,
		sql:     sql.NewSQL(sqlPath),
		router:  mux.NewRouter(),
		client:  transport.NewClient(),
	}

	return s, nil
}

// Returns the connection string.
func (s *Server) connectionString() string {
	cs, _ := transport.Encode(s.listen)
	log.Println("ConnectionString: " + cs)
	return cs
}

// Starts the server.
func (s *Server) ListenAndServe(primary string) error {
	var err error = nil

	// Initialize and start Raft server.
	transporter := raft.NewHTTPTransporter("/raft")
	transporter.Transport.Dial = transport.UnixDialer
	s.raftServer, err = raft.NewServer(s.name, s.path, transporter, nil, s.sql, "")
	if err != nil {
		log.Fatal(err)
	}
	s.raftServer.SetElectionTimeout(750 * time.Millisecond)
	transporter.Install(s.raftServer, s)
	s.raftServer.Start()

	// Initialize and start HTTP server.
	s.httpServer = &http.Server{
		Handler: s.router,
	}

	s.router.HandleFunc("/sql", s.sqlHandler).Methods("POST")
	s.router.HandleFunc("/join", s.joinHandler).Methods("POST")

	if primary == "" {
		if s.raftServer.IsLogEmpty() {
			_, err := s.raftServer.Do(&raft.DefaultJoinCommand{
			Name:             s.raftServer.Name(),
			ConnectionString: s.connectionString(),
			})
			if err != nil {
				log.Fatal(err)
			}
		}

	} else {

		if !s.raftServer.IsLogEmpty() {
			log.Fatal("Cannot join with an existing log")
		}
		//	   		namePath, _ := filepath.Abs()
	   	if err := s.Join(primary); err != nil {
			log.Fatal(err)
		}
		log.Println("Joined leader:", s.raftServer.Leader())
	}

	// Start Unix transport
	l, err := transport.Listen(s.listen)
	if err != nil {
		log.Fatal(err)
	}

	return s.httpServer.Serve(l)
}

// This is a hack around Gorilla mux not providing the correct net/http
// HandleFunc() interface.
func (s *Server) HandleFunc(pattern string, handler func(http.ResponseWriter, *http.Request)) {
	s.router.HandleFunc(pattern, handler)
}

// Client operations

// Join an existing cluster
func (s *Server) Join(primary string) error {

	command := &raft.DefaultJoinCommand{
		Name:             s.raftServer.Name(),
		ConnectionString: s.connectionString(),
	}

	var b bytes.Buffer
	json.NewEncoder(&b).Encode(command)

	cs, err := transport.Encode(primary)
	if err != nil {
		return err
	}

	log.Printf("Server %v with cs=%v is trying to join %v on %s/join", s.raftServer.Name(), s.connectionString(), primary, cs)

	for {
		_, err := s.client.SafePost(cs, "/join", &b)
		if err != nil {
			log.Printf("Unable to join cluster: %s", err)
			time.Sleep(1 * time.Second)
			continue
		}
		return nil
	}
}

// Server handlers
func (s *Server) joinHandler(w http.ResponseWriter, req *http.Request) {
	command := &raft.DefaultJoinCommand{}

	if err := json.NewDecoder(req.Body).Decode(&command); err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	log.Printf("Handling join request: %#v", command)

	if _, err := s.raftServer.Do(command); err != nil {
		log.Printf("Server was unable to join %v with err=%v", command, err)
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
}

// This is the only user-facing function, and accordingly the body is
// a raw string rather than JSON.
func (s *Server) sqlHandler(w http.ResponseWriter, req *http.Request) {

	query, err := ioutil.ReadAll(req.Body)
	if err != nil {
		log.Printf("Couldn't read body: %s", err)
		http.Error(w, err.Error(), http.StatusBadRequest)
		return
	}
	log.Printf("[%s]Received query: %#v", string(s.raftServer.State()),string(query))

	if (s.raftServer.State() != "leader") {
		if (s.raftServer.Leader() == "") {
			w.WriteHeader(http.StatusBadRequest)
			return
		}
		leader, _ := transport.Encode(s.raftServer.Leader())
		log.Printf("Relaying query to leader: %v", s.raftServer.Leader())
       	relayResp, err := s.client.SafePost(leader, "/sql", bytes.NewReader(query))
       	if err != nil {
            http.Error(w, "Only the primary can service queries, relaying failed", http.StatusBadRequest)
            return
       	}
       //buf := new(bytes.Buffer)
       //buf.ReadFrom(relayResp)
       w.Write( relayResp.(*bytes.Buffer).Bytes() )
       return
	}

	// Execute the command against the Raft server.
	resp, err := s.raftServer.Do(command.NewWriteCommand(string(query)))
	if err != nil {
		log.Printf("Current leader: %#v resp=%v err=%v", string(s.raftServer.Leader()), resp, err)
		http.Error(w, err.Error(), http.StatusBadRequest)
		return
	}

	if formatted, ok := resp.(string); ok {
		log.Printf("Returning response to %#v: %#v", string(query), resp)
		w.Write([]byte(formatted))
	} else {
		w.WriteHeader(http.StatusBadRequest)
	}
}