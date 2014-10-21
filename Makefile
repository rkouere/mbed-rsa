# RSA implementation and attack on Mbed
# Makefile
# @author Cyrille Toulet, <cyrille.toulet@gmail.com>

COMPUTER_DATA  = src/test-add-dataset.c
COMPUTER_OBJ   = computer/obj/bigint.o
COMPUTER_OBJ   = computer/obj/test-add.o
COMPUTER_BIN   = computer/bin/test-add

# Generic
all: computer

computer: $(COMPUTER_DATA) $(COMPUTER_OBJ) $(COMPUTER_BIN)

# Data sets
src/test-add-dataset.c: ./src/test-add-dataset-generator.py
	./src/test-add-dataset-generator.py > src/test-add-dataset.c

# Objects
computer/obj/bigint.o: src/bigint.c
	gcc -m32 -c -o computer/obj/bigint.o src/bigint.c -D_COMPUTER_VERSION

computer/obj/test-add.o: src/test-add.c
	gcc -m32 -c -o computer/obj/test-add.o src/test-add.c -D_COMPUTER_VERSION

# Binaries
computer/bin/test-add: computer/obj/test-add.o computer/obj/bigint.o
	gcc -m32 -o computer/bin/test-add computer/obj/test-add.o computer/obj/bigint.o -D_COMPUTER_VERSION

# Misc
.PHONY: computer clean

clean:
	rm -f $(COMPUTER_DATA)
	rm -f computer/obj/*.o computer/bin/*


