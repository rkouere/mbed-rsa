/**
 * RSA implementation and attack on Mbed
 * Big integers library
 * @author Cyrille Toulet, <cyrille.toulet@gmail.com>
 */
#ifndef _H_BIGINT
    #define _H_BIGINT

    /* Big int size */
    #define BIGINT_SIZE 32

    /* Mbed int */
    typedef uint32_t mbed_int;

    /* Mbed bigint */
    typedef mbed_int mbed_bigint[SIZE];

#endif
