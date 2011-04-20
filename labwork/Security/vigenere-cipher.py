# Vigenere Cipher
# Author: Rohit Yadav <rohit.yadav.cse07@itbhu.ac.in>
#         07020003, IDD Part IV, CSE

def vigenere(message, key, decrypt = False):

    message = filter(str.isalpha, message).lower()
    key = filter(str.isalpha, key).lower()

    if not decrypt:
        print "[Encryting] ", message
    else:
        print "{Decryting} ", message

    alpha = 'abcdefghijklmnopqrstuvwxyz'
    tonum = dict([(alpha[i], i) for i in range(len(alpha))])

    # Create Vigenere Square aka tabula recta
    lookup = dict([(a, 0) for a in alpha])
    for a in lookup:
        if not decrypt:
            lookup[a] = dict([(b, alpha[(tonum[a] + tonum[b]) % len(alpha)]) for b in alpha])
        else:
            lookup[a] = dict([(b, alpha[(tonum[a] - tonum[b]) % len(alpha)]) for b in alpha])

    out = ''
    for i in range(len(message)):
        letter = lookup[message[i].lower()][key[ i % len(key) ]]
        out += letter

    return out

key = "lemon"
msg = "attackatdawn"
cipherText = vigenere(msg, key)
plainText = vigenere(cipherText, key, True)

print "Decypted message:" , plainText

if plainText == msg: print "Algorithm Success"
else: "Algorithm failed :("
