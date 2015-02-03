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
	return (n // pow(b, i)) % b

m = big_build([0x1630b245, 0x79bad951, 0xd09ca0ea, 0xa4ceffac, 0x29d2e82e, 0xb4740dc2, 0x78604f36, 0x286407cc, 0x19c112cc, 0x26972bc0, 0x7be3150a, 0x7a4538fa, 0xda3bd403, 0xd3d06696, 0xb8f6aa7f, 0x323a357c, 0xdc37e6e, 0x631744c5, 0xd1b91bc6, 0xf90dc58b, 0xbaef1cea, 0x207358e7, 0x5a718af3, 0x97856659, 0x752c9b2f, 0x7936ead3, 0x2e66ee75, 0x35a1c66f, 0x4aa2e454, 0x64321fbe, 0x4540aeda, 0xf7bc3e1, 0x0, 0x0])



#m =  72639

#mp = 0x8161ceaf
mp = (-invert(m, pow(2,32)) % pow(2, 32))
#mp = 1

r = pow(b, n)
rp = invert(r, m)

x = big_build([0xe5dcde13, 0xa5ec7243, 0xa3aaf01, 0x36f2cf79, 0xdd4eba41, 0x6a38a1a8, 0x9245d29, 0xe23ccf64, 0x4573f035, 0x3ffbf8e0, 0x5a8cf48a, 0x7c6ba9b7, 0x42eef170, 0x4ffd254b, 0xb2877e41, 0x2e09e1e9, 0xa2e10d55, 0x2d21e3af, 0x59b03b6f, 0xa2269f84, 0x655efa2c, 0x34e997f4, 0xdbfa173d, 0xb5dffca1, 0xb89809d0, 0x6fe6ca3f, 0x58245a38, 0xe7711d6c, 0x4ad2b337, 0x1297c5d3, 0x2d21e818, 0xad254af, 0x0, 0x0])
#x = 5792
y = x
#y = 1229

expected = big_build([0xc6afeeb8, 0x42e15b17, 0x8dea937f, 0x67fbfa68, 0x8a3fa156, 0xb3c986ac, 0x9481a463, 0xade1fb35, 0x42b1382, 0x44f8e69, 0xd003db24, 0x119ca78d, 0xcc844b51, 0xb2032bf2, 0xd5088534, 0x53a29f4f, 0x1eefd919, 0x89c57f70, 0x949d6404, 0x67f9450, 0x84d7efa7, 0x38ad0e97, 0xaaadd7c8, 0x26835474, 0x419bfbfb, 0x1e02de29, 0x2e19dc2b, 0x41af2b6a, 0x873e4a9, 0xbfad7f05, 0x6ae9caac, 0x24e0b29, 0x0, 0x0])







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
