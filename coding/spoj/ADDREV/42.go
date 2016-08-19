package main

import "fmt"

func reverse(n int64) int64 {
	var result int64 = 0
	for n > 0 {
		result = result*10 + n%10
		n = n / 10
	}
	return result
}

func main() {
	var n, a, b int64
	fmt.Scanf("%d", &n)
	for n > 0 {
		fmt.Scanf("%d %d", &a, &b)
		fmt.Println(reverse(reverse(a) + reverse(b)))
		n--
	}
}
