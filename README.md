# RSA implementation and attack on Mbed

## Observations
 - Il faudrait que le tableau ait 34 cases ou plus pour pouvoir gerer les 32 digits de 32bits.
   Ca serait certainement la cause d'une perte de précision ...
   Débordement avant le modulo car 32*1 = 33, 33 + 33 = 34 cases (BIM !)
 - Trouver comment se debarasser du R-1

## Environment

To install dependencies:
```sh
sudo aptitude install lib32c-dev python-gmpy
```

## Compilation

To compile:
```sh
make
```

### Tests

To make tests:
```sh
make tests
```

### Clean project

To clean project:
```sh
make clean
```

