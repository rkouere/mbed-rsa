/**
 * RSA implementation and attack on Mbed
 * Big integers library - Tests for bgi_mul_bigint_by_int function
 * @author Cyrille Toulet, <cyrille.toulet@linux.com>
 * @author Benjamin Burnouf, <benjamin76360@gmail.com>
 */

#include <stdlib.h>
#include <stdio.h>
#include "../bigint.h"
#include "datasets/mul-montgomery.c"

mbed_int main()
{
    mbed_bigint r;

    mbed_bigint x = {0xe5dcde13u, 0xa5ec7243u, 0xa3aaf01u, 0x36f2cf79u, 0xdd4eba41u, 0x6a38a1a8u, 0x9245d29u, 0xe23ccf64u, 0x4573f035u, 0x3ffbf8e0u, 0x5a8cf48au, 0x7c6ba9b7u, 0x42eef170u, 0x4ffd254bu, 0xb2877e41u, 0x2e09e1e9u, 0xa2e10d55u, 0x2d21e3afu, 0x59b03b6fu, 0xa2269f84u, 0x655efa2cu, 0x34e997f4u, 0xdbfa173du, 0xb5dffca1u, 0xb89809d0u, 0x6fe6ca3fu, 0x58245a38u, 0xe7711d6cu, 0x4ad2b337u, 0x1297c5d3u, 0x2d21e818u, 0xad254afu, 0x0u, 0x0u};
    mbed_bigint y = {0xe5dcde13u, 0xa5ec7243u, 0xa3aaf01u, 0x36f2cf79u, 0xdd4eba41u, 0x6a38a1a8u, 0x9245d29u, 0xe23ccf64u, 0x4573f035u, 0x3ffbf8e0u, 0x5a8cf48au, 0x7c6ba9b7u, 0x42eef170u, 0x4ffd254bu, 0xb2877e41u, 0x2e09e1e9u, 0xa2e10d55u, 0x2d21e3afu, 0x59b03b6fu, 0xa2269f84u, 0x655efa2cu, 0x34e997f4u, 0xdbfa173du, 0xb5dffca1u, 0xb89809d0u, 0x6fe6ca3fu, 0x58245a38u, 0xe7711d6cu, 0x4ad2b337u, 0x1297c5d3u, 0x2d21e818u, 0xad254afu, 0x0u, 0x0u};

    mbed_bigint m = {0x1630b245u, 0x79bad951u, 0xd09ca0eau, 0xa4ceffacu, 0x29d2e82eu, 0xb4740dc2u, 0x78604f36u, 0x286407ccu, 0x19c112ccu, 0x26972bc0u, 0x7be3150au, 0x7a4538fau, 0xda3bd403u, 0xd3d06696u, 0xb8f6aa7fu, 0x323a357cu, 0xdc37e6eu, 0x631744c5u, 0xd1b91bc6u, 0xf90dc58bu, 0xbaef1ceau, 0x207358e7u, 0x5a718af3u, 0x97856659u, 0x752c9b2fu, 0x7936ead3u, 0x2e66ee75u, 0x35a1c66fu, 0x4aa2e454u, 0x64321fbeu, 0x4540aedau, 0xf7bc3e1u, 0x0u, 0x0u};

    mbed_int mi = 0x96c46f73u;

    mbed_bigint excepted = {0xc6afeeb8u, 0x42e15b17u, 0x8dea937fu, 0x67fbfa68u, 0x8a3fa156u, 0xb3c986acu, 0x9481a463u, 0xade1fb35u, 0x42b1382u, 0x44f8e69u, 0xd003db24u, 0x119ca78du, 0xcc844b51u, 0xb2032bf2u, 0xd5088534u, 0x53a29f4fu, 0x1eefd919u, 0x89c57f70u, 0x949d6404u, 0x67f9450u, 0x84d7efa7u, 0x38ad0e97u, 0xaaadd7c8u, 0x26835474u, 0x419bfbfbu, 0x1e02de29u, 0x2e19dc2bu, 0x41af2b6au, 0x873e4a9u, 0xbfad7f05u, 0x6ae9caacu, 0x24e0b29u, 0x0u, 0x0u};

    bgi_init(r);
    bgi_mul(r, x, y, m, mi);

    if (bgi_cmp(r, excepted) != 0)
    {
        printf("[FAIL] Test");

        printf("\nNumber x        : ");
        bgi_print(x);
        printf("\nNumber y        : ");
        bgi_print(y);
        printf("\nModulus         : ");
        bgi_print(m);
        printf("\nExpected result : ");
        bgi_print(excepted);
        printf("\nReceived result : ");
        bgi_print(r);
        putchar('\n');

        exit(EXIT_FAILURE);
    }
    else
    {
        printf("[PASS] It was a false negative!");
    }

    exit(EXIT_SUCCESS);
}
