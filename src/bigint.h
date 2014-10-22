/**
 * RSA implementation and attack on Mbed
 * Big integers library
 * @author Cyrille Toulet, <cyrille.toulet@gmail.com>
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

    /* Big int size */
    #define BIGINT_SIZE 32u

    /* Max mbed int */
    #define MAX_MBED_INT 4294967295u

    /* Mbed bigint */
    typedef mbed_int mbed_bigint[BIGINT_SIZE + 1];

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
     * Check if a big int is null or not
     * @param x The big int to check
     * @return 1 if x is null, or 0 if not
     */
    extern mbed_int bgi_is_null(const mbed_bigint x);

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

#endif
