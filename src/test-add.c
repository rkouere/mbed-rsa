#include <stdlib.h>
#include <stdio.h>
#include "bigint.h"
#include "test-add-dataset.c"

/**
 test-add-dataset. sera généré par un script python (que j'ai déjà commencé).

 Il contiendra le tableau suivant :

     mbed_int[BIGINT_SIZE][3][100] test_add_dataset;
*/
int main() {
    int i;

    for (i = 0; i < TEST_ADD_COUNT - 1; i++)
    {
        mbed_bigint dest;
        bgi_init(&dest);
        bgi_add(&dest, test_add_dataset[i][0], test_add_dataset[i][1]);
        if (bgi_cmp(dest, test_add_dataset[i][2]) != 0)
        {
            printf("[FAIL] Test %d / %d\n\tNumber 1 : ", i, TEST_ADD_COUNT);
            bgi_print(test_add_dataset[i][0]);
            printf("\n\tNumber 2 : ");
            bgi_print(test_add_dataset[i][1]);
            printf("\n\tExpected result : ");
            bgi_print(test_add_dataset[i][2]);
            printf("\n\tReceived result : ");
            bgi_print(dest);
            putchar('\n');
            exit(EXIT_FAILURE);
        }
    }

    printf("[ OK ]\n");
    exit(EXIT_SUCCESS);
}
