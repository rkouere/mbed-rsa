#!/usr/bin/env python

# RSA implementation and attack on Mbed
# Data generator for montgomery_exponentiation testing
# @author Cyrille Toulet, <cyrille.toulet@linux.com>
# @author Benjamin Burnouf, <benjamin76360@gmail.com>

import random
import string
from datetime import datetime
from gmpy2 import invert
from fractions import gcd

# Number of tests
set_count = 10

def generate_prime(base):
    output = random.randint(0,base)
    while gcd(output,base) != 1 : 
        output = random.randint(0,base)
    return output

def generate_c_header():
    '''
    Generate the C file header
    @return The file header
    '''
    output = "/**\n"
    output = output + " * RSA implementation and attack on Mbed\n"
    output = output + " * Data set used to test montgomery_exponentiation function in bigint library\n"
    output = output + " * Generated at compilation the " + str(datetime.now()) + "\n"
    output = output + " * @author Cyrille Toulet, <cyrille.toulet@linux.com>\n"
    output = output + " * @author Benjamin Burnouf, <benjamin76360@gmail.com>\n"
    output = output + " **/\n\n"
    output = output + "#include \"../../bigint.h\"\n\n"
    output = output + "#define TEST_MOD_EXP_COUNT " + str(set_count) + "u\n\n"
    return output


def generate_c_array(x):
    '''
    Generate a C mbed_bigint from python big int
    @return The static array representing mbed_bigint in C
    '''
    str_x = str(hex(x))

    if str_x[len(str_x) - 1: len(str_x)] == "L":
        tmp2 = str_x[2:len(str_x) - 1]
    else:
        tmp2 = str_x[2:len(str_x)]

    tmp1 = ""
    counter = 34
    output = "{"

    while len(tmp2) > 8:
        counter = counter - 1
        tmp1 = tmp2[len(tmp2) - 8: len(tmp2)]
        tmp2 = tmp2[0 : len(tmp2) - 8]
        if counter == 33:
            output = output + "0x" + tmp1 + "u"
        else:
            output = output + ", 0x" + tmp1 + "u"

    if len(tmp2) > 0:
        counter = counter - 1
        padding_size = 8 - len(tmp2)
        if counter == 33:
            output = output + "0x" + string.rjust(tmp2, 8, '0') + "u"
        else:
            output = output + ", 0x" + string.rjust(tmp2, 8, '0') + "u"

    while counter > 0:
        output = output + ", 0x00000000u"
        counter = counter - 1

    output = output + "}"

    return output


def main():
    '''
    Run the main application
    '''
    code = generate_c_header()

    tab_x = ""
    tab_y = ""
    tab_m = ""
    tab_mp = ""

    i = 0
    while i < set_count:
	b = pow(2, 32)
	n = 32

        m = (random.randint(0, 1 << 1023 - 1) << 1) | 1
	mp = -invert(m, pow(2, 32)) % b

        x = random.randint(0, m - 1)

	r = pow(b, n)
	rm = r % m

	r2 = pow(r, 2) % m
 
        if i == 0:
            tab_x = tab_x + "\t" + generate_c_array(x)
        else:
            tab_x = tab_x + ",\n\t" + generate_c_array(x)
        
        if i == 0:
            tab_y = tab_y + "\t" + generate_c_array(y)
        else:
            tab_y = tab_y + ",\n\t" + generate_c_array(y)

	if i == 0:
            tab_m = tab_m + "\t" + generate_c_array(m)
        else:
            tab_m = tab_m + ",\n\t" + generate_c_array(m)
	
        if i == 0:
            tab_mp = tab_mp + "\t" + str(hex(mp)) + "u"
        else:
            tab_mp = tab_mp + ",\n\t" + str(hex(mp)) + "u"

        i = i + 1

    code = code + "mbed_int test_mont_mul_dataset_modulus[TEST_MOD_EXP_COUNT][BIGINT_SIZE + 2] = {\n" + tab_m + "\n};\n"
    code = code + "mbed_int test_mont_mul_dataset_modulus_invert[TEST_MOD_EXP_COUNT] = {\n" + tab_mp + "\n};\n"

    code = code + "mbed_int test_mont_mul_dataset_x[TEST_MOD_EXP_COUNT][BIGINT_SIZE + 2] = {\n" + tab_x + "\n};\n"
    code = code + "mbed_int test_mont_mul_dataset_y[TEST_MOD_EXP_COUNT][BIGINT_SIZE + 2] = {\n" + tab_y + "\n};\n"

    print code


main()
