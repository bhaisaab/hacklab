package main

import "fmt"

func count(n int64) int64 {
	var result, dividor int64
	result = 0
	dividor = 5
	for n/dividor > 0 {
		result += n / dividor
		dividor *= 5
	}
	return result
}

func main() {
	var t int
	var n int64
	fmt.Scanf("%d", &t)
	for t > 0 {
		fmt.Scanf("%d", &n)
		fmt.Println(count(n))
		t--
	}
}
