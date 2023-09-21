#!/bin/bash

clear

source_files="main.c prog1.c slp.c util.c"

gcc $source_files -o A

if [ $? -eq 0 ]; then
    echo "Build successful. Executable: A"
else
    echo "Build failed."
fi
