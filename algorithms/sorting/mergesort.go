package main

import "fmt"

func mergesort(input []int) []int {
	l := len(input)
	if l <= 2 {
		if l <= 1 {
			return input
		}
		if input[0] > input[1] {
			input[1], input[0] = input[0], input[1]
		}
		return input
	}
	a := mergesort(input[:l/2])
	b := mergesort(input[l/2:])
	output := []int{}
	i, j := 0, 0
	for i < len(a) && j < len(b) {
		if a[i] < b[j] {
			output = append(output, a[i])
			i++
		} else {
			output = append(output, b[j])
			j++
		}
	}
	for ; i < len(a); i++ {
		output = append(output, a[i])
	}
	for ; j < len(b); j++ {
		output = append(output, b[j])
	}
	return output
}

func main() {
	a := []int{908, 1321, 1, 123, 463, 9834, 1301, 198512, 19, 543, 64}
	fmt.Println("input =", a)
	fmt.Println("output (mergesort) =", mergesort(a))
}
