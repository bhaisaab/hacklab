package main

import "fmt"

type empty interface{}
type semaphore chan empty

var sem = make(semaphore, 10)

func (s semaphore) Acquire(n int) {
	for i := 0; i < n; i++ {
		sem <- new(empty)
	}
}

func (s semaphore) Release(n int) {
	for i := 0; i < n; i++ {
		<-s
	}
}

func (s semaphore) Lock() {
	s.Acquire(1)
}

func (s semaphore) Unlock() {
	s.Release(1)
}

func main() {
	fmt.Println("Semaphore locked")
	sem.Lock()
	defer func() {
		sem.Unlock()
		fmt.Println("Semaphore unlocked")
	}()
}
