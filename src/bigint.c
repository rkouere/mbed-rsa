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
bgi_init(mbed_bigint x)
{
    mbed_int i;

    for(i = 0; i < BIGINT_SIZE + 1; i++)
        x[i] = (mbed_int) 0x0u;
}


/**
 * @see bigint.h
 */
void
bgi_cpy(mbed_bigint dest, const mbed_bigint src)
{
    mbed_int i;

    for(i = (mbed_int) 0; i <= BIGINT_SIZE + 1; i++)
        dest[i] = src[i];
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
bgi_add(mbed_bigint dest, const mbed_bigint x, const mbed_bigint y)
{
    mbed_int carry = 0;
    mbed_int i;

    for (i = (mbed_int) 0; i < BIGINT_SIZE; i++)
    {
        dest[i] = (x[i] + y[i] + carry) % MAX_MBED_INT;
        carry = (MAX_MBED_INT - x[i] - carry) < y[i]? (mbed_int) 1: (mbed_int) 0;
    }

    dest[i] = carry;
}


/**
 * @see bigint.h
 */
void 
bgi_sub(mbed_bigint dest, const mbed_bigint x, const mbed_bigint y)
{
    mbed_int carry = 0;
    mbed_int i;

    for (i = (mbed_int) 0; i < BIGINT_SIZE; i++)
    {
        dest[i] = (x[i] - y[i] + carry) % MAX_MBED_INT;
        carry = (x[i] + carry) <= y[i]? (mbed_int) -1: (mbed_int) 0;
    }

    dest[i] = carry;
}


/**
 * @see bigint.h
 */
void 
bgi_mul_int_by_int(mbed_int *dest1, mbed_int *dest2, const mbed_int x, const mbed_int y) 
{
    mbed_long_int res = (mbed_long_int) (((mbed_long_int) x) * ((mbed_long_int) y));

    *dest1 = (mbed_int) (res >> 32);
    *dest2 = (mbed_int) res; 
}


/**
 * @see bigint.h
 */
void 
bgi_mul_bigint_by_int(mbed_bigint dest, const mbed_bigint x, const mbed_int y) 
{
    mbed_int rest;
    mbed_int temp = 0;
    mbed_int carry = 0;
    mbed_int i;

    for (i = (mbed_int) 0; i < BIGINT_SIZE; i++)
    {
        temp = carry;
        bgi_mul_int_by_int(&carry, &rest, x[i], y);
        if ( rest > MAX_MBED_INT-temp) 
        {
            dest[i] = rest + temp % MAX_MBED_INT;
            carry ++;
        }
        else 
            dest[i] = rest + temp;
    }
    dest[i] = carry;
}


/**
 * @see bigint.h
 */
void 
bgi_lshift(mbed_bigint x, mbed_int shift)
{
    mbed_int i;

    for (i = BIGINT_SIZE - shift; i > 0; i--)
        x[i + shift] = x[i];

    for (i = shift; i > 0; i--)
        x[i] = 0x0u;
}


/**
 * @see bigint.h
 */
void 
bgi_rshift(mbed_bigint x, mbed_int shift)
{
    mbed_int i;

    for (i = 0 + shift; i <= BIGINT_SIZE; i++)
        x[i] = x[i + shift];

    for (i = BIGINT_SIZE + 1 - shift; i <= BIGINT_SIZE; i++)
        x[i] = 0x0u;
}


/**
 * @see bigint.h
 */
/*void 
bgi_mul(mbed_bigint dest, const mbed_bigint x, const mbed_bigint y, 
const mbed_bigint m, const mbed_int mp)
{
    mbed_bigint u;
    mbed_int i;
    mbed_int tmp1, tmp2, tmp3;
    mbed_bigint tmp4, tmp5, tmp6;
    mbed_longint tmp7;

    bgi_init(dest);
    bgi_init(u);

    for (i = 0; i < BIGINT_SIZE; i++)
    {
        bgi_init(tmp4);
        bgi_init(tmp5);
        bgi_init(tmp6);

        bgi_mul_int_by_int(tmp1, tmp2, x[i], y[0]);
        tmp3 = dest[0] + tmp2;
        bgi_mul_int_by_int(tmp7[0], tmp7[1], mp, tmp3);
        u[i] = 

        bgi_mul_bigint_by_int(tmp4, y, x[i]);
        bgi_mul_bigint_by_int(tmp5, m, u[i]);
        bgi_add(tmp6, dest, tmp4);
        bgi_add(tmp6, tmp6, tmp5);
        bgi_div(dest, tmp6, MAX_MBED_INT);
    }

    if (bgi_cmp(dest, m) != -1)
       bgi_sub(dest, dest, m); 
}*/
