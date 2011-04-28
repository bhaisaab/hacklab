
# LCG
def random(a, x, m, c = 9):
  return (a*x+c) % m

def rand(max):
  from numpy.random import randint
  seed = randint(max)
  return random(randint(max), seed, max)

def hash(msg):
  h = 0
  for m in msg:
    h = h ^ ord(m)
  print "Hash of '%s' = " % msg, h
  return h

def gcd(a, b):
  if b == 0:
    return a
  else:
    return gcd(b, a % b)

def test_coprime(a, b):
  return gcd(a, b) == 1

def test_prime(p):
  #print "[!] Testing primality for", p
  if p == 0 or p == 1: return False
  import math
  for num in range(2, int(math.sqrt(p))+1):
    if p % num == 0: return False
  return True

def gen_prime(max):
  while True:
    p = rand(max)
    if test_prime(p): return p

def findg(p, q):
  while True:
    h = rand(p) # 1 < h < (p-1)
    print "[!] Possible H = ", h
    g = pow(h, (p-1)/q) % p
    if g > 1 and h > 1:
      return g

# gcd(a,b) = ax + by | a > b
# a^-1 mod b = x => nb+x = a^-1 => (an)b+ ax = 1
# Returns x, y
# Used to calculate multiplicative inverse
def extended_gcd(a,b):
  if b == 0: return (1,0)
  else:
    q, r = a/b, a%b
    s, t = extended_gcd(b, r)
  return (t, s - q * t)

def main():
#  msg = raw_input("Enter message")
  msg = "Kill Mr. Minister X"

  # Global Public Key Components
  q = gen_prime(100) # a 160 bit prime number, but using a simpler version :D
  print "Generate prime number 'q' =", q
  p = gen_prime(10000)
  while ((p-1) % q != 0):
    p = gen_prime(10000)
  print "Generate prime number 'p' =", p
  g = findg(p, q)
  print "Generate g =", g

  # User's private key
  x = 0
  while x < 1:  x = rand(q)
  # User's public key
  y = pow(g, x) % p
  print "Private Key (x) = %d. Public key (y) = %d" % (x, y)

  k = 0
  while k < 1: k = rand(q)
  print "User's Per-Message Secret Number, k =", k

  q, p, g, x, y, k = 19, 2699, 2396, 12, 62, 14

  # Signing
  r = (pow(g, k) % p) % q
  kinverse = extended_gcd(k, q)[0] % q # kinverse mod q
  print "k-1 = ", kinverse
  s = (kinverse * (hash(msg) + x * r)) % q
  print "Signature (r,s) = (%d, %d)" % (r,s)

  assert r != 0 and s != 0


  # Verifying
  msg = "Kill Mr. President"
  mdash, rdash, sdash = msg, r, s # They are received
  w =  extended_gcd(sdash, q)[0] % q
  u1 = (hash(msg) * w) % q
  u2 = (rdash * w) % q
  v = ((pow(g, u1) * pow(y, u2)) % p) % q

  print "[!] Verification: w, u1, u2, v =", w, u1, u2, v

  # Test
  if v == rdash:
    print "[!] Test PASSED, Signature verified"
  else:
    print "[!] Test FAILED"

if __name__ == "__main__":
  main()
