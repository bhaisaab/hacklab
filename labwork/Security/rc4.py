def rc4crypt(data, key):
    # Initialization
    s = range(256)
    # Initial permutation of s
    j = 0
    for i in range(256):
        j = ( j + s[i] + ord(key[i % len(key)]) ) % 256
        s[i], s[j] = s[j], s[i]
     # Stream Generation
    i,j = 0,0
    out = []
    for char in data:
        i = ( i + 1 ) % 256
        j = ( j + s[i] ) % 256
        s[i], s[j] = s[j], s[i]
        t = ( s[i] + s[j] ) % 256
        k = s[t]
        out.append( chr( ord(char) ^ k ) )

    return ''.join(out)

def main():
    key = 'secret!@#$%'
    msg = 'Top Secret Business Transaction'
    cipher = rc4crypt(msg, key)
    decipher = rc4crypt(cipher, key)
    print '[*] Plain text = ', msg, ' | key = ', key, ' | cipher text = ', cipher

    if decipher == msg:
        print '[+] Algorithm success!'
    else:
        print '[!] Algorithm failure'

if __name__ == '__main__':
    main()
