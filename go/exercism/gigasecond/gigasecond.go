package gigasecond

import "time"

const Gigasecond time.Duration = 1e18

func AddGigasecond(input time.Time) time.Time {
	return input.Add(Gigasecond)
}
