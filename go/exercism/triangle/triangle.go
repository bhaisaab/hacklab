package triangle

import "math"

type Kind int

const (
	Equ Kind = iota
	Iso
	Sca
	NaT
)

func KindFromSides(a, b, c float64) Kind {
	if math.IsNaN(a) || math.IsNaN(b) || math.IsNaN(c) || math.IsInf(a, 0) || math.IsInf(b, 0) || math.IsInf(c, 0) {
		return NaT
	}
	if a+b <= c || a+c <= b || b+c <= a {
		return NaT
	}
	if a == b && b == c {
		return Equ
	}
	if a == b || b == c || c == a {
		return Iso
	}
	return Sca
}
