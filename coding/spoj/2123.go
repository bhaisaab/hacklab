package main

import "fmt"

func main() {
	var N int
	for {
		fmt.Scanf("%d", &N)
		if N == -1 {
			break
		}
		total := 0
		candies := make([]int, N)
		for i := 0; i < N; i++ {
			fmt.Scanf("%d", &candies[i])
			total += candies[i]
		}
		if total%N == 0 {
			steps := 0
			mean := total / N
			for _, val := range candies {
				if val > mean {
					steps += (val - mean)
				}
			}
			fmt.Println(steps)
		} else {
			fmt.Println(-1)
		}
	}
}
