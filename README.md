# Tower Defense

[![license](http://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/Blackhawk-TA/TowerDefense/blob/master/LICENSE.md)
![Build](https://github.com/Blackhawk-TA/TowerDefense/workflows/Build/badge.svg)
[![github](https://img.shields.io/github/release/Blackhawk-TA/TowerDefense.svg?color=brightgreen)](https://github.com/Blackhawk-TA/TowerDefense/releases)

A simple tower defense game for the 32Blit and PicoSystem retro consoles

## Build
To be able to build this project the [32blit-sdk](https://github.com/32blit/32blit-sdk) has to be configured.

Linux:
```
mkdir build
cd build
cmake ..
make
```

32Blit:
```
mkdir build.stm32
cd build.stm32
cmake .. -DCMAKE_TOOLCHAIN_FILE="../32blit-sdk/32blit.toolchain"
make TowerDefense
```

PicoSystem:
```
mkdir build.pico
cd build.pico
cmake .. -DCMAKE_TOOLCHAIN_FILE=../../32blit-sdk/pico.toolchain -DPICO_BOARD=pimoroni_picosystem
make
```
