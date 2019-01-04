#!/bin/bash

cd ../
mkdir ./Build
cd ./Build
mkdir Ramio
cd ./Ramio
make clean
QT_SELECT=qt5 qmake ../../Ramio.pro
make -j4
