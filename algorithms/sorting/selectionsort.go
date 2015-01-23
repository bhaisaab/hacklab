package main

import "fmt"

func selectionSort(a []int) []int {
	for i := 0; i < len(a); i++ {
		min := a[i]
		for j := i; j < len(a); j++ {
			if a[j] < min {
				min = a[j]
				a[i], a[j] = a[j], a[i]
			}
		}
	}
	return a
}

func main() {
	a := []int{908, 1321, 1, 123, 463, 9834, 1301, 198512, 19, 543, 64}
	fmt.Println("input =", a)
	fmt.Println("output (mergesort) =", selectionSort(a))
}
