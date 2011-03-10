def fiestel(msg, key, decrypt=False):
    wordLen = len(msg)
    if len(msg) % 2 != 0:
        print "[+] padding msg"
        msg += " "
        wordLen += 1

    key = filter(str.isalpha, key).lower()
    if len(key) < wordLen/2:
        print "Key should be at least half the len of msg!!!"
        import sys
        sys.exit()

    l, r = [], []
    for char in msg[:len(msg)/2]:
        l.append(ord(char))

    for char in msg[len(msg)/2:]:
        r.append(ord(char))

    print "l, r = ", l, r

    if decrypt:
        temp = r
        r = l
        l = temp

    for i in range(16):
        temp = r
        for j in range(wordLen/2):
            r[j] = l[j] ^ r[j] ^ ord(key[j])
        l = temp

    return r+l

#Key of length 8
key = "zfyqpgxkwxjh"
msg = "attack is at dawn!"
print "msg[%s]: %s" % (len(msg), msg)
cipherText = ""
plainText = ""

for i in fiestel(msg, key):
    cipherText += chr(i)

for i in fiestel(cipherText, key, True):
    plainText += chr(i)

print "[c]: ", cipherText
print "[d]: ", plainText
