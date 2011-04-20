# Caesar Cipher
# Author: Rohit Yadav <rohit.yadav.cse07@itbhu.ac.in>
#         07020003, IDD Part IV, CSE

small = "abcdefghijklmnopqrstuvwxyz"
big   = small.upper()
size  = len(big)

def encipher(S, n = 3):
    finale_str = ''
    for c in S:
        if c.islower():
            c = small[ (small.find(c)+n) % size ]
        elif c.isupper():
            c = big[ (big.find(c)+n) % size ]
        finale_str += c
    return finale_str

def decipher(S, n = 3):
    finale_str = ''
    for c in S:
        if c.islower():
            c = small[ (small.find(c) - n) % size ]
        elif c.isupper():
            c = big[ (big.find(c) - n) % size ]
        finale_str += c
    return finale_str

# Encipher examples...
msg = "!@#$%^&*()+-=_1234567890{}[]:;'<>,./?~`\t A quick brown fox jumps over a lazy DOG!"
key = 5
print "[MESSAGE]: ", msg
print "[KEY]: ", key

cipherText = encipher(msg, key)
print "[Enciphered Msg]: ", cipherText

# Decipher examples...
print "[Deciphered Msg]: ", decipher(cipherText, key)

if( msg == decipher(cipherText, key) ):
    print "[RESULT] Algorithm successful"
else:
    print "[RESULT] Algorithm failed"

print "\n[BRUTE] Running decipher() for all key in range(1, 25):\n"

for i in range(26):
    if i != 0: print "[key = %2d]: %s" % (i, decipher(cipherText, i))
