package main

import (
	"fmt"
	"log"
	"math"
	"time"
)

type Point struct {
	x, y int64
}

type Line struct {
	a, b Point
}

type futureLine chan Line
type futurePoint chan Point

func (p Point) String() string {
	return fmt.Sprintf("Point x=%d y=%d", p.x, p.y)
}

func (l Line) String() string {
	return fmt.Sprintf("Line len=%f p1=(%v) p2=(%v)", l.Length(), l.a, l.b)
}

func (l Line) Length() float64 {
	xdiff := l.b.x - l.a.x
	ydiff := l.b.y - l.a.y
	return math.Sqrt(math.Pow(float64(xdiff), 2) + math.Pow(float64(ydiff), 2))
}

func GetPoint(x, y int64) Point {
	log.Println("AsyncGetPoint called")
	return <-AsyncGetPoint(x, y)
}

func GetLine(a, b Point) Line {
	log.Println("AsyncGetLine called")
	return <-AsyncGetLine(a, b)
}

func AsyncGetPoint(x, y int64) futurePoint {
	point := make(futurePoint)
	go func() {
		time.Sleep(100 * time.Millisecond)
		log.Println("Async getting point")
		point <- Point{x: x, y: y}
	}()
	return point
}

func AsyncGetLine(a, b Point) futureLine {
	line := make(futureLine)
	go func() {
		time.Sleep(1000 * time.Millisecond)
		log.Println("Async getting line")
		line <- Line{a: a, b: b}
	}()
	return line
}

func main() {
	fmt.Println("Welcome to future")
	a := GetPoint(10, 10)
	b := GetPoint(20, 20)
	line := GetLine(a, b)
	fmt.Printf("Future Line:: %v", line)
}
