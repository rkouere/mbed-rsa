/**
 * RSA implementation and attack on Mbed
 * Big integers library - Tests of montgomery_exponentiation function
 * @author Cyrille Toulet, <cyrille.toulet@linux.com>
 * @author Benjamin Burnouf, <benjamin76360@gmail.com>
 */

#include <stdlib.h>
#include <stdio.h>
#include "../bigint.h"
#include "datasets/mod-exp.c"

mbed_int main()
{
    long int i = 0;
    mbed_bigint dest;

    while (i < TEST_MOD_EXP_COUNT)
    {
        bgi_init(dest);

        bgi_mod_exp(
	    dest, 
            test_mod_exp_dataset_x[i], 
            test_mod_exp_dataset_e[i], 
            test_mod_exp_dataset_m[i], 
            test_mod_exp_dataset_mp[i], 
            test_mod_exp_dataset_rm[i], 
            test_mod_exp_dataset_r2[i]
	);

        if (bgi_cmp(dest, test_mod_exp_dataset_excepted[i]) != 0)
        {
            printf("[FAIL] Test mod_exp %d / %d", i + 1, TEST_MOD_EXP_COUNT);

            printf("\nx:               ");
            bgi_print(test_mod_exp_dataset_x[i]);

            printf("\ne:               ");
            bgi_print(test_mod_exp_dataset_e[i]);

            printf("\nm:               ");
            bgi_print(test_mod_exp_dataset_m[i]);

            printf("\nm':              [       0        0] %x", test_mod_exp_dataset_mp[i]);

            printf("\nR mod m:         ");
            bgi_print(test_mod_exp_dataset_rm[i]);

            printf("\nR²:              ");
            bgi_print(test_mod_exp_dataset_r2[i]);

            printf("\nExcepted result: ");
            bgi_print(test_mod_exp_dataset_excepted[i]);

            printf("\nRecieved result: ");
            bgi_print(dest);

            putchar('\n');

            exit(EXIT_FAILURE);
        }
	else
            printf("[PASS] Test mod_exp %d / %d\n", i + 1, TEST_MOD_EXP_COUNT);

        i++;
    }

    exit(EXIT_SUCCESS);
}

