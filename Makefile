# RSA implementation and attack on Mbed
# Makefile
# @author Cyrille Toulet, <cyrille.toulet@gmail.com>
# @author Benjamin Burnouf, <benjamin76360@gmail.com>

COMPUTER_DATA  = src/tests/datasets/add.c
COMPUTER_DATA += src/tests/datasets/sub.c
COMPUTER_DATA += src/tests/datasets/mul-int-by-int.c
COMPUTER_DATA += src/tests/datasets/mul-bigint-by-int.c
COMPUTER_DATA += src/tests/datasets/mul-montgomery.c

COMPUTER_OBJ   = computer/obj/bigint.o
COMPUTER_OBJ  += computer/obj/tests/add.o
COMPUTER_OBJ  += computer/obj/tests/sub.o
COMPUTER_OBJ  += computer/obj/tests/mul-int-by-int.o
COMPUTER_OBJ  += computer/obj/tests/mul-bigint-by-int.o
COMPUTER_OBJ  += computer/obj/tests/shift.o
COMPUTER_OBJ  += computer/obj/tests/mul-montgomery.o

COMPUTER_BIN   = computer/bin/tests/add
COMPUTER_BIN  += computer/bin/tests/sub
COMPUTER_BIN  += computer/bin/tests/mul-int-by-int
COMPUTER_BIN  += computer/bin/tests/mul-bigint-by-int
COMPUTER_BIN  += computer/bin/tests/shift
COMPUTER_BIN  += computer/bin/tests/mul-montgomery

# Generic
all: $(COMPUTER_BIN)

# Datasets
src/tests/datasets/add.c: ./src/tests/generators/add.py
	python src/tests/generators/add.py > src/tests/datasets/add.c

src/tests/datasets/sub.c: ./src/tests/generators/sub.py
	python src/tests/generators/sub.py > src/tests/datasets/sub.c

src/tests/datasets/mul-int-by-int.c: ./src/tests/generators/mul-int-by-int.py
	python src/tests/generators/mul-int-by-int.py > src/tests/datasets/mul-int-by-int.c

src/tests/datasets/mul-bigint-by-int.c: ./src/tests/generators/mul-bigint-by-int.py
	python src/tests/generators/mul-bigint-by-int.py > src/tests/datasets/mul-bigint-by-int.c

src/tests/datasets/mul-montgomery.c: ./src/tests/generators/mul-montgomery.py
	python src/tests/generators/mul-montgomery.py > src/tests/datasets/mul-montgomery.c

# Objects
computer/obj/bigint.o: src/bigint.c
	gcc -m32 -c -o computer/obj/bigint.o src/bigint.c -D_COMPUTER_VERSION

computer/obj/tests/add.o: src/tests/add.c src/tests/datasets/add.c
	gcc -m32 -c -o computer/obj/tests/add.o src/tests/add.c -D_COMPUTER_VERSION

computer/obj/tests/sub.o: src/tests/sub.c src/tests/datasets/sub.c
	gcc -m32 -c -o computer/obj/tests/sub.o src/tests/sub.c -D_COMPUTER_VERSION

computer/obj/tests/mul-bigint-by-int.o: src/tests/mul-bigint-by-int.c src/tests/datasets/mul-bigint-by-int.c
	gcc -m32 -c -o computer/obj/tests/mul-bigint-by-int.o src/tests/mul-bigint-by-int.c -D_COMPUTER_VERSION

computer/obj/tests/mul-int-by-int.o: src/tests/mul-int-by-int.c src/tests/datasets/mul-int-by-int.c
	gcc -m32 -c -o computer/obj/tests/mul-int-by-int.o src/tests/mul-int-by-int.c -D_COMPUTER_VERSION

computer/obj/tests/shift.o: src/tests/shift.c src/tests/datasets/add.c
	gcc -m32 -c -o computer/obj/tests/shift.o src/tests/shift.c -D_COMPUTER_VERSION

computer/obj/tests/mul-montgomery.o: src/tests/mul-montgomery.c src/tests/datasets/mul-montgomery.c
	gcc -m32 -c -o computer/obj/tests/mul-montgomery.o src/tests/mul-montgomery.c -D_COMPUTER_VERSION

# Binaries
computer/bin/tests/add: computer/obj/tests/add.o computer/obj/bigint.o
	gcc -m32 -o computer/bin/tests/add computer/obj/tests/add.o computer/obj/bigint.o -D_COMPUTER_VERSION

computer/bin/tests/sub: computer/obj/tests/sub.o computer/obj/bigint.o
	gcc -m32 -o computer/bin/tests/sub computer/obj/tests/sub.o computer/obj/bigint.o -D_COMPUTER_VERSION

computer/bin/tests/mul-int-by-int: computer/obj/tests/mul-int-by-int.o computer/obj/bigint.o
	gcc -m32 -o computer/bin/tests/mul-int-by-int computer/obj/tests/mul-int-by-int.o computer/obj/bigint.o -D_COMPUTER_VERSION

computer/bin/tests/mul-bigint-by-int: computer/obj/tests/mul-bigint-by-int.o computer/obj/bigint.o
	gcc -m32 -o computer/bin/tests/mul-bigint-by-int computer/obj/tests/mul-bigint-by-int.o computer/obj/bigint.o -D_COMPUTER_VERSION

computer/bin/tests/shift: computer/obj/tests/shift.o computer/obj/bigint.o
	gcc -m32 -o computer/bin/tests/shift computer/obj/tests/shift.o computer/obj/bigint.o -D_COMPUTER_VERSION

computer/bin/tests/mul-montgomery: computer/obj/tests/mul-montgomery.o computer/obj/bigint.o
	gcc -m32 -o computer/bin/tests/mul-montgomery computer/obj/tests/mul-montgomery.o computer/obj/bigint.o -D_COMPUTER_VERSION

# Tests
tests: computer/bin/tests/add computer/bin/tests/sub computer/bin/tests/mul-int-by-int computer/bin/tests/mul-bigint-by-int computer/bin/tests/shift computer/bin/tests/mul-montgomery
	./computer/bin/tests/add
	./computer/bin/tests/sub
	./computer/bin/tests/mul-int-by-int
	./computer/bin/tests/mul-bigint-by-int
#	./computer/bin/tests/shift
	./computer/bin/tests/mul-montgomery

# Misc
.PHONY: clean

clean:
	rm -f $(COMPUTER_DATA)
	rm -f $(COMPUTER_OBJ)
	rm -f $(COMPUTER_BIN)

