#!/bin/sh
gcc -O0 -fsanitize=address bdfi.c -o bdfi.dbg
./bdfi.dbg test.bdf
