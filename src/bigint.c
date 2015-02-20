/**
 * RSA implementation and attack on Mbed
 * Big integers library
 * @author Cyrille Toulet, <cyrille.toulet@linux.com>
 * @author Benjamin Burnouf, <benjamin76360@gmail.com>
 */

#include "bigint.h"

#ifndef _COMPUTER_VERSION
    #include <rflpc17xx/rflpc17xx.h>
#endif


/**
 * @see bigint.h
 */
void
bgi_init(mbed_bigint x)
{
    mbed_int i;

    /* Init the 32 digits + the 2 carry's digits to 0 */
    for(i = 0; i < BIGINT_SIZE + 2; i++)
        x[i] = (mbed_int) 0x0u;
}


/**
 * @see bigint.h
 */
void
bgi_cpy(mbed_bigint dest, const mbed_bigint src)
{
    int i;

    /* Copy the 32 digits + the 2 carry's digits to "dest" */
    for(i = (mbed_int) 0; i < BIGINT_SIZE + 2; i++)
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

        /* Print the the 31 firsts digits of the bigint */
        for (i = (BIGINT_SIZE + 2 - 1); i > 0; i--)
        {
            if (i == (BIGINT_SIZE + 1))
                printf("[%8x ", x[i]);
            else if (i == BIGINT_SIZE)
                printf("%8x] ", x[i]);
            else
                printf("%8x ", x[i]);
        }

	/* And the last one */
        printf("%8x ", x[0]);
    #endif
}


/**
 * @see bigint.h
 */
mbed_int
bgi_cmp(const mbed_bigint x, const mbed_bigint y)
{
    int i = BIGINT_SIZE;

    while (i > 0) 
        /* Compare digit by digit */
        if (x[i] != y[i]) 
            return (x[i] > y[i]? 1: -1);
        else
            i--;

    return 0;
}


/**
 * @see bigint.h
 */
void
bgi_add(mbed_bigint dest, const mbed_bigint x, const mbed_bigint y)
{
    mbed_int carry = 0;
    int i;

    /* Add two big integers digit by digit */
    for (i = 0; i < BIGINT_SIZE + 1; i++)
    {
        dest[i] = (x[i] + y[i] + carry);

        carry = (
            ((x[i] + y[i] + carry) < x[i]) ||
            ((x[i] + y[i] + carry) < y[i])
        ) ? (mbed_int) 1: (mbed_int) 0;
    }

    /* And don't forget the carry! */
    dest[i] += carry;
}


/**
 * @see bigint.h
 */
void 
bgi_sub(mbed_bigint dest, const mbed_bigint x, const mbed_bigint y)
{
    mbed_int carry = 0;
    int i;

    /* Subtracts two big integers digit by digit */
    for (i = 0; i < BIGINT_SIZE + 1; i++)
    {
        dest[i] = (x[i] - (y[i] + carry));
        carry = (x[i] < (carry + y[i]))? (mbed_int) 1: (mbed_int) 0;
    }

    /* And don't forget the carry! */
    dest[i] = carry;
}


/**
 * @see bigint.h
 */
void 
bgi_mul_int_by_int(mbed_int *carry, mbed_int *rest, const mbed_int x, 
const mbed_int y)
{
    /* Multiply two integers and store the result in a 64 bits integer */
    mbed_long_int res = (mbed_long_int) 
        (((mbed_long_int) x) * ((mbed_long_int) y));

    /* Split the result to extract the carry */
    *carry = (mbed_int) (res >> 32);
    *rest = (mbed_int) res; 
}


/**
 * @see bigint.h
 */
void 
bgi_mul_bigint_by_int(mbed_bigint dest, const mbed_bigint x, const mbed_int y)
{
    mbed_int rest;
    mbed_int tmp = 0;
    mbed_int carry = 0;
    int i;

    /* Do a basic multiplication */
    for (i = 0; i < BIGINT_SIZE + 1; i++)
    {
        tmp = carry;
        bgi_mul_int_by_int(&carry, &rest, x[i], y);

        if (rest > MAX_MBED_INT - 1 - tmp) 
            carry ++;

        dest[i] = rest + tmp;
    }

    dest[i] = carry;
}


/**
 * @see bigint.h
 */
void 
bgi_rshift(mbed_bigint x, mbed_int shift)
{
    int i;

    /* Shift the digits */
    for (i = 0; i <= BIGINT_SIZE + 1 - shift; i++)
        x[i] = x[i + shift];

    /* Complete digits with "0" */
    for (i = BIGINT_SIZE + 1 - shift + 1; i <= BIGINT_SIZE + 1; i++)
        x[i] = 0x0u;
}


/**
 * @see bigint.h
 */
void 
bgi_montgomery_mul(mbed_bigint dest, const mbed_bigint x, const mbed_bigint y,
const mbed_bigint m, const mbed_int mp)
{
    mbed_bigint u;
    mbed_bigint y_xi;
    mbed_bigint ui_m;
    mbed_bigint tmp;
    mbed_bigint tmp2;
    int i;

    bgi_init(dest);
    bgi_init(u);
    
    for (i = 0; i < BIGINT_SIZE; i++)
    {
        bgi_init(y_xi);
        bgi_init(ui_m);
        bgi_init(tmp);
        bgi_init(tmp2);

        u[i] = ((dest[0] + (x[i] * y[0])) * mp);

        bgi_mul_bigint_by_int(y_xi, y, x[i]);
        bgi_add(tmp, dest, y_xi);

	bgi_mul_bigint_by_int(ui_m, m, u[i]);
        bgi_add(dest, tmp, ui_m);

        bgi_rshift(dest, 1);
    }

    if (bgi_cmp(dest, m) != -1)
    {
        bgi_cpy(tmp2, dest);
        bgi_sub(dest, tmp2, m);
    }
}


/**
 * @see bigint.h
 */
mbed_int
bgi_highest_bit(const mbed_bigint x)
{
    int i;
    int j;

    for(i = (BIGINT_SIZE - 1); i > 0; i--)
        if(x[i] != 0)
            break;

    for(j = 31; j > 0; j--)
        if(((x[i] >> (j - 1)) & 0x1) == 1)
            break;

    return i * 32 + j;
}


/**
 * @see bigint.h
 */
void 
bgi_mod_exp(mbed_bigint dest, const mbed_bigint x, 
const mbed_bigint e, const mbed_bigint m, const mbed_int mp, 
const mbed_bigint rm, const mbed_bigint r2)
{
    mbed_bigint xp;
    mbed_bigint a;
    mbed_bigint tmp;
    mbed_bigint one;
    int t;
    int i;

    bgi_montgomery_mul(xp, x, r2, m, mp);
    bgi_cpy(a, rm);

    t = bgi_highest_bit(e);

    for(i = t; i >= 0; i--)
    {
        int j;
        int k;

        bgi_cpy(tmp, a);
        bgi_montgomery_mul(a, tmp, tmp, m, mp);

        j = i >> 5;
        k = i & 31;

        if(((e[j] >> k) & 0x1) == 0x1)
        {
            bgi_cpy(tmp, a);
            bgi_montgomery_mul(a, tmp, xp, m, mp);
        }
    }

    bgi_init(one);
    one[0] = 1;

    bgi_cpy(tmp, a);
    bgi_montgomery_mul(a, tmp, one, m, mp);

    bgi_cpy(dest, a);
}

