package clock

import "fmt"

type Clock struct {
	hour   int
	minute int
}

func (c Clock) String() string {
	return fmt.Sprintf("%.2d:%.2d", c.hour, c.minute)
}

func (c Clock) Add(minutes int) Clock {
	c.minute += minutes
	c.hour += c.minute / 60

	if c.minute < 0 {
		c.hour -= 1
	}

	c.minute = (60 + c.minute%60) % 60
	c.hour = (24 + c.hour%24) % 24
	return c
}

func New(hour, minute int) Clock {
	return Clock{hour, minute}
}
