#!/bin/bash

sudo ln -s $PWD/../Lib/libRamio.so.0 /usr/local/lib/libRamio.so.0
sudo ln -s $PWD/../Lib/libRamio.so /usr/local/lib/libRamio.so
sudo ldconfig
