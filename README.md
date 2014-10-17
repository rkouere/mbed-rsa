# RSA implementation and attack on Mbed

## Environment

To prepare environment to compilation:

```sh
mkdir -p computer/obj
mkdir -p computer/bin
```

To install dependencies:
```sh
sudo aptitude install lib32c-dev
```

## Compilation

### Computer compilation

To compile for computer:
```sh
make computer
```

### Mbed compilation

To compile for mbed:
```sh
make mbed
```

### Both compilation

To compile for all devices:
```sh
make
# or
make all
```

### Clean project

To clean project:
```sh
make clean
```

