#!/bin/bash

sourcefile=$1
binaryfile="${sourcefile%.*}"
g++ $sourcefile -o $binaryfile
if [ $? == 0 ]; then
    echo "Binary $binaryfile is built successfully"
fi

