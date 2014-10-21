#!/usr/bin/env python

import random
import string

set_count = 10

def generate_c_header():
    '''
    '''
    output = "#include \"bigint.h\"\n\n#define TEST_ADD_COUNT " + str(set_count) + "\n\n"
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
    counter = 32
    output = "{"

    while len(tmp2) > 8:
        counter = counter - 1
        tmp1 = tmp2[len(tmp2) - 8: len(tmp2)]
        tmp2 = tmp2[0 : len(tmp2) - 8]
        if counter == 31:
            output = output + "0x" + tmp1
        else:
            output = output + ", 0x" + tmp1

    if len(tmp2) > 0:
        counter = counter - 1
        padding_size = 8 - len(tmp2)
        if counter == 31:
            output = output + "0x" + string.rjust(tmp2, 8, '0')
        else:
            output = output + ", 0x" + string.rjust(tmp2, 8, '0')

    while counter > 0:
        output = output + ", 0x" + "00000000"
        counter = counter - 1

    output = output + "}"

    return output


def main():
    '''
    '''
    code = generate_c_header()

    i = 0
    code = code + "mbed_int test_add_dataset[BIGINT_SIZE][3][" + str(set_count) + "] = {\n"

    while i < set_count:
#        x = random.randint(0, pow(pow(2, 32), 32))
#        y = random.randint(0, pow(pow(2, 32), 32))
#        s = x + y
        x = 0xba2527ce3c48b70a11f3b5d5b34849de8d0d88f74b2cecd335c2ff105f0e14b30c4321fb45fb6c5fcee97fe0f9cbb860ff6f047cc5b6aa9c773372405439f9c7988f8eec4e89568fd7746fa2a9f401021434c4c5a2caf0d661ad50166943ef713b2852860ec26052ae904db3a78a2e7dff38fca9a146d5b69a76e45b659c8a38
        y = 0x852da64c9c4ec29165feacbde6274baab3b086376460995d8ed36a139419bb017bd5c76b0d36ceb027663d896367ee2b4a0facf82b11505ee03285e94c930bf3f3e5d9e0299bef113fde2aefd2a56fda249df5fbe593cd80a73a8b71a8311fa61f92b25fdeff5d106bba523b3b088abf541b5a8ec1be648006aa1e4399586194
        s = 0x13f52ce1ad897799b77f26293996f958940be0f2eaf8d8630c4966923f327cfb48818e96653323b0ff64fbd6a5d33a68c497eb174f0c7fafb5765f829a0cd05bb8c7568cc782545a117529a927c9970dc38d2bac1885ebe5708e7db8811750f175abb04e5edc1bd631a4a9feee292b93d5354573863053a36a121029efef4ebcc

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

    code = code + "\n};"

    print code


main()
