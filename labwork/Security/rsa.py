# RSA
# Author: Rohit Yadav <rohit.yadav.cse07@itbhu.ac.in>
#         07020003, IDD Part IV, CSE

# Returns gcd of a, b
def gcd(a, b):
  if b == 0:
    return a
  else:
    return gcd(b, a % b)

# gcd(a,b) = ax + by | a > b
# a^-1 mod b = x => nb+x = a^-1 => (an)b+ ax = 1
# Returns x, y
def extended_gcd(a,b):
  if b == 0: return (1,0)
  else:
    q, r = a/b, a%b
    s, t = extended_gcd(b, r)
  return (t, s - q * t)

def encrypt(msg, PU):
  cipher = []
  for i in range(len(msg)):
    cipher.append(chr(pow(ord(msg[i]), PU['e']) % PU['n']))
  return ''.join(cipher)

def decrypt(cipher, PR):
  msg = []
  for i in range(len(cipher)):
    msg.append(chr(pow(ord(cipher[i]), PR['d']) % PR['n']))
  return ''.join(msg)

p = 17
q = 11
n = p * q
phi = (p-1) * (q-1)
# e < n
e = 7

# check that e is relatively prime to phi
assert gcd(phi, e) == 1

# d*e ~= 1 (mod phi) and d < phi
d = extended_gcd(e, phi)[0]
assert (d*e % phi) == 1

PU = {'e':e, 'n':n}
PR = {'d':d, 'n':n}

msg = "Top secret message, go to / and run rm -fr * to remove everthing"
cipher = encrypt(msg, PU)
decipher = decrypt(cipher, PR)
assert decipher == msg
print "Msg:", msg
print "ENCRYPT[%s]: %s" % (PU, cipher)
print "DECRYPT[%s]: %s" % (PR, decipher)

