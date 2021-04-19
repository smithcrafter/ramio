#!/bin/bash

./01_MakeRamio.sh || exit
./01_MakeRamioCore.sh || exit
./02_MakeExamples.sh || exit
./03_MakeTests.sh || exit
./04_RunTests.sh || exit


