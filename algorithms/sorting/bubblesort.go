package main

import "fmt"

func bubbleSort(a []int) []int {
	for i := 0; i < len(a); i++ {
		for j := 0; j < len(a); j++ {
			if a[j] > a[i] {
				a[i], a[j] = a[j], a[i]
			}
		}
	}
	return a
}

func main() {
	a := []int{908, 1321, 1, 123, 463, 9834, 1301, 198512, 19, 543, 64}
	fmt.Println("input =", a)
	fmt.Println("output (mergesort) =", bubbleSort(a))
}
