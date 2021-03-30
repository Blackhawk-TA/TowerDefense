# TowerDefense

[![license](http://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/Blackhawk-TA/TowerDefense/blob/master/LICENSE.md)
![Build](https://github.com/Blackhawk-TA/TowerDefense/workflows/Build/badge.svg)
[![github](https://img.shields.io/github/release/Blackhawk-TA/TowerDefense.svg?color=brightgreen)](https://github.com/Blackhawk-TA/snake32/releases)

A simple tower defense game for the 32Blit retro console.

## Build
Linux:
```
mkdir build
cd build
cmake ..
make
```

32blit:
```
mkdir build.stm32
cd build.stm32
cmake .. -DCMAKE_TOOLCHAIN_FILE="../32blit-sdk/32blit.toolchain"
make TowerDefense
```
