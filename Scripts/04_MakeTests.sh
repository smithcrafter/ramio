#!/bin/bash

cd ../Build || exit

buildTest()
{
    target=$1
    
    echo -en "\033[33;1;34m [BUILD] $target  \033[0m \n"

    if ! [ -d $target ]; then
    B_NEEDCLEAN=1
    fi

    mkdir -p $target;
    cd ./$target

    if [ -z $B_NEEDCLEAN ]; then
    echo -en "\033[33;1;40m [CLEAN] $(date)  \033[0m \n"
    make clean
    fi

    echo -en "\033[33;1;40m [MAKE] $(date) \033[0m \n"
    QT_SELECT=qt5 qmake ../../Tests/$target/$target.pro
    make -j4
    
    if [ $? -eq 0 ]; then
    echo -en "\033[33;1;32m [DONE] $(date) \033[0m \n"
    fi
    
    cd ..
}

buildTest "Items"

buildTest "MetaItemTest"


