/**
 * RSA implementation and attack on Mbed
 * Big integers library - Tests for bgi_mul_bigint_by_int function
 * @author Cyrille Toulet, <cyrille.toulet@gmail.com>
 * @author Benjamin Burnouf, <benjamin76360@gmail.com>
 */

#include <stdlib.h>
#include <stdio.h>
#include "bigint.h"
#include "test-mul-montgomery-dataset.c"

mbed_int main()
{
    mbed_int i = 0;
    mbed_int dest;

    while (i < TEST_MONT_MUL_COUNT)
    {
        dest = 0;
        bgi_mul(&dest, test_mont_mul_dataset_x[i], test_mont_mul_dataset_x[i], TEST_MONT_MUL_MODULUS , TEST_MONT_MUL_MODULUS_INVERSE);

        if (dest, test_mont_mul_dataset_y[i] != 0)
        {
            printf("[FAIL] Test bgi_mul %d / %d", i + 1, TEST_MONT_MUL_COUNT);
            printf("\nNumber 1        : ");
            bgi_print(test_mont_mul_dataset_x[i]);
            printf("\nExpected result : ");
            printf("%8x", test_mont_mul_dataset_y[i]);
            printf("\nReceived result : ");
            printf("%8x", dest);
            putchar('\n');
            exit(EXIT_FAILURE);
        }

        printf("[PASS] Test bgi_mul %d / %d\n", i + 1, TEST_MONT_MUL_COUNT);
        i++;
    }

    exit(EXIT_SUCCESS);
}
