import sys
for line in sys.stdin:
	i = int(line)
	if i == 42:
		break
	print i
