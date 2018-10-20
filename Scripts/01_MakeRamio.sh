#!/bin/bash

cd ../
mkdir ./Build
cd ./Build
mkdir Ramio
cd ./Ramio
make clean
qmake ../../Ramio.pro
make -j4
