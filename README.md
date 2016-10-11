# minode-dal

The set of drivers for MiNode kit.

## Build

### Build Environments

The minode DAL is built on top of ARM mbed and hence uses yotta as an offline build system.

#### Install yotta & gcc arm embedded

Refer to [yotta Documentation](http://yottadocs.mbed.com/#installing) to install yotta

#### Install other dependencies

srecord

```sh
$ sudo apt-get install srecord
```

### Set yotta target

```sh
$ cd /path/to/minode-dal
$ yt target bbc-microbit-classic-gcc
```

### Build

```sh
$ cd /path/to/minode-dal
$ yt build
```

## Hello World

TBD

## Links

- [microbit runtime docs](http://lancaster-university.github.io/microbit-docs/)
