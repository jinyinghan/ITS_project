#!/bin/bash

rm try
g++ myUi.cpp -o try -lcurses -fpermissive
./try
