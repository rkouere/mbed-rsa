/**
 * RSA implementation and attack on Mbed
 * MBED software - Test of bgi_add()
 * @author Cyrille Toulet, <cyrille.toulet@linux.com>
 * @author Benjamin Burnouf, <benjamin76360@gmail.com>
 */

#include <rflpc17xx/rflpc17xx.h>
#include "../../bigint.h"

void
main()
{
    mbed_bigint x = {0x65be3c44u, 0xf272f5dfu, 0xa05b728du, 0x43f84d9bu, 
        0x6a64d3d2u, 0x4c85252au, 0x2b903e16u, 0xffc4c2d8u, 0x8ffb29e0u, 
        0x0c8667d8u, 0x7eb40d5bu, 0x97734cfeu, 0xd90b1e20u, 0xf5302694u, 
        0x2230fbd1u, 0xfb1d035eu, 0xe8579c53u, 0x7e0b7cfbu, 0x2c52568cu, 
        0xec91d194u, 0xf7268375u, 0x8b2e6429u, 0x52b6d9dcu, 0xfd5cfebcu, 
        0x95740b7fu, 0x49ea8056u, 0xb1f90091u, 0x65e1781du, 0x020d8d47u, 
        0x6b066f7du, 0x9c462af3u, 0x56ac9b2bu, 0x00000000u, 0x00000000u};

    mbed_bigint y = {0x56807d6au, 0x621923b0u, 0x6674cb97u, 0x415b2efeu, 
        0xe88f54eeu, 0x2acabb9eu, 0x117feb31u, 0x593674bcu, 0xe092ac14u, 
        0xc65e7bfeu, 0xae8e8f85u, 0xd1309a37u, 0xc38e3575u, 0x503a04c4u, 
        0xf549f657u, 0xff9066a2u, 0xa25a3844u, 0xe0feb27cu, 0x29e9b1c9u, 
        0x0714a505u, 0x7f92226fu, 0xd53b4f4au, 0x5c2739c2u, 0x60e5c5f0u, 
        0x74a6316fu, 0xd281a465u, 0xd23c8b26u, 0x06a85dfeu, 0x60c334f1u, 
        0xf41b9ca1u, 0x14682ba5u, 0x03886a87u, 0x00000000u, 0x00000000u};

    mbed_bigint r = {0xbc3eb9aeu, 0x548c198fu, 0x06d03e25u, 0x85537c9au, 
        0x52f428c0u, 0x774fe0c9u, 0x3d102947u, 0x58fb3794u, 0x708dd5f5u, 
        0xd2e4e3d7u, 0x2d429ce0u, 0x68a3e736u, 0x9c995396u, 0x456a2b59u, 
        0x177af229u, 0xfaad6a01u, 0x8ab1d498u, 0x5f0a2f78u, 0x563c0856u, 
        0xf3a67699u, 0x76b8a5e4u, 0x6069b374u, 0xaede139fu, 0x5e42c4acu, 
        0x0a1a3cefu, 0x1c6c24bcu, 0x84358bb8u, 0x6c89d61cu, 0x62d0c238u, 
        0x5f220c1eu, 0xb0ae5699u, 0x5a3505b2u, 0x00000000u, 0x00000000u};

    mbed_bigint dest;


    /* Init leds */    
    rflpc_led_init();
    rflpc_led_clr(RFLPC_LED_1);
    rflpc_led_clr(RFLPC_LED_2);
    rflpc_led_clr(RFLPC_LED_3);
    rflpc_led_clr(RFLPC_LED_4);

    /* Do addition */
    bgi_add(dest, x, y);

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

