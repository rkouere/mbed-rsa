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
    output = output + " * Data set used to test bgi_mul_int_by_int function in bigint library\n"
    output = output + " * Generated at compilation the " + str(datetime.now()) + "\n"
    output = output + " * @author Cyrille Toulet, <cyrille.toulet@gmail.com>\n"
    output = output + " * @author Benjamin Burnouf, <benjamin76360@gmail.com>\n"
    output = output + " **/\n\n"
    output = output + "#include \"bigint.h\"\n\n"
    output = output + "#define TEST_MUL_INT_BY_INT_COUNT " + str(set_count) + "u\n\n"
    return output


def main():
    '''
    Run the main application
    '''
    code = generate_c_header()
        
    tab_x = ""
    tab_y = ""
    tab_a = ""
    tab_b = ""

    i = 0
    while i < set_count:
        x = random.randint(0, pow(2, 32))
        y = random.randint(0, pow(2, 32))
        r = x * y
        
        tmp = hex(r)

        if tmp[len(tmp) - 1] == 'L':
            tmp = tmp[2:len(tmp) - 1]
        else:
            tmp = tmp[2:len(tmp)]

        tmp = string.rjust(str(tmp), 16, '0')
        
        if i == 0:
            tab_x = tab_x + str(hex(x))
        else:
            tab_x = tab_x + ", " + str(hex(x))
        
        if i == 0:
            tab_y = tab_y + str(hex(y))
        else:
            tab_y = tab_y + ", " + str(hex(y))
        
        if i == 0:
            tab_a = tab_a + "0x" + tmp[0:8] + "u"
        else:
            tab_a = tab_a + ", " + "0x" + tmp[0:8] + "u"
        
        if i == 0:
            tab_b = tab_b + "0x" + tmp[8:16] + "u"
        else:
            tab_b = tab_b + ", " + "0x" + tmp[8:16] + "u"
    
        i = i + 1

    code = code + "mbed_int test_mul_int_by_int_dataset_x[TEST_MUL_INT_BY_INT_COUNT] = {" + tab_x + "};\n"
    code = code + "mbed_int test_mul_int_by_int_dataset_y[TEST_MUL_INT_BY_INT_COUNT] = {" + tab_y + "};\n"
    code = code + "mbed_int test_mul_int_by_int_dataset_a[TEST_MUL_INT_BY_INT_COUNT] = {" + tab_a + "};\n"
    code = code + "mbed_int test_mul_int_by_int_dataset_b[TEST_MUL_INT_BY_INT_COUNT] = {" + tab_b + "};\n\n"

    print code


main()
