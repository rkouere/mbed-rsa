/**
 * RSA implementation and attack on Mbed
 * Big integers library - Tests for bgi_sub function
 * @author Cyrille Toulet, <cyrille.toulet@linux.com>
 * @author Benjamin Burnouf, <benjamin76360@gmail.com>
 */

#include <stdlib.h>
#include <stdio.h>
#include "../bigint.h"
#include "datasets/sub.c"

mbed_int main()
{
    mbed_int i = 0;
    mbed_bigint dest;

    while (i < TEST_SUB_COUNT)
    {
        bgi_init(dest);
        bgi_sub(dest, test_sub_dataset[i][0], test_sub_dataset[i][1]);

        if (bgi_cmp(dest, test_sub_dataset[i][2]) != 0)
        {
            printf("[FAIL] Test bgi_sub %d / %d", i + 1, TEST_SUB_COUNT);

            printf("\nNumber 1        : ");
            bgi_print(test_sub_dataset[i][0]);
            printf("\nNumber 2        : ");
            bgi_print(test_sub_dataset[i][1]);
            printf("\nExpected result : ");
            bgi_print(test_sub_dataset[i][2]);
            printf("\nReceived result : ");
            bgi_print(dest);

            putchar('\n');
        }

        printf("[PASS] Test bgi_sub %d / %d\n", i + 1, TEST_SUB_COUNT);

        i++;
    }

    exit(EXIT_SUCCESS);
}
