#!/usr/bin/env bash

sudo apt-get update --yes
sudo apt-get install --yes cmake
sudo apt-get install --yes libgtest-dev
sudo apt-get install --yes valgrind
sudo apt-get install --yes cppcheck
sudo apt-get install --yes curl
sudo apt-get install --yes wget
sudo apt-get install --yes unzip
export CODECOV_TOKEN="f595c59d-c930-48e3-8c8c-dbff8bd00453"
cd /usr/src/gtest && sudo mkdir build && cd build 
sudo cmake .. && sudo make && sudo cp *.a /usr/lib
