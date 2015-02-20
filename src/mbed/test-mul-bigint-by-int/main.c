/**
 * RSA implementation and attack on Mbed
 * MBED software - Test of bgi_mul_bigint_by_int()
 * @author Cyrille Toulet, <cyrille.toulet@linux.com>
 * @author Benjamin Burnouf, <benjamin76360@gmail.com>
 */

#include <rflpc17xx/rflpc17xx.h>
#include "../../bigint.h"

void
main()
{
    mbed_bigint x = {0xb760fe83u, 0xc5a4cf4cu, 0x5aa9dfd3u, 0xabb009b5u, 
        0xf813f38eu, 0x4b5ca1bcu, 0xeb38de8fu, 0x8717f038u, 0x6ec3fb74u, 
        0x965c5216u, 0x6c91c4d7u, 0x37e74d65u, 0xa60df0a8u, 0xd790de1fu, 
        0x57d63bc2u, 0xa31f888cu, 0x9a96fd5cu, 0xc2d030aau, 0x9fd30b6fu, 
        0x9e0167ebu, 0x91465d04u, 0xf3ea3565u, 0xf93636aau, 0xc1b3e084u, 
        0x328b5d3bu, 0x57c41f27u, 0xe3a14cf8u, 0xbbd60dd2u, 0xc8359dc1u, 
        0x110a160du, 0x6ddaaf2eu, 0x9e807de4u, 0x00000000u, 0x00000000u};

    mbed_int y = 0x7664b4ce;

    mbed_bigint r = {0x902ce96au, 0x42df17dfu, 0x71e62f4fu, 0x511d0b35u, 
        0x8e2c82c3u, 0x0e6d1e8cu, 0x40f5fb08u, 0x9cd36bfeu, 0xde4c14d5u, 
        0x4fd36e64u, 0x1f39451au, 0x9a3531a0u, 0xf7e862b2u, 0xada84898u, 
        0x77e21154u, 0x76b19decu, 0x3b05447fu, 0xcba519beu, 0xfb51d8aau, 
        0x55e901b0u, 0xd6a87743u, 0xa0a5903cu, 0xcf456d2au, 0x576c809au, 
        0xa0539e09u, 0xc2549c7eu, 0x1f613c84u, 0x4344ac3du, 0xba5333f4u, 
        0xc54a5b85u, 0xd2fea927u, 0x5bc7a139u, 0x494d942au, 0x00000000u};

    mbed_bigint dest;


    /* Init leds */    
    rflpc_led_init();
    rflpc_led_clr(RFLPC_LED_1);
    rflpc_led_clr(RFLPC_LED_2);
    rflpc_led_clr(RFLPC_LED_3);
    rflpc_led_clr(RFLPC_LED_4);

    /* Do multiplication */
    bgi_mul_bigint_by_int(dest, x, y);

    /* If success, switch on leds 2 & 4 */
    if(bgi_cmp(dest, r) == 0)
    {
        rflpc_led_set(RFLPC_LED_2);
        rflpc_led_set(RFLPC_LED_4);
    }

    /* Switch on leds 1 & 3 */
    rflpc_led_set(RFLPC_LED_1);
    rflpc_led_set(RFLPC_LED_3);

    /* Wait for interuption */
    while(1)
        asm("wfi");
}

