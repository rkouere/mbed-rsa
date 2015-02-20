/**
 * RSA implementation and attack on Mbed
 * MBED software - Test of bgi_montgomery_mul()
 * @author Cyrille Toulet, <cyrille.toulet@linux.com>
 * @author Benjamin Burnouf, <benjamin76360@gmail.com>
 */

#include <rflpc17xx/rflpc17xx.h>
#include "../../bigint.h"

void
main()
{
    mbed_bigint m = {0x4b2bbf55u, 0x46d301ffu, 0xc4def1acu, 0xc67a8528u, 0x6bedc842u, 0xa6ad24adu, 0x7df95e40u, 0xb1f8f640u, 0xf1caf98cu, 0xcd468b8du, 0x6ff54c67u, 0x487ab1a7u, 0x8de45f91u, 0x3010449cu, 0x633223ebu, 0x4bc1b99eu, 0x7740bad6u, 0xee24242bu, 0x6f24209fu, 0x7e54774du, 0x2c006da1u, 0xb69018f6u, 0xe27d8973u, 0xbe8deb70u, 0xd910d40cu, 0xab37e92au, 0x03ab0fedu, 0xa246f325u, 0x836f6c32u, 0xedec62cbu, 0x94b26cdcu, 0x38b92a5cu, 0x00000000u, 0x00000000u};

    mbed_int mp = 0x1595ba03u;

    mbed_bigint x = {0x8f11eb6du, 0x79d6a644u, 0x4e4a5045u, 0x1e806dc4u, 0x7b763df0u, 0x02bc51b5u, 0x9c430ef3u, 0x3f7212f0u, 0xd608f402u, 0x73fc6e09u, 0xc0e2beb1u, 0xe487a165u, 0x4f326579u, 0x9b4a9245u, 0x81ddedaeu, 0xda790062u, 0x751595d4u, 0xa51ba9d7u, 0xaae31c28u, 0xf539d397u, 0x9941686au, 0x8c4dbcaau, 0x59d52a51u, 0x258eb422u, 0xb3736edau, 0xc37e52a8u, 0xe00f2dccu, 0xe02fc80fu, 0xc439fb7au, 0x8cbdfc73u, 0xcde14b71u, 0x376056a1u, 0x00000000u, 0x00000000u};

    mbed_bigint r = {0x4c16cccdu, 0xe87305a3u, 0xdb984acbu, 0x2a69b0bdu, 0x845f8d1fu, 0x47aac6aeu, 0x80685165u, 0xc4a42fe1u, 0x5c4cca93u, 0x3a768e4cu, 0x47d82d3eu, 0x135498e2u, 0x8e020277u, 0xc5a18e2eu, 0x64fe3ec8u, 0xb2c767bdu, 0x0f72238au, 0x3e3c72cdu, 0x30948ad2u, 0x1aa1a995u, 0x6fc7f735u, 0xde108266u, 0xcdbfc0bfu, 0xa6fd7e9bu, 0xe43fb5cbu, 0xa47f1e7bu, 0x8cab0808u, 0x325fc171u, 0xfcc7df20u, 0xdd50b96bu, 0xc57f8e38u, 0x1002a5e8u, 0x00000000u, 0x00000000u};

    mbed_bigint dest;

    bgi_init(dest);

    /* Init leds */    
    rflpc_led_init();
    rflpc_led_clr(RFLPC_LED_1);
    rflpc_led_clr(RFLPC_LED_2);
    rflpc_led_clr(RFLPC_LED_3);
    rflpc_led_clr(RFLPC_LED_4);

    /* Switch on led 1 */
    rflpc_led_set(RFLPC_LED_1);

    /* Do multiplication */
    bgi_montgomery_mul(dest, x, x, m, mp);

    /* If success, switch on leds 2 & 4 */
    if(bgi_cmp(dest, r) == 0)
    {
        rflpc_led_set(RFLPC_LED_2);
        rflpc_led_set(RFLPC_LED_4);
    }

    /* Switch on led 3 */
    rflpc_led_set(RFLPC_LED_3);

    /* Wait for interuption */
    while(1)
        asm("wfi");
}

