# RSA implementation and attack on Mbed
# Makefile
# @author Cyrille Toulet, <cyrille.toulet@linux.com>
# @author Benjamin Burnouf, <benjamin76360@gmail.com>

DATA  = src/tests/datasets/add.c
DATA += src/tests/datasets/sub.c
DATA += src/tests/datasets/mul-int-by-int.c
DATA += src/tests/datasets/mul-bigint-by-int.c
DATA += src/tests/datasets/mul-montgomery.c

OBJ   = tests/obj/bigint.o
OBJ  += tests/obj/tests/add.o
OBJ  += tests/obj/tests/sub.o
OBJ  += tests/obj/tests/mul-int-by-int.o
OBJ  += tests/obj/tests/mul-bigint-by-int.o
OBJ  += tests/obj/tests/shift.o
OBJ  += tests/obj/tests/mul-montgomery.o
OBJ  += tests/obj/tests/failed-mul-montgomery.o

BIN   = tests/bin/tests/add
BIN  += tests/bin/tests/sub
BIN  += tests/bin/tests/mul-int-by-int
BIN  += tests/bin/tests/mul-bigint-by-int
BIN  += tests/bin/tests/shift
BIN  += tests/bin/tests/mul-montgomery
BIN  += tests/bin/tests/failed-mul-montgomery


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

src/tests/datasets/mul-montgomery.c: ./src/tests/generators/mul-montgomery.py
	python src/tests/generators/mul-montgomery.py > src/tests/datasets/mul-montgomery.c


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

tests/obj/tests/mul-montgomery.o: src/tests/mul-montgomery.c src/tests/datasets/mul-montgomery.c
	gcc -m32 -c -o tests/obj/tests/mul-montgomery.o src/tests/mul-montgomery.c -D_COMPUTER_VERSION

tests/obj/tests/failed-mul-montgomery.o: src/tests/failed-mul-montgomery.c
	gcc -m32 -c -o tests/obj/tests/failed-mul-montgomery.o src/tests/failed-mul-montgomery.c -D_COMPUTER_VERSION


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

tests/bin/tests/mul-montgomery: tests/obj/tests/mul-montgomery.o tests/obj/bigint.o
	gcc -m32 -o tests/bin/tests/mul-montgomery tests/obj/tests/mul-montgomery.o tests/obj/bigint.o -D_COMPUTER_VERSION

tests/bin/tests/failed-mul-montgomery: tests/obj/tests/failed-mul-montgomery.o tests/obj/bigint.o
	gcc -m32 -o tests/bin/tests/failed-mul-montgomery tests/obj/tests/failed-mul-montgomery.o tests/obj/bigint.o -D_COMPUTER_VERSION


# Testing
tests: tests/bin/tests/add tests/bin/tests/sub tests/bin/tests/mul-int-by-int tests/bin/tests/mul-bigint-by-int tests/bin/tests/shift tests/bin/tests/mul-montgomery
	./tests/bin/tests/add
	./tests/bin/tests/sub
	./tests/bin/tests/mul-int-by-int
	./tests/bin/tests/mul-bigint-by-int
	./tests/bin/tests/shift
	./tests/bin/tests/mul-montgomery


# Debuging
debug: tests/bin/tests/failed-mul-montgomery
	./tests/bin/tests/failed-mul-montgomery
	python src/debug/montgomery.py


# Clean
clean:
	rm -f $(DATA)
	rm -f $(OBJ)
	rm -f $(BIN)


# Misc
.PHONY: clean tests debug


