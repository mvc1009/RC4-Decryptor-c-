import base64
import array
import sys
import io

filename = sys.argv[1]
password = sys.argv[2]
out_filename = sys.argv[3]

def print_hex(a):
    out = "{"
    for i in range(0,len(a) -1, 2):
        if i == len(a)-2:
            out += "0x%s%s" % (a[i],a[i+1])
        else:
            out += "0x%s%s, " % (a[i],a[i+1])
    out += "}"
    print(out)
    print()

def ByteToHex (bytestring):
    s = ''.join('{:02x}'.format(x) for x in bytestring)
    return s

def encodeb64(data):
    return base64.b64encode(data)

def crypt(key, data):
    S = list(range(256))
    j = 0

    for i in list(range(256)):
        j = (j + S[i] + ord(key[i % len(key)])) % 256
        S[i], S[j] = S[j], S[i]

    j = 0
    y = 0
    out = []

    for char in data:
       j = (j + 1) % 256
       y = (y + S[j]) % 256
       S[j], S[y] = S[y], S[j]
       out.append(char ^ S[(S[j] + S[y]) % 256])
       
    return out

def read_filename(path):

    f = open(path, "rb") # read binary data
    s = f.read() # read all bytes into a string
    print(len(s))
    return array.array("B", s) # "f" for float

def write_filename(path, ciphered_data):
    out_filename = open(path, "wb") 
    out_filename.write(ciphered_data)
    out_filename.close()

data = read_filename(filename)
print("[!] Data")
print_hex(ByteToHex(data))

#encoded_data = encodeb64(data)
#print("[!] B64 Encoded Data")
#print_hex(ByteToHex(encoded_data))
#print(encoded_data)

ciphered_data = crypt (password, data)
key = [ord(char) for char in password]
print("[!] Key")
print_hex(ByteToHex(key))

print("[!] Encrypted RC4 Data")
print_hex(ByteToHex(ciphered_data))

write_filename(out_filename, array.array("B", ciphered_data))