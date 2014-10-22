#!/usr/bin/env python

# RSA implementation and attack on Mbed
# Data generator for bgi_mul_int testing
# @author Cyrille Toulet, <cyrille.toulet@gmail.com>
# @author Benjamin Burnouf, <benjamin76360@gmail.com>

import random
import string
from datetime import datetime

# Number of tests
set_count = 10

def generate_c_header():
    '''
    Generate the C file header
    @return The file header
    '''
    output = "/**\n"
    output = output + " * RSA implementation and attack on Mbed\n"
    output = output + " * Data set used to test bgi_mul_bigint_by_int function in bigint library\n"
    output = output + " * Generated at compilation the " + str(datetime.now()) + "\n"
    output = output + " * @author Cyrille Toulet, <cyrille.toulet@gmail.com>\n"
    output = output + " * @author Benjamin Burnouf, <benjamin76360@gmail.com>\n"
    output = output + " **/\n\n"
    output = output + "#include \"bigint.h\"\n\n"
    output = output + "#define TEST_MUL_BIGINT_BY_INT_COUNT " + str(set_count) + "u\n\n"
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
    counter = 33
    output = "{"

    while len(tmp2) > 8:
        counter = counter - 1
        tmp1 = tmp2[len(tmp2) - 8: len(tmp2)]
        tmp2 = tmp2[0 : len(tmp2) - 8]
        if counter == 32:
            output = output + "0x" + tmp1 + "u"
        else:
            output = output + ", 0x" + tmp1 + "u"

    if len(tmp2) > 0:
        counter = counter - 1
        padding_size = 8 - len(tmp2)
        if counter == 32:
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
    tab_r = ""

    i = 0
    while i < set_count:
        x = random.randint(0, pow(pow(2, 32), 32))
        y = random.randint(0, pow(2, 32))
        r = x * y
        
        if i == 0:
            tab_x = tab_x + "\t" + generate_c_array(x)
        else:
            tab_x = tab_x + ",\n\t" + generate_c_array(x)
        
        if i == 0:
            tab_y = tab_y + str(hex(y))
        else:
            tab_y = tab_y + ", " + str(hex(y))
        
        if i == 0:
            tab_r = tab_r + "\t" + generate_c_array(r)
        else:
            tab_r = tab_r + ",\n\t" + generate_c_array(r)

        i = i + 1


    code = code + "mbed_int test_mul_bigint_by_int_dataset_x[TEST_MUL_BIGINT_BY_INT_COUNT][BIGINT_SIZE + 1] = {\n" + tab_x + "\n};\n"
    code = code + "mbed_int test_mul_bigint_by_int_dataset_y[TEST_MUL_BIGINT_BY_INT_COUNT] = {" + tab_y + "};\n"
    code = code + "mbed_int test_mul_bigint_by_int_dataset_r[TEST_MUL_BIGINT_BY_INT_COUNT][BIGINT_SIZE + 1] = {\n" + tab_r + "\n};\n"

    print code


main()
