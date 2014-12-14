package main

import "fmt"

func integers() chan int {
	yield := make(chan int)
	count := 0
	go func() {
		for {
			count += 1
			yield <- count
		}
	}()
	return yield
}

var generator = integers()

func generateInteger() int {
	return <-generator
}

func main() {
	fmt.Println(generateInteger())
	fmt.Println(generateInteger())
	fmt.Println(generateInteger())
	fmt.Println(generateInteger())
	fmt.Println(generateInteger())
	fmt.Println(generateInteger())
	fmt.Println(generateInteger())
	fmt.Println(generateInteger())
}
