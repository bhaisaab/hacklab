package main

import "fmt"

var coins map[int64]int64

func max(a, b int64) int64 {
	if a > b {
		return a
	}
	return b
}

func dp(n int64) int64 {
	if n < 2 {
		return n
	}
	value, ok := coins[n]
	if ok {
		return value
	}
	value = max(n, dp(n/2)+dp(n/3)+dp(n/4))
	coins[n] = value
	return value
}

func main() {
	coins = make(map[int64]int64)
	var n int64
	for {
		_, err := fmt.Scanf("%d", &n)
		if err != nil {
			break
		}
		fmt.Println(dp(n))
	}
}
