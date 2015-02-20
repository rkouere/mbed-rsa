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

OBJ   = pc/obj/bigint.o
OBJ  += pc/obj/tests/add.o
OBJ  += pc/obj/tests/sub.o
OBJ  += pc/obj/tests/mul-int-by-int.o
OBJ  += pc/obj/tests/mul-bigint-by-int.o
OBJ  += pc/obj/tests/montgomery-mul.o
OBJ  += pc/obj/tests/mod-exp.o
OBJ  += mbed/obj/bigint.o

BIN   = pc/bin/tests/add
BIN  += pc/bin/tests/sub
BIN  += pc/bin/tests/mul-int-by-int
BIN  += pc/bin/tests/mul-bigint-by-int
BIN  += pc/bin/tests/montgomery-mul
BIN  += pc/bin/tests/mod-exp
BIN  += mbed/bin/test-add


RFLPC = mbed/lib/rflpc
RFLPC_CFLAGS = $(shell $(RFLPC)/rflpc-config --cflags)

# Global rule
all: pc/obj/bigint.o mbed/obj/bigint.o


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
pc/obj/bigint.o: src/bigint.c
	gcc -m32 -c -o pc/obj/bigint.o src/bigint.c -D_COMPUTER_VERSION

pc/obj/tests/add.o: src/tests/add.c src/tests/datasets/add.c
	gcc -m32 -c -o pc/obj/tests/add.o src/tests/add.c -D_COMPUTER_VERSION

pc/obj/tests/sub.o: src/tests/sub.c src/tests/datasets/sub.c
	gcc -m32 -c -o pc/obj/tests/sub.o src/tests/sub.c -D_COMPUTER_VERSION

pc/obj/tests/mul-bigint-by-int.o: src/tests/mul-bigint-by-int.c src/tests/datasets/mul-bigint-by-int.c
	gcc -m32 -c -o pc/obj/tests/mul-bigint-by-int.o src/tests/mul-bigint-by-int.c -D_COMPUTER_VERSION

pc/obj/tests/mul-int-by-int.o: src/tests/mul-int-by-int.c src/tests/datasets/mul-int-by-int.c
	gcc -m32 -c -o pc/obj/tests/mul-int-by-int.o src/tests/mul-int-by-int.c -D_COMPUTER_VERSION

pc/obj/tests/shift.o: src/tests/shift.c src/tests/datasets/add.c
	gcc -m32 -c -o pc/obj/tests/shift.o src/tests/shift.c -D_COMPUTER_VERSION

pc/obj/tests/montgomery-mul.o: src/tests/montgomery-mul.c src/tests/datasets/montgomery-mul.c
	gcc -m32 -c -o pc/obj/tests/montgomery-mul.o src/tests/montgomery-mul.c -D_COMPUTER_VERSION

pc/obj/tests/mod-exp.o: src/tests/mod-exp.c src/tests/datasets/mod-exp.c
	gcc -m32 -c -o pc/obj/tests/mod-exp.o src/tests/mod-exp.c -D_COMPUTER_VERSION

mbed/obj/bigint.o: src/bigint.c
	arm-none-eabi-gcc $(RFLPC_CFLAGS) -c -o mbed/obj/bigint.o src/bigint.c


# Compilated binaries
pc/bin/tests/add: pc/obj/tests/add.o pc/obj/bigint.o
	gcc -m32 -o pc/bin/tests/add pc/obj/tests/add.o pc/obj/bigint.o -D_COMPUTER_VERSION

pc/bin/tests/sub: pc/obj/tests/sub.o pc/obj/bigint.o
	gcc -m32 -o pc/bin/tests/sub pc/obj/tests/sub.o pc/obj/bigint.o -D_COMPUTER_VERSION

pc/bin/tests/mul-int-by-int: pc/obj/tests/mul-int-by-int.o pc/obj/bigint.o
	gcc -m32 -o pc/bin/tests/mul-int-by-int pc/obj/tests/mul-int-by-int.o pc/obj/bigint.o -D_COMPUTER_VERSION

pc/bin/tests/mul-bigint-by-int: pc/obj/tests/mul-bigint-by-int.o pc/obj/bigint.o
	gcc -m32 -o pc/bin/tests/mul-bigint-by-int pc/obj/tests/mul-bigint-by-int.o pc/obj/bigint.o -D_COMPUTER_VERSION

pc/bin/tests/shift: pc/obj/tests/shift.o pc/obj/bigint.o
	gcc -m32 -o pc/bin/tests/shift pc/obj/tests/shift.o pc/obj/bigint.o -D_COMPUTER_VERSION

pc/bin/tests/montgomery-mul: pc/obj/tests/montgomery-mul.o pc/obj/bigint.o
	gcc -m32 -o pc/bin/tests/montgomery-mul pc/obj/tests/montgomery-mul.o pc/obj/bigint.o -D_COMPUTER_VERSION

pc/bin/tests/mod-exp: pc/obj/tests/mod-exp.o pc/obj/bigint.o
	gcc -m32 -o pc/bin/tests/mod-exp pc/obj/tests/mod-exp.o pc/obj/bigint.o -D_COMPUTER_VERSION

mbed/bin/test-add: mbed/obj/bigint.o src/mbed/test-add/main.c
	@(cd src/mbed/test-add/ && $(MAKE))


# PC tests binaries
tests: pc/bin/tests/add pc/bin/tests/sub pc/bin/tests/mul-int-by-int pc/bin/tests/mul-bigint-by-int pc/bin/tests/montgomery-mul pc/bin/tests/mod-exp
	./pc/bin/tests/add
	./pc/bin/tests/sub
	./pc/bin/tests/mul-int-by-int
	./pc/bin/tests/mul-bigint-by-int
	./pc/bin/tests/montgomery-mul
	./pc/bin/tests/mod-exp


# Mbed binaries
mbed: rflpc mbed/bin/test-add


# RFLPC rules
rflpc:
	@(cd mbed/lib/rflpc && $(MAKE))


program:
	make -C src/mbed/test-add/ program

reset: 
	make -C src/mbed/test-add/ reset

# Clean
clean:
	@(cd mbed/lib/rflpc && $(MAKE) clean)
	rm -f $(DATA)
	rm -f $(OBJ)
	rm -f $(BIN)

clean-datasets:
	rm -f $(DATA)


# Misc
.PHONY: clean clean-datasets program reset

