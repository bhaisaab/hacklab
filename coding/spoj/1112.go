package main

import "fmt"

func satisfy(a, b int) bool {
	return a != b && a != (b+2)
}

func main() {
	var t, a, b int
	fmt.Scanf("%d", &t)
	for ; t > 0; t-- {
		fmt.Scanf("%d %d", &a, &b)
		if (a%2 == 0 && b%2 != 0) || (a%2 != 0 && b%2 == 0) || satisfy(a, b) {
			fmt.Println("No Number")
		} else {
			if a%2 == 0 {
				fmt.Println(a + b)
			} else {
				fmt.Println(a + b - 1)
			}
		}
	}
}
