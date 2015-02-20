# MBED code for bgi_mod_exp() testing

## About

This software is a tests fot bgi_mod_exp() function.


## Installation

To deploy this software:
```sh
# At the mbed-rsa root directory
make mbed

# Mount mbed on /mnt
sudo mount /dev/sdc /mnt

# Copy the binary on MBED
sudo cp mbed/bin/test-mod-exp.bin /mnt/

# Sync devices
sudo sync
```

And finaly press the MBED reset switch.


## Status

To know the test status:

 - **1 fixed led:** Computing
 - **2 fixed leds:** Test faillure
 - **4 fixed leds:** Test success
 - **4 blinking leds:** MBED error


