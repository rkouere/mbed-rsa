# RSA implementation and attack on Mbed
# Makefile
# @author Cyrille Toulet, <cyrille.toulet@gmail.com>
# @author Benjamin Burnouf, <benjamin76360@gmail.com>

COMPUTER_DATA  = src/test-add-dataset.c
COMPUTER_DATA += src/test-sub-dataset.c
COMPUTER_DATA += src/test-mul-int-by-int-dataset.c
COMPUTER_DATA += src/test-mul-bigint-by-int-dataset.c
COMPUTER_DATA += src/test-mul-montgomery-dataset.c

COMPUTER_OBJ   = computer/obj/bigint.o
COMPUTER_OBJ  += computer/obj/test-add.o
COMPUTER_OBJ  += computer/obj/test-sub.o
COMPUTER_OBJ  += computer/obj/test-mul-int-by-int.o
COMPUTER_OBJ  += computer/obj/test-mul-bigint-by-int.o
COMPUTER_OBJ  += computer/obj/test-shift.o
COMPUTER_OBJ  += computer/obj/test-mul-montgomery.o

COMPUTER_BIN   = computer/bin/test-add
COMPUTER_BIN  += computer/bin/test-sub
COMPUTER_BIN  += computer/bin/test-mul-int-by-int
COMPUTER_BIN  += computer/bin/test-mul-bigint-by-int
COMPUTER_BIN  += computer/bin/test-shift
COMPUTER_BIN  += computer/bin/test-mul-montgomery

# Generic
all: $(COMPUTER_BIN)

# Data sets
src/test-add-dataset.c: ./src/test-add-dataset-generator.py
	python src/test-add-dataset-generator.py > src/test-add-dataset.c

src/test-sub-dataset.c: ./src/test-sub-dataset-generator.py
	python src/test-sub-dataset-generator.py > src/test-sub-dataset.c

src/test-mul-int-by-int-dataset.c: ./src/test-mul-int-by-int-dataset-generator.py
	python src/test-mul-int-by-int-dataset-generator.py > src/test-mul-int-by-int-dataset.c

src/test-mul-bigint-by-int-dataset.c: ./src/test-mul-bigint-by-int-dataset-generator.py
	python src/test-mul-bigint-by-int-dataset-generator.py > src/test-mul-bigint-by-int-dataset.c

src/test-mul-montgomery-dataset.c: ./src/test-mul-montgomery-dataset-generator.py
	python src/test-mul-montgomery-dataset-generator.py > src/test-mul-montgomery-dataset.c

# Objects
computer/obj/bigint.o: src/bigint.c
	gcc -m32 -c -o computer/obj/bigint.o src/bigint.c -D_COMPUTER_VERSION

computer/obj/test-add.o: src/test-add.c src/test-add-dataset.c
	gcc -m32 -c -o computer/obj/test-add.o src/test-add.c -D_COMPUTER_VERSION

computer/obj/test-sub.o: src/test-sub.c src/test-sub-dataset.c
	gcc -m32 -c -o computer/obj/test-sub.o src/test-sub.c -D_COMPUTER_VERSION

computer/obj/test-mul-bigint-by-int.o: src/test-mul-bigint-by-int.c src/test-mul-bigint-by-int-dataset.c
	gcc -m32 -c -o computer/obj/test-mul-bigint-by-int.o src/test-mul-bigint-by-int.c -D_COMPUTER_VERSION

computer/obj/test-mul-int-by-int.o: src/test-mul-int-by-int.c src/test-mul-int-by-int-dataset.c
	gcc -m32 -c -o computer/obj/test-mul-int-by-int.o src/test-mul-int-by-int.c -D_COMPUTER_VERSION

computer/obj/test-shift.o: src/test-shift.c src/test-add-dataset.c
	gcc -m32 -c -o computer/obj/test-shift.o src/test-shift.c -D_COMPUTER_VERSION

computer/obj/test-mul-montgomery.o: src/test-mul-montgomery.c src/test-mul-montgomery-dataset.c
	gcc -m32 -c -o computer/obj/test-mul-montgomery.o src/test-mul-montgomery.c -D_COMPUTER_VERSION

# Binaries
computer/bin/test-add: computer/obj/test-add.o computer/obj/bigint.o
	gcc -m32 -o computer/bin/test-add computer/obj/test-add.o computer/obj/bigint.o -D_COMPUTER_VERSION

computer/bin/test-sub: computer/obj/test-sub.o computer/obj/bigint.o
	gcc -m32 -o computer/bin/test-sub computer/obj/test-sub.o computer/obj/bigint.o -D_COMPUTER_VERSION

computer/bin/test-mul-int-by-int: computer/obj/test-mul-int-by-int.o computer/obj/bigint.o
	gcc -m32 -o computer/bin/test-mul-int-by-int computer/obj/test-mul-int-by-int.o computer/obj/bigint.o -D_COMPUTER_VERSION

computer/bin/test-mul-bigint-by-int: computer/obj/test-mul-bigint-by-int.o computer/obj/bigint.o
	gcc -m32 -o computer/bin/test-mul-bigint-by-int computer/obj/test-mul-bigint-by-int.o computer/obj/bigint.o -D_COMPUTER_VERSION

computer/bin/test-shift: computer/obj/test-shift.o computer/obj/bigint.o
	gcc -m32 -o computer/bin/test-shift computer/obj/test-shift.o computer/obj/bigint.o -D_COMPUTER_VERSION

computer/bin/test-mul-montgomery: computer/obj/test-mul-montgomery.o computer/obj/bigint.o
	gcc -m32 -o computer/bin/test-mul-montgomery computer/obj/test-mul-montgomery.o computer/obj/bigint.o -D_COMPUTER_VERSION

# Tests
tests: computer/bin/test-add computer/bin/test-sub computer/bin/test-mul-int-by-int computer/bin/test-mul-bigint-by-int computer/bin/test-shift computer/bin/test-mul-montgomery
	./computer/bin/test-add
	./computer/bin/test-sub
	./computer/bin/test-mul-int-by-int
	./computer/bin/test-mul-bigint-by-int
#	./computer/bin/test-shift
	./computer/bin/test-mul-montgomery

# Misc
.PHONY: clean

clean:
	rm -f $(COMPUTER_DATA)
	rm -f $(COMPUTER_OBJ)
	rm -f $(COMPUTER_BIN)


