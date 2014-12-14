package main

import "fmt"

func intSeq() func() int {
	i := 0
	return func() int {
		i += 1
		return i
	}
}

func main() {
	gen := intSeq()
	fmt.Println(gen())
	fmt.Println(gen())
	fmt.Println(gen())
	fmt.Println(gen())

	gen = intSeq()
	fmt.Println(gen())
	fmt.Println(gen())
	fmt.Println(gen())
}
