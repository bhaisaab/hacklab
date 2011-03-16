# Blum Blum Shub PRNG

p = 383 
q = 503

if not p%4 == q%4 == 3:
  print "Error, p, q should be large primes that are congruent with 3 (mod 4 wise)."

m = p*q
xi = 9 # xi is a random number relatively prime to m, neither p/q is a factor of xi

def rng():
    global xi
    xi = (xi * xi) % m
    bi = xi % 2
    return (xi, bi)

for i in range(100):
    print rng()
