#!/bin/bash
cd linux
g++ pgtest.cpp -o pgtest
chmod +x pgtest
./pgtest > pgtest.txt