#!/bin/bash

cd ../
mkdir -p ./Build
cd ./Build

if ! [ -d Ramio ]; then
B_NEEDCLEAN=1
fi

mkdir -p Ramio
cd ./Ramio

if [ -z $B_NEEDCLEAN ]; then
echo -en "\033[33;1;40m [CLEAN] $(date)  \033[0m \n"
make clean
fi

echo -en "\033[33;1;40m [MAKE] $(date) \033[0m \n"
QT_SELECT=qt5 qmake ../../Ramio.pro
make -j4

if [ $? -eq 0 ]; then
echo -en "\033[33;1;40m [DONE] $(date) \033[0m \n"
fi
