package main

import (
	"fmt"
	"math/rand"
	"sync"
)

type randomNum chan float64

func generateRandomNumber(n int) randomNum {
	var wg sync.WaitGroup
	numChan := make(randomNum)

	for i := 0; i < n; i++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			numChan <- rand.Float64()
		}()
	}

	go func() {
		wg.Wait()
		close(numChan)
	}()

	return numChan
}

func main() {
	for x := range generateRandomNumber(100) {
		fmt.Println(x)
	}
}
