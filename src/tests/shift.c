/**
 * RSA implementation and attack on Mbed
 * Big integers library - Tests for bgi_lshift function
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

    while (i < TEST_ADD_COUNT)
    {
        printf("Number: ");
        bgi_print(test_add_dataset_y[i]);
        putchar('\n');
        
        printf("Number with %d right shift: ", (i % BIGINT_SIZE));

        bgi_rshift(test_add_dataset_y[i], i % BIGINT_SIZE);
        bgi_print(test_add_dataset_y[i]);
        putchar('\n');
        putchar('\n');

        i++;
    }

    exit(EXIT_SUCCESS);
}
