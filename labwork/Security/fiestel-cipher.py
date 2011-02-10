def feistel(msg, key, decrypt=False):
    wordLen = len(msg)
    if not wordLen % 2:
        msg += " "
        wordLen += 1
    key = filter(str.isalpha, key).lower()

    l, r = msg[:wordLen/2], msg[wordLen/2:]

    if not decrypt:
        print "[Encryting] ", message
    else:
        print "{Decryting} ", message

    return out

#Key of length 8
key = "zfyqpgxk"
msg = "attackisatdawnmann"
cipherText = fiestel(msg, key)
plainText = fiestel(cipherText, key, True)

