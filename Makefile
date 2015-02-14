# RSA implementation and attack on Mbed
# Makefile
# @author Cyrille Toulet, <cyrille.toulet@linux.com>
# @author Benjamin Burnouf, <benjamin76360@gmail.com>

DATA  = src/tests/datasets/add.c
DATA += src/tests/datasets/sub.c
DATA += src/tests/datasets/mul-int-by-int.c
DATA += src/tests/datasets/mul-bigint-by-int.c
DATA += src/tests/datasets/montgomery-mul.c
DATA += src/tests/datasets/mod-exp.c

OBJ   = tests/obj/bigint.o
OBJ  += tests/obj/tests/add.o
OBJ  += tests/obj/tests/sub.o
OBJ  += tests/obj/tests/mul-int-by-int.o
OBJ  += tests/obj/tests/mul-bigint-by-int.o
OBJ  += tests/obj/tests/shift.o
OBJ  += tests/obj/tests/montgomery-mul.o
OBJ  += tests/obj/tests/mod-exp.o

BIN   = tests/bin/tests/add
BIN  += tests/bin/tests/sub
BIN  += tests/bin/tests/mul-int-by-int
BIN  += tests/bin/tests/mul-bigint-by-int
BIN  += tests/bin/tests/shift
BIN  += tests/bin/tests/montgomery-mul
BIN  += tests/bin/tests/mod-exp


# Global rule
all: $(BIN)


# Testing datasets
src/tests/datasets/add.c: ./src/tests/generators/add.py
	python src/tests/generators/add.py > src/tests/datasets/add.c

src/tests/datasets/sub.c: ./src/tests/generators/sub.py
	python src/tests/generators/sub.py > src/tests/datasets/sub.c

src/tests/datasets/mul-int-by-int.c: ./src/tests/generators/mul-int-by-int.py
	python src/tests/generators/mul-int-by-int.py > src/tests/datasets/mul-int-by-int.c

src/tests/datasets/mul-bigint-by-int.c: ./src/tests/generators/mul-bigint-by-int.py
	python src/tests/generators/mul-bigint-by-int.py > src/tests/datasets/mul-bigint-by-int.c

src/tests/datasets/montgomery-mul.c: ./src/tests/generators/montgomery-mul.py
	python src/tests/generators/montgomery-mul.py > src/tests/datasets/montgomery-mul.c

src/tests/datasets/mod-exp.c: ./src/tests/generators/mod-exp.py
	python src/tests/generators/mod-exp.py > src/tests/datasets/mod-exp.c


# Objects
tests/obj/bigint.o: src/bigint.c
	gcc -m32 -c -o tests/obj/bigint.o src/bigint.c -D_COMPUTER_VERSION

tests/obj/tests/add.o: src/tests/add.c src/tests/datasets/add.c
	gcc -m32 -c -o tests/obj/tests/add.o src/tests/add.c -D_COMPUTER_VERSION

tests/obj/tests/sub.o: src/tests/sub.c src/tests/datasets/sub.c
	gcc -m32 -c -o tests/obj/tests/sub.o src/tests/sub.c -D_COMPUTER_VERSION

tests/obj/tests/mul-bigint-by-int.o: src/tests/mul-bigint-by-int.c src/tests/datasets/mul-bigint-by-int.c
	gcc -m32 -c -o tests/obj/tests/mul-bigint-by-int.o src/tests/mul-bigint-by-int.c -D_COMPUTER_VERSION

tests/obj/tests/mul-int-by-int.o: src/tests/mul-int-by-int.c src/tests/datasets/mul-int-by-int.c
	gcc -m32 -c -o tests/obj/tests/mul-int-by-int.o src/tests/mul-int-by-int.c -D_COMPUTER_VERSION

tests/obj/tests/shift.o: src/tests/shift.c src/tests/datasets/add.c
	gcc -m32 -c -o tests/obj/tests/shift.o src/tests/shift.c -D_COMPUTER_VERSION

tests/obj/tests/montgomery-mul.o: src/tests/montgomery-mul.c src/tests/datasets/montgomery-mul.c
	gcc -m32 -c -o tests/obj/tests/montgomery-mul.o src/tests/montgomery-mul.c -D_COMPUTER_VERSION

tests/obj/tests/mod-exp.o: src/tests/mod-exp.c src/tests/datasets/mod-exp.c
	gcc -m32 -c -o tests/obj/tests/mod-exp.o src/tests/mod-exp.c -D_COMPUTER_VERSION

# Testing and debuging binaries
tests/bin/tests/add: tests/obj/tests/add.o tests/obj/bigint.o
	gcc -m32 -o tests/bin/tests/add tests/obj/tests/add.o tests/obj/bigint.o -D_COMPUTER_VERSION

tests/bin/tests/sub: tests/obj/tests/sub.o tests/obj/bigint.o
	gcc -m32 -o tests/bin/tests/sub tests/obj/tests/sub.o tests/obj/bigint.o -D_COMPUTER_VERSION

tests/bin/tests/mul-int-by-int: tests/obj/tests/mul-int-by-int.o tests/obj/bigint.o
	gcc -m32 -o tests/bin/tests/mul-int-by-int tests/obj/tests/mul-int-by-int.o tests/obj/bigint.o -D_COMPUTER_VERSION

tests/bin/tests/mul-bigint-by-int: tests/obj/tests/mul-bigint-by-int.o tests/obj/bigint.o
	gcc -m32 -o tests/bin/tests/mul-bigint-by-int tests/obj/tests/mul-bigint-by-int.o tests/obj/bigint.o -D_COMPUTER_VERSION

tests/bin/tests/shift: tests/obj/tests/shift.o tests/obj/bigint.o
	gcc -m32 -o tests/bin/tests/shift tests/obj/tests/shift.o tests/obj/bigint.o -D_COMPUTER_VERSION

tests/bin/tests/montgomery-mul: tests/obj/tests/montgomery-mul.o tests/obj/bigint.o
	gcc -m32 -o tests/bin/tests/montgomery-mul tests/obj/tests/montgomery-mul.o tests/obj/bigint.o -D_COMPUTER_VERSION

tests/bin/tests/mod-exp: tests/obj/tests/mod-exp.o tests/obj/bigint.o
	gcc -m32 -o tests/bin/tests/mod-exp tests/obj/tests/mod-exp.o tests/obj/bigint.o -D_COMPUTER_VERSION

# Testing
tests: tests/bin/tests/add tests/bin/tests/sub tests/bin/tests/mul-int-by-int tests/bin/tests/mul-bigint-by-int tests/bin/tests/shift tests/bin/tests/montgomery-mul tests/bin/tests/mod-exp
	./tests/bin/tests/add
	./tests/bin/tests/sub
	./tests/bin/tests/mul-int-by-int
	./tests/bin/tests/mul-bigint-by-int
#	./tests/bin/tests/shift
	./tests/bin/tests/montgomery-mul
	./tests/bin/tests/mod-exp


# Clean
clean:
	rm -f $(DATA)
	rm -f $(OBJ)
	rm -f $(BIN)

clean-datasets:
	rm -f $(DATA)


# Misc
.PHONY: clean clean-datasets tests 


