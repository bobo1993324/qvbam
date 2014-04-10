#!/bin/bash
mkdir build
cd build
cmake .. -DENABLE_QT=on
make
