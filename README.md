# CPU-Time-Jitter-Based-RNG
CPU Time Jitter Based RNG
基于CPU抖动的随机数生成器

**参照标准：GMT 0105-2021 软件随机数发生器设计指南**
**本库的实现参考了https://github.com/smuellerDD/jitterentropy-library**

本库通过计算高精度时间戳间的差值，收集执行SHA3-256/SM3和随机内存读取时的CPU抖动作为熵源，并参照标准设计对应的熵池与基于SM3随机数发生器。

## 概述

#### 熵源计算支持算法

- sha3-256
- sm3

基于这两个算法的实现都通过了NIST SP800-90B的熵源检测

#### 高精度时间戳

- 当系统自带时间戳的精度满足要求时调用系统本身的高精度时间戳
- 否则调用本库实现的高精度时间戳（注意：调用本库实现的高精度时间戳需要pthread线程库的环境）

## 构建 && 安装

### 快速开始

请确保编译环境中含gcc、cmake和pthread环境。

运行下面命令编译库：
```asm
$ mkdir build && cd build
$ cmake ..
$ make -j
```
编译好后，{项目路径}/build/out目录下为头文件和编译库，{项目路径}/build/out目录下为可执行文件和库文件。
