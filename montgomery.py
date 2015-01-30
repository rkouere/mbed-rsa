from gmpy2 import invert

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
	return (n // pow(b, i)) % b

m = big_build([0xd9afb7b1, 0xeadb7ae1, 0xa1c4f26c, 0x0409de5e, 0xfca539c6, 0x78f2dac8, 0x411f9a64, 0x333c9091, 0x30555b92, 0x98252cfb, 0xc61c9910, 0x1f69ee58, 0xa8592326, 0x7d816de1, 0x3d2fa190, 0x20b726ad, 0x7d6847a3, 0x0333eca1, 0xd8d7218d, 0x92a3abb6, 0xe5b0d3df, 0x3ff83971, 0x2e33b7a0, 0xfb615a0d, 0x2d04b17d, 0x3b1aae94, 0xc77fff97, 0x23af67fd, 0x4a6d87cb, 0x65a06b55, 0x2d4e5c1c, 0x2535a251, 0x00000000, 0x00000000])
#m =  72639

mp = 0x8161ceaf
#mp = (-invert(m, pow(2,32)) % pow(2, 32))
#mp = 1

r = pow(b, n)
rp = invert(r, m)

#x = big_build([0xecc0ae5d, 0x4a67cec4, 0x5c9afeb2, 0x10a5ff05, 0xb0117eac, 0x846a35ac, 0xbd1a94cc, 0x393dc9a2, 0x1d5cc37f, 0x91511fb9, 0xae287ed8, 0xeb8b8f0e, 0x69031e30, 0x0921a035, 0x22f11a51, 0x9156466b, 0x088f3373, 0x9a3192ee, 0xf021d23d, 0x965165e6, 0xb12a9988, 0x36220967, 0x27b78557, 0xd1a2a1dc, 0x5cb18ced, 0xdbdc3d1c, 0x6bc4dc50, 0x9f2c1354, 0x83413afb, 0xfe44e120, 0xfe3a1aee, 0x7c0f5a7c, 0x00000000])
x = big_build([0x049a3551, 0x328f1e26, 0xe60bf250, 0x86127664, 0x926a4601, 0x30cd5003, 0x5fe02dd7, 0x4cfc1902, 0xd62331fc, 0x5fd3644c, 0xd7c65314, 0xf9c7a6e3, 0x79c2ce5f, 0xcf89dd90, 0x6f275516, 0x5a6ab92c, 0xd46a70b7, 0xb421cdf4, 0x1afda597, 0xdaa6556a, 0xffb5bd27, 0x09ba5597, 0x47c72b03, 0x96fe00c9, 0x7fb977a2, 0x42dca8c0, 0xd0831291, 0xa4669ab9, 0x9d5f6524, 0x73556b8b, 0xd628f5c6, 0xb38bde1c, 0x00000000, 0x00000000])
#x = 5792
y = x
#y = 1229

expected = big_build([0xeafbe17c, 0x72534157, 0x29a36197, 0xa9c94801, 0x1ffc9122, 0x719fe735, 0x3c07e06f, 0xc31f0106, 0x79e0075b, 0x645dc415, 0x6e4143d4, 0x3ee187f6, 0xd9cc1f03, 0xdd9e7b19, 0xb4ac8973, 0xea46f363, 0xd3a691b1, 0x5a469bac, 0xbec6ebe2, 0x2fc60941, 0x41f8d9e2, 0x0a5c9f94, 0x91d2e8af, 0x957daa65, 0xde9af78f, 0x96b64b8e, 0x055cd263, 0x08c46257, 0xe16ff1c7, 0xa86adb66, 0xe9ab1a77, 0x085c1238, 0x00000000, 0x00000000])

expected2 = (x*x*rp)%m

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
	a = (a + extract(x, i) * y + u * m) // b
	#a = (a + extract(x, i) * y + u * m) / b
        print "A :\n"
	print hex(a % pow(b, 33))
	#print "a : " + str(a)
	print "\n"

if a >= m:
	a = a - m

#for i in range(0, 1000000):
#	if ((x*y*i) % m) == a:
#		print "ICIIIII => " + str(i)
#print rp

#out = (x * y * rp) % m

print "HOP"
#print hex(r)
print "A (apres sub) : \n"
print hex(a)
print "\n"
print hex(expected)
print hex(expected2)
#print a
#print hex(a * r)
#print hex(out)
#print out
#print hex(excepted - out)
#print hex(rp)
