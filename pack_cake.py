import argparse
import os
import random
import subprocess


def next_key(k):
    # Linear conguential generator of form: k(n+1) = (a * k(n) + c) % m
    # We use params to match rand() in glibc
    a = 1103515245
    m = 2**31
    c = 12345
    return (a * k + c) % m

def crypt(input_, key):
    # XOR encryption is also decryption!
    output = []
    for c in input_:
        c = ord(c)
        c = c ^ (key & 0xef)
        output.append(chr(c))
        key = next_key(key)
    return ''.join(output)

def escape(x):
    return ''.join('\\%03o' % ord(c) for c in x)


parser = argparse.ArgumentParser()
parser.add_argument('-k', '--key', type=int)
parser.add_argument('-o', '--output', default='cake_taker')
parser.add_argument('-f', '--cake-filename')
parser.add_argument('password')
parser.add_argument('cake_file')
args = parser.parse_args()

if not args.key:
    args.key = random.randrange(0, 2**31 - 1)
    print 'Using random key:', args.key

# Prepare the C macros.
cake = crypt(open(args.cake_file).read(), args.key)
macros = {
    'KEY': args.key,
    'CRYPTED_PASSWORD': '"%s"' % escape(crypt(args.password, args.key)),
    'CRYPTED_CAKE': '"%s"' % escape(cake),
    'CAKE_SIZE': len(cake),
    'CAKE_FILENAME': '"%s"' % (args.cake_filename or os.path.basename(args.cake_file)),
}
macro_string = ''.join('#define %s %s\n' % x for x in macros.iteritems())

# Render the source template.
template = open('cake_taker_template.c').read()
template = template.replace('// TEMPLATE GOES HERE', macro_string)
c_path = args.output + '.c'
with open(c_path, 'w') as fh:
    fh.write(template)

# Compile it.
subprocess.check_call(['make', 'SRC=%s' % c_path, 'EXE=%s' % args.output])
