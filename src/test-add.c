#include <stdio.h>
#include "bigint.h"
#include "test-add-dataset.h"

/**
 * test-add-dataset. sera généré par un script python (que j'ai déjà commencé).
 *
 * Il contiendra le tableau suivant :
 *
 *     mbed_int[BIGINT_SIZE][3][100] test_add_dataset;
 * 
 * Reste à faire le main :
 *
 * for (i=0; i < 99; i++)
 * {
 *     mbed_bigint dest;
 *     bgi_init(&dest);
 *     bgi_add(&dest, test_add_dataset[i][0], test_add_dataset[i][1]);
 *     if (bgi_cmp(dest, test_add_dataset[i][2]) != 0)
 *     {
 *         printf("[FAIL] + détails ...\n");
 *         exit(EXIT_FAILURE);
 *     }
 * }
 *
 * printf("[ OK ]\n");
 * exit(EXIT_SUCCESS);
 *
 * Il faut détailler les infos au cas ou le test ne passe pas ;~)
 */
