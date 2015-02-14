/**
 * RSA implementation and attack on Mbed
 * Big integers library - Tests for bgi_mul_int_by_int function
 * @author Cyrille Toulet, <cyrille.toulet@linux.com>
 * @author Benjamin Burnouf, <benjamin76360@gmail.com>
 */

#include <stdlib.h>
#include <stdio.h>
#include "../bigint.h"
#include "datasets/mul-int-by-int.c"

mbed_int main()
{
    mbed_int i = 0;
    mbed_int a;
    mbed_int b;

    while (i < TEST_MUL_INT_BY_INT_COUNT)
    {
        bgi_mul_int_by_int(&a, &b, test_mul_int_by_int_dataset_x[i], test_mul_int_by_int_dataset_y[i]);

        if (
            (a != test_mul_int_by_int_dataset_a[i])
            || (b != test_mul_int_by_int_dataset_b[i])
        )
        {
            printf("[FAIL] Test bgi_mul_int_by_int %d / %d", i + 1, TEST_MUL_INT_BY_INT_COUNT);

            printf("\nNumber 1        : %x", test_mul_int_by_int_dataset_x[i]);
            printf("\nNumber 2        : %x", test_mul_int_by_int_dataset_y[i]);
            printf("\nExpected result : a = %8x, b = %8x", test_mul_int_by_int_dataset_a[i], test_mul_int_by_int_dataset_b[i]);
            printf("\nReceived result : a = %8x, b = %8x\n", a, b);
        }

        printf("[PASS] Test bgi_mul_int_by_int %d / %d\n", i + 1, TEST_MUL_INT_BY_INT_COUNT);

        i++;
    }

    exit(EXIT_SUCCESS);
}
