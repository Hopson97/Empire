#!/bin/bash

if [ "$1" = "release" ]
then
    ./bin/release/empire 
else
    ./bin/debug/empire 
fi