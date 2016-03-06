package main

import (
	"log"
	"os"
	"runtime"
)

func main() {
	log.Printf("Mapping OS threads to 1 CPUs, total cpus=%d", runtime.NumCPU())
	runtime.GOMAXPROCS(1)

	brokerUrl := "amqp://guest:guest@127.0.0.1:5672/"
	ch := make(chan bool)
	maxConsumers := 2 * runtime.NumCPU()
	for i := 0; i < maxConsumers; i++ {
		go consume(brokerUrl, ch)
	}

	log.Printf(" [*] Waiting for logs. To exit press CTRL+C")
	<-ch
	log.Printf("ch")
	os.Exit(0)
}
