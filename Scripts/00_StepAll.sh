#!/bin/bash

./01_MakeRamio.sh || exit
./02_MakeExamples.sh || exit
./03_MakeTests.sh || exit
./04_RunTests.sh || exit


