package main

import "fmt"

func main() {
	var t, k int64
	fmt.Scanf("%d", &t)
	for ; t > 0; t-- {
		fmt.Scanf("%d", &k)
		val := 192 + (k-1)*250
		fmt.Println(val)
	}
}
