#!/bin/bash


echo "Run the OPC-UA client
"

g++ src/main.cpp -o run -L/usr/local/lib -lopen62541

./run
