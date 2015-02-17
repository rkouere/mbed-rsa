# RSA implementation on Mbed

RSA is one of the first practicable public-key cryptosystems widely used for 
secure data transmission. In such a cryptosystem, the encryption key is public
and differs from the decryption key which is kept secret. In RSA, this 
asymmetry is based on the practical difficulty of factoring the product of two
large prime numbers: the factoring problem. 

There are some years, a cryptographic attack of RSA algorithm was performed by 
statistical analysis of the computation time of a processor. Our project was to
verify the possibility and feasibility of this attack. Studies have been 
conducted and have shown the theoretical possibility to attack the 
cryptosystem by devious means. Observation of computing time will give us 
information about the internal state of the algorithm and allow us to guess the
decryption key.

Therefore, the first part of this project was the implementation of this 
algorithm on a MBED microcontroller. Work on this chip allows isolated 
computing to perform this attack in a controlled environment. The second part 
was to perform two types of attacks: 
 - one by the computation time of the chip;
 - one by the sound of the chip during the calculation.

The RSA algorithm works with very large integers (between 0 and 21024), encoded
on 1024 bits. Without access to functions of memory allocations as the MBED, we
represented these large integers as a simple array of 34 boxes (including two 
used to store caries) containing a 32-bit digits (standard size of an integer 
on the MBED micro-controller).

Last year, a graduate student worked on this project without obtaining from 
results. Before starting, our tutors have provided us a partial copy of a 
famous manual: "The Handbook of Cryptography". This book gave us the 
theoretical algorithms functions that we had to implement.  Our tutors found 
simpler to begin again the project from scratch.

The MBED chip on which we worked imposes the C programming language for the 
software development. We had to rewrite the basic mathematical functions such 
as addition, subtraction, multiplication in order to don’t exceed the size of 
an integer. In order to verify our calculations, we test our results with 
another programming language: Python.

With these features, we have begun the big mathematical part of the project 
which was the writing of the 'Montgomery multiplication' and the ‘Montgomery 
modular exponentiation’.

The main difficulties encountered were on the implementations of the algorithm 
of Montgomery multiplication. Indeed, when we wrote this algorithm, the results
did not correspond with the expected results. After many hours spent on this 
algorithm, we had the chance to meet our supervisors with whom we spent many 
hours working and problem solving coding or understanding of the mathematical 
function.

Unfortunately, we may not have time to make the first attack on the MBED. We 
hope we can run our algorithms on the chip before the end of the project. We 
are disappointed enough not to pass in the funniest part of the project but we
hope that our project will be resumed by students of 4th year for the tests 
using our libraries.


## Informations

The modular exponentiation has been tested **1425237** times with success.


## Requirements

The compilation requires few dependencies:
 - lib32c-dev
 - multiarch-support
 - python-gmpy2
 - make
 - gcc
 - gcc-arm-none-eabi


## Compilation

To build the bigint library (pc/obj/bigint.o & mbed/obj/bigint.o), type:
```sh
make
```

To build and run PC tests, type:
```sh
make tests
```

To clear the tests datasets, type:
```sh
make clean-datasets
```

To clear all the compilated files, type:
```sh
make clean
```

To build the mbed binaries, type:
```sh
make mbed
```

