/**
 * RSA implementation and attack on Mbed
 * Big integers library - Tests for bgi_lshift function
 * @author Cyrille Toulet, <cyrille.toulet@gmail.com>
 * @author Benjamin Burnouf, <benjamin76360@gmail.com>
 */

#include <stdlib.h>
#include <stdio.h>
#include "bigint.h"
#include "test-add-dataset.c"

mbed_int main()
{
    mbed_int i = 0;

    while (i < TEST_ADD_COUNT)
    {
        printf("Number: \n");
        bgi_print(test_add_dataset_x[i]);
        
        printf("Number with %d shift: \n", (i % BIGINT_SIZE));

        bgi_lshift(test_add_dataset_x[i], i % BIGINT_SIZE);
        bgi_print(test_add_dataset_x[i]);

        i++;
    }

    exit(EXIT_SUCCESS);
}
