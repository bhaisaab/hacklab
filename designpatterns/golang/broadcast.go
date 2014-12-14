package main

import (
	"fmt"
	"time"
)

func minion(i int, block, done chan struct{}) {
	fmt.Printf("Minion %d reporting...\n", i)
	<-block
	fmt.Println(i, "done")
	done <- struct{}{}
}

func main() {
	block, done := make(chan struct{}), make(chan struct{})
	for i := 0; i < 10; i++ {
		go minion(i, block, done)
	}
	time.Sleep(5 * time.Millisecond)
	fmt.Println("Broadcasting done")
	close(block)
	for i := 0; i < 10; i++ {
		<-done
	}
}
