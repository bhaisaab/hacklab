k = []
rounds = 16

def fiestel(l, r, k, rev=False):
    for i in range(rounds):
        temp = r[:]
        for j in range(len(r)):
            if rev:
                r[j] = l[j] ^ (r[j] ^ ord(k[15-i]))
            else:
                r[j] = l[j] ^ (r[j] ^ ord(k[i]))
        l = temp
    return l,r

def pm(l,r):
    ml, mr = '',''
    for i in range(len(l)):
        ml += chr(l[i])
        mr += chr(r[i])
    return ml+mr

#Key of length 16
key = "1234567890abcdef"
msg = "attackisatdawn"
print "msg[%s]: %s" % (len(msg), msg)
k = key

l, r = [], []
for char in msg[:len(msg)/2]:
    l.append(ord(char))
for char in msg[len(msg)/2:]:
    r.append(ord(char))

l,r = fiestel(l, r, k)
print pm(r,l)
l,r = fiestel(r, l, k, True)
print pm(r,l)

