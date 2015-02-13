/**
 * RSA implementation and attack on Mbed
 * Big integers library
 * @author Cyrille Toulet, <cyrille.toulet@linux.com>
 * @author Benjamin Burnouf, <benjamin76360@gmail.com>
 */
#ifndef _H_BIGINT
    #define _H_BIGINT

    #ifdef _COMPUTER_VERSION
        #include <stdio.h>
    #endif

    #include <stdint.h>

    /* Mbed int */
    typedef uint32_t mbed_int;

    /* Mbed long int */
    typedef uint64_t mbed_long_int;

    /* Big int size */
    #define BIGINT_SIZE 32u

    /* Max mbed int */
    #define MAX_MBED_INT 4294967296ul

    /* Mbed bigint */
    typedef mbed_int mbed_bigint[BIGINT_SIZE + 2];

    /**
     * Init to 0 a big int
     * @param x The big int to init
     */
    extern void bgi_init (mbed_bigint x);

    /**
     * Copy a big int
     * @param dest The big int copy destination
     * @param src The big int to copy
     */
    extern void bgi_cpy (mbed_bigint dest, const mbed_bigint src);

    /**
     * Print a big int
     * @param x The big int to print
     */
    extern void bgi_print (const mbed_bigint x);

    /**
     * Compare two big integers
     * @param x The first big int to compare
     * @param y The second big int to compare
     * @return 0 if x=y, -1 if x<y, or 1 if x>y
     */
    extern mbed_int bgi_cmp(const mbed_bigint x, const mbed_bigint y);

    /**
     * Add two big integers and put result in dest
     * @param dest The sum x+y
     * @param x The first big int of addition
     * @param y The second big int of addition
     */
    extern void bgi_add(mbed_bigint dest, const mbed_bigint x, 
        const mbed_bigint y);
    
    /**
     * Substract two big integers and put result in dest
     * @param dest The difference x-y
     * @param x The first big int of substraction
     * @param y The second big int of substraction
     */
    extern void bgi_sub (mbed_bigint dest, const mbed_bigint x, 
        const mbed_bigint y);

    /**
     * Shift a number to the rught
     * @param x The big int to shift
     * @param shift The shift value
     */
    extern void bgi_rshift(mbed_bigint x, mbed_int shift);
    
    /**
     * Multiply an integer by an other integer and put result in two dests
     * @param dest1 the first part of result x*y on 32 bits
     * @param dest2 the second part of result x*y on 32 bits
     * @param x The first int of multiplication
     * @param y The second int of multiplication
     */
    extern void bgi_mul_int_by_int(mbed_int *dest1, mbed_int *dest2, 
        const mbed_int x, const mbed_int y);

    /**
     * Multiply a big integers by a small integer and put result in dest
     * @param dest The product x*y
     * @param x The big int of multiplication
     * @param y The small int of multiplication
     */
    extern void bgi_mul_bigint_by_int(mbed_bigint dest, const mbed_bigint x, 
        const mbed_int y);

    /**
     * Multiply two big integers and put result in dest
     * @param dest The Montgomery multiplication result
     * @param x The first big int of multiplication
     * @param y The second big int of multiplication
     * @param m The modulus of multiplication
     * @param mp The modulus inverse of multiplication
     */
    extern void bgi_mul(mbed_bigint dest, const mbed_bigint x, 
        const mbed_bigint y, const mbed_bigint m, const mbed_int mp);

    /**
     * Montgomery modular exponentiation
     * @param dest The Montgomery multiplication result
     * @param x The big int 
     * @param e The exponent 
     * @param m The modulus of multiplication
     * @param mp The modulus inverse of multiplication
     */
    extern void mod_exp(mbed_bigint dest, const mbed_bigint x, 
	const mbed_bigint e, const mbed_bigint m, const mbed_int mp, 
	const mbed_bigint rm, const mbed_bigint r2);

#endif
