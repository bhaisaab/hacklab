package command

import (
	"github.com/goraft/raft"
	"stripe-ctf.com/sqlcluster/sql"
	"errors"
	"fmt"
	"stripe-ctf.com/sqlcluster/util"
)

// This command writes a value to a key.
type WriteCommand struct {
	Query   string `json:"query"` // Query
}

// Creates a new write command.
func NewWriteCommand(query string) *WriteCommand {
	return &WriteCommand{
		Query:   query,
	}
}

// The name of the command in the log.
func (c *WriteCommand) CommandName() string {
	return "sqlQuery"
}

// Writes a value to a key.
func (c *WriteCommand) Apply(server raft.Server) (interface{}, error) {
	sqlCtx := server.Context().(*sql.SQL)
	output, err := sqlCtx.Execute(c.Query)

	if err != nil {
		var msg string
		if output != nil && len(output.Stderr) > 0 {
			template := `Error executing %#v (%s)

SQLite error: %s`
			msg = fmt.Sprintf(template, c.Query, err.Error(), util.FmtOutput(output.Stderr))
		} else {
			msg = err.Error()
		}

		return nil, errors.New(msg)
	}

	formatted := fmt.Sprintf("SequenceNumber: %d\n%s",
		output.SequenceNumber, output.Stdout)
	return formatted, err
}