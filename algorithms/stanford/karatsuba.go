package main

import (
	"fmt"
	"math/big"
)

func power10(n uint) int64 {
	r := int64(1)
	for i := uint(0); i < n; i++ {
		r *= 10
	}
	return r
}

func split(a *big.Int, m uint) (high, low *big.Int) {
	high, _ = big.NewInt(0).SetString(a.String()[:len(a.String())-int(m)], 10)
	low, _ = big.NewInt(0).SetString(a.String()[len(a.String())-int(m):], 10)
	return
}

func add(a, b *big.Int) *big.Int {
	return big.NewInt(0).Add(a, b)
}

func mul(a, b *big.Int) *big.Int {
	return big.NewInt(0).Mul(a, b)
}

func sub(a, b *big.Int) *big.Int {
	return big.NewInt(0).Sub(a, b)
}

func karatsuba(a, b *big.Int) *big.Int {
	if a.Cmp(big.NewInt(10)) < 1 || b.Cmp(big.NewInt(10)) < 1 {
		return mul(a, b)
	}

	// find the pivot
	m := len(a.String())
	if m < len(b.String()) {
		m = len(b.String())
	}
	m = m/2 + m%2

	highA, lowA := split(a, uint(m))
	highB, lowB := split(b, uint(m))

	z0 := karatsuba(highA, highB)
	z1 := karatsuba(lowA, lowB)
	z2 := karatsuba(add(highA, lowA), add(highB, lowB))
	z2 = sub(z2, add(z0, z1))

	// z0*10^2m+(z2-z1-z0)*10^m+z1
	temp0 := mul(z0, big.NewInt(power10(uint(2*m))))
	temp1 := mul(z2, big.NewInt(power10(uint(m))))
	temp2 := add(temp0, temp1)

	return add(temp2, z1)
}

func main() {
	var a string
	var b string
	fmt.Scanf("%s", &a)
	fmt.Scanf("%s", &b)

	A := new(big.Int)
	A.SetString(a, 10)
	B := new(big.Int)
	B.SetString(b, 10)

	fmt.Println("Karatsuba a*b =", karatsuba(A, B))
	fmt.Println("Normal    a*b =", A.Mul(A, B))
}
