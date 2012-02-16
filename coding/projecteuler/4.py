
def checkPalin(n):
  rev = 0
  num = n
  while n>0:
    rev = 10*rev + (n%10)
    n /= 10
  if num == rev:
    return True
  return False

largest = 0,0

def brute():
  global largest
  i = 999
  j = 999
  while j > 99:
    if checkPalin(i*j):
      if (i+j) > (largest[0]+largest[1]):
        largest = i,j
    if i < 100:
      j = j-1
      i = 999
    i = i-1

brute()
print largest, largest[0]*largest[1]
