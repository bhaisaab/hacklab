def gcd(p,q):
  if q == 0:
    return p
  return gcd(q,p%q)

def lcm(p,q):
  return p*q/gcd(p,q)

def lcmMethod():
  n = 20
  sets = n/2
  p = range(1,n+1)
  while sets > 0:
    q = []
    for i in range(1,sets+1):
      i,j = p[2*i-2], p[2*i-1]
      q.append( lcm(i,j) )
    p = q
    if (sets % 2) != 0:
      p[sets-2] = lcm(p[sets-2], p[sets-1])
    sets = sets/2
  return p[0]

# LCM method is faster
#def primeMethod():
#  #primes upto 20
#  p = [2,3,5,7,11,13,17,19] 
#  ans = 1
#  size = len(p)
#  while size > 0:
#    ans *= p[size-1]
#    size -= 1
#  return ans
#print primeMethod()
print lcmMethod()

