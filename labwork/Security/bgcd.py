
def gcd(a, b):
  if b == 0:
    return a
  else:
    return gcd(b, a % b)

def bgcd(a,b):
  r = a
  rdash = b
  e = 0
  while (r % 2 == 0) & (rdash % 2 == 0):
    r = r >> 1
    rdash = rdash >> 1
    e = e + 1

  divs = 0
  subs = 0
  while rdash != 0:
    while (r % 2 == 0):
      r = r >> 1
      divs += 1
    while (rdash % 2 == 0):
      rdash = rdash >> 1
      divs +=1 
    if rdash < r: r, rdash = rdash, r
    rdash = rdash - r
    subs += 1

  print "Divisions, subtrations = ", e + divs, subs 
  d = pow(2, e) * r
  return d

data = raw_input("Enter two number a, b: ")
nos = data.split(" ")
a, b = int(nos[0]), int(nos[1])

#assert gcd(a, b) == bgcd(a, b)

print "Binary GCD = ", bgcd(a, b)

