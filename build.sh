#!/bin/sh

mkdir build
g++ -std=c++11 convto.cpp -o build/convto
g++ -std=c++11 convfrom.cpp -o build/convfrom
