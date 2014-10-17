# RSA implementation and attack on Mbed
# Makefile
# @author Cyrille Toulet, <cyrille.toulet@gmail.com>

OBJ  = obj/bigint.o


all: $(OBJ)

obj/bigint.o: src/bigint.c
	gcc -c -o obj/bigint.o src/bigint.c

.PHONY: clean

clean:
	rm -f obj/*.o bin/*


