/**
 * RSA implementation and attack on Mbed
 * MBED software - Test of bgi_mul_int_by_int()
 * @author Cyrille Toulet, <cyrille.toulet@linux.com>
 * @author Benjamin Burnouf, <benjamin76360@gmail.com>
 */

#include <rflpc17xx/rflpc17xx.h>
#include "../../bigint.h"

void
main()
{
    mbed_int x = 0x37946455;
    mbed_int y = 0x23a7d9b;
    mbed_int r = 0x007bdbac;
    mbed_int c = 0x81184077;

    mbed_int carry;
    mbed_int result;

    /* Init leds */    
    rflpc_led_init();
    rflpc_led_clr(RFLPC_LED_1);
    rflpc_led_clr(RFLPC_LED_2);
    rflpc_led_clr(RFLPC_LED_3);
    rflpc_led_clr(RFLPC_LED_4);

    /* Do multiplication */
    bgi_mul_int_by_int(&carry, &result, x, y);

    /* If success, switch on leds 2 & 4 */
    if ((carry != c) || (result != r))
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

