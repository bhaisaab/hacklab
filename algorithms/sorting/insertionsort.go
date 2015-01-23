package main

import "fmt"

func insertionsort(a []int) []int {
	for i := 1; i < len(a); i++ {
		for j := i - 1; j >= 0; j-- {
			if a[j+1] > a[j] {
				break
			}
			a[j+1], a[j] = a[j], a[j+1]
		}
	}
	return a
}

func main() {
	a := []int{908, 1321, 1, 123, 463, 9834, 1301, 198512, 19, 543, 64}
	fmt.Println("input =", a)
	fmt.Println("output (mergesort) =", insertionsort(a))
}
