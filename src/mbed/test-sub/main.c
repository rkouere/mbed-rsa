/**
 * RSA implementation and attack on Mbed
 * MBED software - Test of bgi_sub()
 * @author Cyrille Toulet, <cyrille.toulet@linux.com>
 * @author Benjamin Burnouf, <benjamin76360@gmail.com>
 */

#include <rflpc17xx/rflpc17xx.h>
#include "../../bigint.h"

void
main()
{
    mbed_bigint x = {0xbebd4958u, 0x394c1889u, 0xd4a28807u, 0xd06d9e09u, 
        0x00733f20u, 0x586b2d5fu, 0xf26e6203u, 0xebd9874cu, 0xe7eeec4cu, 
        0xdaeaf982u, 0xa85d7349u, 0xdf7072bau, 0x1226b396u, 0x076a871eu, 
        0x38aa8727u, 0x737ecd3au, 0x64383331u, 0x274097dau, 0xa55fd5e0u, 
        0xc6ddc81cu, 0x4d8fcf04u, 0x0be70fa8u, 0x8fb5963fu, 0x2389b233u, 
        0xc38c52ddu, 0x91c9f16du, 0x17f7fce5u, 0xf3ffb853u, 0xa9da1879u, 
        0xaf2ed2c6u, 0xc7f3c6a4u, 0x751bbf72u, 0x00000000u, 0x00000000u};

    mbed_bigint y = {0xce920f3fu, 0xc4cfd0aau, 0x6a1c953cu, 0x14a47e64u, 
        0x519306d9u, 0x5148e09cu, 0x62dc4bd4u, 0xb1ba6225u, 0x8c68f86eu, 
        0xdc07c1beu, 0xcf324bdeu, 0x7e0c1739u, 0x31c82cfau, 0x9ee1d157u,
        0x8a94c1ecu, 0x517e2310u, 0xfeabd964u, 0xdd08e60cu, 0xd7557523u, 
        0xbec31e55u, 0xc5a43865u, 0x32eefd26u, 0x9d52f3dau, 0x73e6dc49u, 
        0x8ad78a8eu, 0xd93402d4u, 0x7070c008u, 0x224d2d25u, 0x56e0cf67u, 
        0xa377c935u, 0x7b09b668u, 0x34adbadfu, 0x00000000u, 0x00000000u}; 

    mbed_bigint r = {0xf02b3a19u, 0x747c47deu, 0x6a85f2cau, 0xbbc91fa5u, 
        0xaee03847u, 0x07224cc2u, 0x8f92162fu, 0x3a1f2527u, 0x5b85f3deu, 
        0xfee337c4u, 0xd92b276au, 0x61645b80u, 0xe05e869cu, 0x6888b5c6u, 
        0xae15c53au, 0x2200aa29u, 0x658c59cdu, 0x4a37b1cdu, 0xce0a60bcu, 
        0x081aa9c6u, 0x87eb969fu, 0xd8f81281u, 0xf262a264u, 0xafa2d5e9u, 
        0x38b4c84eu, 0xb895ee99u, 0xa7873cdcu, 0xd1b28b2du, 0x52f94912u, 
        0x0bb70991u, 0x4cea103cu, 0x406e0493u, 0x00000000u, 0x00000000u};

    mbed_bigint dest;

    /* Init leds */    
    rflpc_led_init();
    rflpc_led_clr(RFLPC_LED_1);
    rflpc_led_clr(RFLPC_LED_2);
    rflpc_led_clr(RFLPC_LED_3);
    rflpc_led_clr(RFLPC_LED_4);

    /* Do substraction */
    bgi_sub(dest, x, y);

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

