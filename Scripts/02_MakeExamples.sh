#!/bin/bash

cd ../Build || exit

buildExample()
{
    target=$1

    if ! [ -d $target ]; then
    B_NEEDCLEAN=1
    fi

    mkdir -p $target;
    cd ./$target

    if [ -z $B_NEEDCLEAN ]; then
    make clean
    fi

    QT_SELECT=qt5 qmake ../../Example/$target/$target.pro
    make -j4
    cd ..
}


buildExample "ItemSetWidget"

buildExample "ItemSetServer"

buildExample "ItemSetClient"

