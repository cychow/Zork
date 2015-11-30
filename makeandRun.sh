#! /bin/sh
rm ./zork.exe 
g++ -g -Wall zork.cpp tinyxml2/tinyxml2.cpp -o zork.exe 
./zork.exe $1