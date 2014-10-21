#!/usr/bin/env python

import random
import string

set_count = 10

def generate_c_header():
    '''
    '''
    output = "#include \"bigint.h\"\n\n#define TEST_ADD_COUNT " + str(set_count) + "u\n\n"
    return output


def generate_c_array(x):
    '''
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
            output = output + "0x" + tmp1
        else:
            output = output + ", 0x" + tmp1

    if len(tmp2) > 0:
        counter = counter - 1
        padding_size = 8 - len(tmp2)
        if counter == 32:
            output = output + "0x" + string.rjust(tmp2, 8, '0')
        else:
            output = output + ", 0x" + string.rjust(tmp2, 8, '0')

    while counter > 0:
        output = output + ", 0x00000000"
        counter = counter - 1

    output = output + "}"

    return output


def main():
    '''
    '''
    code = generate_c_header()

    i = 0
    code = code + "mbed_int test_add_dataset[TEST_ADD_COUNT][3][BIGINT_SIZE + 1] = {\n"

    while i < set_count:
        x = random.randint(0, pow(pow(2, 32), 32))
        y = random.randint(0, pow(pow(2, 32), 32))
        s = x + y

        code = code + "\t{\n\t\t"
        code = code + generate_c_array(x)
        code = code + ", \n\t\t"
        code = code + generate_c_array(y)
        code = code + ", \n\t\t"
        code = code + generate_c_array(s)
    
        if i == (set_count - 1):
            code = code + "\n\t}\n"
        else:
            code = code + "\n\t},\n"
    
        i = i + 1

    code = code + "};"

    print code


main()
