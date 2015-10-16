


def next_key(k):
    # k(n+1) = (a * k(n) + c) % m
    # We use params to match rand() in glibc
    a = 1103515245
    m = 2**31
    c = 12345
    return (a * k + c) % m

def crypt(input_, key):
    output = []
    for c in input_:
        c = ord(c)
        c = c ^ (key & 0xef)
        output.append(chr(c))
        key = next_key(key)
    return ''.join(output)


x = crypt('TEST CAKE!', 1234)
print ''.join('\\%03o' % ord(c) for c in x)

