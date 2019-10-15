#!/bin/bash

cd ../Bin || exit

runTest()
{
    target=$1

    echo -en "\033[33;1;34m [RUN] $target  \033[0m \n"

    ./$target

    if [ $? -eq 0 ]; then
    echo -en "\033[33;1;32m [DONE] $(date) \033[0m \n"
    fi
}


runTest "MetaItemTest"
