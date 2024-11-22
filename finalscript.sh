#!/bin/bash
export PATH="/usr/bin:/bin:/usr/local/bin"
/usr/bin/gcc cJSON.c startfun.c endfunc.c done.c -o ok
./ok
