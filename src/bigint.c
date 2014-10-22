/**
 * RSA implementation and attack on Mbed
 * Big integers library
 * @author Cyrille Toulet, <cyrille.toulet@gmail.com>
 * @author Benjamin Burnouf, <benjamin76360@gmail.com>
 */

#include "bigint.h"


/**
 * @see bigint.h
 */
void
bgi_init(mbed_bigint *x)
{
    mbed_int i;

    for(i = 0; i < BIGINT_SIZE + 1; i++)
        (*x)[i] = (mbed_int) 0x0u;
}


/**
 * @see bigint.h
 */
void
bgi_cpy(mbed_bigint *dest, const mbed_bigint src)
{
    mbed_int i;

    for(i = (mbed_int) 0; i <= BIGINT_SIZE + 1; i++)
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

        for (i = (BIGINT_SIZE - 1); i > 0; i--)
            printf("%8x ", x[i]);
    #endif
}


/**
 * @see bigint.h
 */
mbed_int
bgi_cmp(const mbed_bigint x, const mbed_bigint y)
{
    mbed_int i = (BIGINT_SIZE - 1);

    while (i > 0) 
        if (x[i] != y[i]) 
            return (x[i] > y[i]? 1: -1);
        else
            i--;

    return 0;
}


/**
 * @see bigint.h
 */
mbed_int
bgi_is_null(const mbed_bigint x)
{
    mbed_int i = 0;

    while (i < BIGINT_SIZE + 1)
        if (x[i++] != (mbed_int) 0)
            return 1;

    return 0;
}


/**
 * @see bigint.h
 */
void
bgi_add(mbed_bigint *dest, const mbed_bigint x, const mbed_bigint y)
{
    mbed_int carry = 0;
    mbed_int i;

    for (i = (mbed_int) 0; i < BIGINT_SIZE; i++)
    {
        (*dest)[i] = (x[i] + y[i] + carry) % MAX_MBED_INT;
        carry = (MAX_MBED_INT - x[i] - carry) < y[i]? (mbed_int) 1: (mbed_int) 0;
    }

    (*dest)[i] = carry;
}


/**
 * @see bigint.h
 */
void 
bgi_sub(mbed_bigint *dest, const mbed_bigint x, const mbed_bigint y)
{
    mbed_int carry = 0;
    mbed_int i;

    for (i = (mbed_int) 0; i < BIGINT_SIZE; i++)
    {
        (*dest)[i] = (x[i] - y[i] + carry) % MAX_MBED_INT;
        carry = (x[i] - y[i] + carry) < 0? (mbed_int) -1: (mbed_int) 0;
    }

    (*dest)[i] = carry;
}
