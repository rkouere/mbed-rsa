from gmpy import invert


b = pow(2, 32)
#b = 10
n = 32
#n = 5


def big_build(l):
	n = 0
	for i in range(0, len(l) - 1):
		n = n + l[i] * pow(2, 32 * i)
	return n


#def extract(n, i):
#	return (n >> (32 * i)) & 0xFFFFFFFF

def extract(n, i):
	return (n / pow(b, i)) % b

m = big_build([0x746fa4c1, 0xb01acc75, 0x232c9ae5, 0xb39f23b3, 0xa6ca2f82, 0xf6fc6f4d, 0x4b412bf0, 0xefdf3324, 0x9cb65298, 0xf4588df0, 0x3bab5bf6, 0x79288432, 0xa777a944, 0x7ed47a34, 0x4a65ed2c, 0x7835a9a9, 0x74db84e7, 0x5f956058, 0xbe35bcd3, 0x1f2bbc6c, 0x1f6843af, 0xccfd4001, 0xada2ebeb, 0xfb89fdf3, 0x5eb01219, 0x3ce97f24, 0xdcf5b793, 0x6ccfa480, 0x65ccd5f4, 0x271794fd, 0x23712f97, 0x1efd3962, 0x00000000, 0x00000000])
#m =  72639

#mp = 0x62e185fb
mp = (-invert(m, pow(2,32)) % pow(2, 32))
#mp = 1

r = pow(b, n)
rp = invert(r, m)

#x = big_build([0xecc0ae5d, 0x4a67cec4, 0x5c9afeb2, 0x10a5ff05, 0xb0117eac, 0x846a35ac, 0xbd1a94cc, 0x393dc9a2, 0x1d5cc37f, 0x91511fb9, 0xae287ed8, 0xeb8b8f0e, 0x69031e30, 0x0921a035, 0x22f11a51, 0x9156466b, 0x088f3373, 0x9a3192ee, 0xf021d23d, 0x965165e6, 0xb12a9988, 0x36220967, 0x27b78557, 0xd1a2a1dc, 0x5cb18ced, 0xdbdc3d1c, 0x6bc4dc50, 0x9f2c1354, 0x83413afb, 0xfe44e120, 0xfe3a1aee, 0x7c0f5a7c, 0x00000000])
x = big_build([0xecc0ae5d, 0x4a67cec4, 0x5c9afeb2, 0x10a5ff05, 0xb0117eac, 0x846a35ac, 0xbd1a94cc, 0x393dc9a2, 0x1d5cc37f, 0x91511fb9, 0xae287ed8, 0xeb8b8f0e, 0x69031e30, 0x0921a035, 0x22f11a51, 0x9156466b, 0x088f3373, 0x9a3192ee, 0xf021d23d, 0x965165e6, 0xb12a9988, 0x36220967, 0x27b78557, 0xd1a2a1dc, 0x5cb18ced, 0xdbdc3d1c, 0x6bc4dc50, 0x9f2c1354, 0x83413afb, 0xfe44e120, 0xfe3a1aee, 0x00000000, 0x00000000])
#x = 5792
y = x
#y = 1229

excepted = big_build([0x35c1437f, 0x5562687e, 0xc315675a, 0xd4eeb096, 0xcecf3cc0, 0xbc0a55c1, 0xc7018223, 0xf8dfd0c6, 0x963b5369, 0x840b615a, 0x4dbd8c72, 0xce740625, 0x4bd3c43f, 0xed30732d, 0x2474b38f, 0xc2739e49, 0x2ba940c9, 0xa8f21271, 0xe5702c01, 0xfcddbf89, 0x81fc35c8, 0x6e378b9c, 0x5cb7f608, 0xb8a78502, 0x00a1e7a9, 0x2e6f0d74, 0x3b390641, 0xc998fdf2, 0xa5e43948, 0xf2e5b50b, 0x83bfc939, 0x17cf4341, 0x00000000, 0x00000000])


a = 0
u = 0

for i in range(0, n):
	#print "xi : " + str(extract(x, i))
	u = ((extract(a, 0) + extract(x, i) * extract(y, 0)) * mp) % b
	#print "xi*y0 : " + str(extract(x, i) * extract(y, 0))
	tmp1 = extract(x, i) * y
	print hex(tmp1 % pow(b, 32))
	#print "ui : " + str(u)
	#print "xi*y : " + str(tmp1)
	tmp2 = u * m
	print hex(tmp2 % pow(b, 32))
	#print "ui*m : " + str(tmp2)
	a = (a + extract(x, i) * y + u * m) % pow(b, 32) / b
	#a = (a + extract(x, i) * y + u * m) / b
	print hex(a % pow(b, 32))
	#print "a : " + str(a)
	print "\n"

if a > m:
	a = a - m

#for i in range(0, 1000000):
#	if ((x*y*i) % m) == a:
#		print "ICIIIII => " + str(i)
#print rp

out = (x * y * rp) % m

print "HOP"
#print hex(r)
print hex(a)
#print a
#print hex(a * r)
print hex(out)
#print out
#print hex(excepted - out)
#print hex(rp)
