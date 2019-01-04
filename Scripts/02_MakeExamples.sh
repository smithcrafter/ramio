#!/bin/bash

cd ../Build || exit

buildExample()
{
    target=$1

    mkdir $target;
    cd ./$target
    make clean
    QT_SELECT=qt5 qmake ../../Example/$target/$target.pro
    make -j4
    cd ..
}


buildExample "ItemSetWidget"

buildExample "ItemSetServer"

buildExample "ItemSetClient"

