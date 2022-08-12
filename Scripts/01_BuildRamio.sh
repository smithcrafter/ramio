#!/bin/bash

cd ../
mkdir -p ./Build
cd ./Build

echo -en "\033[33;1;34m [BUILD] Ramio  \033[0m \n"

mkdir -p Ramio
cd ./Ramio

echo -en "\033[33;1;40	m [MAKE] $(date) \033[0m \n"
QT_SELECT=qt5 qmake ../../Ramio.pro
make -j4

if [ $? -eq 0 ]; then
echo -en "\033[33;1;32m [DONE] $(date) \033[0m \n"
fi
