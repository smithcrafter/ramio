#!/bin/bash

./02_MakeRamio.sh || exit
./02_MakeRamioCore.sh || exit
./03_MakeExamples.sh || exit
./04_MakeTests.sh || exit
./04_RunTests.sh || exit


