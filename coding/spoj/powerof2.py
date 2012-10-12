import math

def powerof2(num):
  n = math.log(num, 2)
  if int(math.ceil(n - math.floor(n))) == 0:
    return num*2
  return long(pow(2, math.ceil(n)))

n = input()
for i in range(n):
  print powerof2(int(input()))
