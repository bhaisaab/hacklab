from math import sqrt

def isPrime(n):
  if n<2: return False
  if n%2==0: return False
  for i in range(2,int(sqrt(n))+1):
    if n%i==0: return False
  return True

no = 600851475143
lst=range(2,int(sqrt(no))+1)
lst.reverse()
for i in lst:
  if isPrime(i) and no%i==0:
    print 'voila',i
    break
