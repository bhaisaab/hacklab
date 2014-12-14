package main

import "log"

var done = make(chan bool)
var msgs = make(chan int)

func producer() {
	for i := 0; i < 20; i++ {
		log.Printf("Producer:: %d", i)
		msgs <- i
	}
	done <- true
	log.Println("Producer is done")
}

func consumer() {
	for x := range msgs {
		log.Printf("Consumer:: %d", x)
	}
}

func main() {
	go producer()
	go consumer()
	<-done
}
