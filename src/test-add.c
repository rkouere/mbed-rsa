#include <stdio.h>
#include "bigint.h"
#include "test-add-dataset.c"

/**
 test-add-dataset. sera généré par un script python (que j'ai déjà commencé).

 Il contiendra le tableau suivant :

     mbed_int[BIGINT_SIZE][3][100] test_add_dataset;
*/
int main() {
    for (i=0; i < TEST_ADD_COUNT-1; i++)
    {
        mbed_bigint dest;
        bgi_init(&dest);
        bgi_add(&dest, test_add_dataset[i][0], test_add_dataset[i][1]);
        if (bgi_cmp(dest, test_add_dataset[i][2]) != 0)
        {
            printf("[FAIL]\n\tNombre 1 : ");
            bgi_print(test_add_dataset[i][0];
            printf("\n\tNombre 2 : ");
            bgi_print(test_add_dataset[i][1];
            printf("\n\tRésultat attendu : ");
            bgi_print(test_add_dataset[i][2];
            printf("\n\tRésultat reçu : ");
            bgi_print(dest);
            exit(EXIT_FAILURE);
        }
    }

    printf("[ OK ]\n");
    exit(EXIT_SUCCESS);
}
