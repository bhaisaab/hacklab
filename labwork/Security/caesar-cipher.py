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
msg = "\t!@#$%^&*()+-=_1234567890{}[]:;'<>,./?~` A quick brown fox jumps over a lazy DOG!\n"
key = 5
print "[MESSAGE]: "
print msg
print "[KEY]: ", key

cipherText = encipher(msg, key)
print "[Testing Encipher]"
print cipherText

# Decipher examples...
print "[Testing Decipher]"
print decipher(cipherText, key)

if( msg == decipher(cipherText, key) ):
    print "[RESULT] Algorithm successful\n"
else:
    print "[RESULT] Algorithm failed\n"
