from math import sqrt

primes = [2]
plen = 1
 
def isPrime(n):
  global primes,plen
  if n < 2: return False
  if n == 2: return True
  if (n % 2) == 0: return False
  c = 0
  limit = sqrt(n) + 1
  while c < plen and primes[c] < limit:
    if (n%primes[c])==0: return False
    c+=1
  primes.append(n)
  plen += 1
  return True

pc = 1
n = 3
while pc != 10001:
  if isPrime(n):
    pc+=1;
  n+=2

print n-2
