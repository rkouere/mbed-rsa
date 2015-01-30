# RSA implementation on Mbed

## Requirements

The computer compilation requires few dependencies:
 - lib32c-dev
 - python-gmpy

```sh
sudo aptitude install lib32c-dev multiarch-support python-gmpy
```

# Bugs

On few systems, bgi_sub() tests fail!

Just swap **BIGINT_SIZE + 1** with **BIGINT_SIZE + 2** and retry.


## Build

To compile the project, type ```make```, or ```make all```.

You can clean the compilated files by typping ```make clean```.


## Development

To test the bigint library, type ```make tests```.




## Debug 2015-30-01

 - Probleme de soustraction qui allait pas assez loin
 - probleme de shift qui allait pas assez loin, 
 - probleme d'accolade autour du if final de montgomery
 - manquait une copy dans la soustraction finale
 - conditions de départ x < m 
 - assert sources<>dest
