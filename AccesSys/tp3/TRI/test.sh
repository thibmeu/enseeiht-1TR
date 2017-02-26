#!/bin/bash

if [ `echo 42` -eq 0 ]; then
    echo true
else
    echo false
fi

name=toto.txt
echo ${name%txt}
