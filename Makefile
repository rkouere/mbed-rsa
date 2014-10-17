# RSA implementation and attack on Mbed
# Makefile
# @author Cyrille Toulet, <cyrille.toulet@gmail.com>

COMPUTER_OBJ  = computer/obj/bigint.o

all: computer

computer: $(COMPUTER_OBJ)

computer/obj/bigint.o: src/bigint.c
	gcc -m32 -c -o computer/obj/bigint.o src/bigint.c -D_COMPUTER_VERSION

.PHONY: computer clean

clean:
	rm -f computer/obj/*.o computer/bin/*


