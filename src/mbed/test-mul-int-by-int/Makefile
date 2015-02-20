# RSA implementation and attack on Mbed
# MBED Sub Makefile
# @author Cyrille Toulet, <cyrille.toulet@linux.com>
# @author Benjamin Burnouf, <benjamin76360@gmail.com>

# The binary name
OUTPUT_NAME = ../../../mbed/bin/test-mul-int-by-int

# The source files 
SRC         = $(wildcard *.c)

# The objects files
OBJS        = $(SRC:.c=.o)
OBJS       += ../../../mbed/obj/bigint.o

# The rflpc lib directory
RFLPC_DIR   = ../../../mbed/lib/rflpc

# Include rflpc Makefile template
include $(RFLPC_DIR)/Makefile.in
