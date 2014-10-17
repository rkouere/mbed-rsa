/**
 * RSA implementation and attack on Mbed
 * Big integers library
 * @author Cyrille Toulet, <cyrille.toulet@gmail.com>
 */

#include "bigint.h"


/**
 * @see bigint.h
 */
void
bgi_init(mbed_bigint *x)
{
    mbed_int i;

    for(i = (mbed_int) 0; i <= BIGINT_SIZE; i++)
        (*x)[i] = 0;
}


/**
 * @see bigint.h
 */
void
bgi_cpy(mbed_bigint *dest, const mbed_bigint src)
{
    mbed_int i;

    for(i = (mbed_int) 0; i <= BIGINT_SIZE; i++)
        (*dest)[i] = src[i];
}


/**
 * @see bigint.h
 */
void
bgi_print(const mbed_bigint x)
{
    #ifdef _COMPUTER_VERSION
        mbed_int i;

        for (i = (mbed_int) 0; i < BIGINT_SIZE - 1; i++)
            printf("%lx.", (unsigned long) x[i]);

        printf("%lx\n", (unsigned long) x[BIGINT_SIZE]);
    #endif
}


/**
 * @see bigint.h
 */
mbed_int
bgi_cmp(const mbed_bigint x, const mbed_bigint y)
{
    mbed_int i = (mbed_int) 0;

    while (i <= BIGINT_SIZE) 
        if (x[i] != y[i++]) 
            return (mbed_int) (x[i] > y[i] ? 1 : -1);

    return (mbed_int) 0;
}


/**
 * @see bigint.h
 */
mbed_int
bgi_is_null(const mbed_bigint x)
{
    mbed_int i = (mbed_int) 0;

    while (i <= BIGINT_SIZE)
        if (x[i++] != (mbed_int) 0)
            return (mbed_int) 1;

    return (mbed_int) 0;
}

