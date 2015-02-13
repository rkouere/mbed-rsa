/**
 * RSA implementation and attack on Mbed
 * Big integers library - Tests for bgi_mul_bigint_by_int function
 * @author Cyrille Toulet, <cyrille.toulet@linux.com>
 * @author Benjamin Burnouf, <benjamin76360@gmail.com>
 */

#include <stdlib.h>
#include <stdio.h>
#include "../bigint.h"
#include "datasets/montgomery-mul.c"

mbed_int main()
{
    long int i = 0;
    mbed_bigint dest;

    while (i < TEST_MONT_MUL_COUNT)
    {
        bgi_init(dest);

        bgi_montgomery_mul(dest, test_mont_mul_dataset_x[i], 
            test_mont_mul_dataset_x[i], test_mont_mul_dataset_modulus[i], 
            test_mont_mul_dataset_modulus_invert[i]);

        if (bgi_cmp(dest, test_mont_mul_dataset_y[i]) != 0)
        {
            printf("[FAIL] Test bgi_mul %d / %d", i + 1, TEST_MONT_MUL_COUNT);

            printf("\nNumber x        : ");
            bgi_print(test_mont_mul_dataset_x[i]);
            printf("\nNumber y        : ");
            bgi_print(test_mont_mul_dataset_x[i]);
            printf("\nModulus         : ");
            bgi_print(test_mont_mul_dataset_modulus[i]);
            printf("\nExpected result : ");
            bgi_print(test_mont_mul_dataset_y[i]);
            printf("\nReceived result : ");
            bgi_print(dest);
            putchar('\n');

            exit(EXIT_FAILURE);
        }
	else
            printf("[PASS] Test bgi_mul %d / %d\n", i + 1, TEST_MONT_MUL_COUNT);

        i++;
    }

    exit(EXIT_SUCCESS);
}
