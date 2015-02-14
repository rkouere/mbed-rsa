/**
 * RSA implementation and attack on Mbed
 * Big integers library - Tests for bgi_add function
 * @author Cyrille Toulet, <cyrille.toulet@linux.com>
 * @author Benjamin Burnouf, <benjamin76360@gmail.com>
 */

#include <stdlib.h>
#include <stdio.h>
#include "../bigint.h"
#include "datasets/add.c"

mbed_int main()
{
    mbed_int i = 0;
    mbed_bigint dest;

    while (i < TEST_ADD_COUNT)
    {
        bgi_init(dest);
        bgi_add(dest, test_add_dataset_x[i], test_add_dataset_y[i]);

        if (bgi_cmp(dest, test_add_dataset_r[i]) != 0)
        {
            printf("[FAIL] Test bgi_add %d / %d", i + 1, TEST_ADD_COUNT);

            printf("\nNumber 1        : ");
            bgi_print(test_add_dataset_x[i]);
            printf("\nNumber 2        : ");
            bgi_print(test_add_dataset_y[i]);
            printf("\nExpected result : ");
            bgi_print(test_add_dataset_r[i]);
            printf("\nReceived result : ");
            bgi_print(dest);

            putchar('\n');
        }

        printf("[PASS] Test bgi_add %d / %d\n", i + 1, TEST_ADD_COUNT);

        i++;
    }

    exit(EXIT_SUCCESS);
}
