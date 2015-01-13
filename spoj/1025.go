package main

import (
	"fmt"
	"sort"
)

type list []int

func (s list) Len() int {
	return len(s)
}

func (s list) Less(i, j int) bool {
	return s[i] < s[j]
}

func (s list) Swap(i, j int) {
	s[i], s[j] = s[j], s[i]
}

func main() {
	var t int
	fmt.Scanf("%d", &t)
	for ; t > 0; t-- {
		var N int
		fmt.Scanf("%d", &N)
		men := make(list, N)
		women := make(list, N)
		bond := 0
		for i := 0; i < N; i++ {
			fmt.Scanf("%d", &men[i])
		}
		for i := 0; i < N; i++ {
			fmt.Scanf("%d", &women[i])
		}
		sort.Sort(men)
		sort.Sort(women)
		for i := 0; i < N; i++ {
			bond += men[i] * women[i]
		}

		fmt.Println(bond)
	}
}
