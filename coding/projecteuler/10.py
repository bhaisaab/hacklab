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
  plen+=1
  return True

#O(n sqrtn)
def brute():
  psum = 2
  n = 3
  while n < 2000000:
    if isPrime(n):
      psum += n
    n+=2
  return psum

#O(nloglogn)
def sieve(): #ofEratosthenes
  limit = 2000000
  nos = [False,False,True] # 0,1,2
  crosslimit = int(sqrt(limit))+1

  #Initialize
  for i in range(3,limit):
    nos.append(i)
    if (i%2) == 0:
      nos[i] = False
    else:
      nos[i] = True

  for i in range(3,crosslimit):
    if nos[i]: # got prime
      j = i*i #all multiples of i till i*i already crossed
      while j < limit:
        nos[j] = False
        j += 2*i # proceed to cross odd multiples

  sum = 0
  for n in range(2,limit):
    if nos[n]:
      sum += n
  return sum

def sieveOptimized():
  #We start searching from 3, 5, 7... 2*10^6-1
  limit = 2000000
  sievebound = (limit-1)/2
  crosslimit = (int(sqrt(limit))-1)/2
  sieve = [False] # 0th is a dummy

  #Initialize
  for i in range(1,sievebound+1):
    sieve.append(True)

  for i in range(1,crosslimit+1):
    if sieve[i]: # got prime at 2*i+1
      j = i*2*(i+1) # Start at i*the prime
      while j <= sievebound:
        sieve[j] = False
        j += (2*i+1) # proceed to the multiples, 2i+1 which is odd :)

  sum = 2 #2 is prime
  for i in range(1,sievebound+1):
    if sieve[i]:
      sum = sum + (2*i+1)
  return sum

print sieveOptimized() # brute()

