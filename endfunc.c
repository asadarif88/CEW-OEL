#include<stdio.h>
#include<stdlib.h>
#include "endfunc.h"
void run_bash_script(const char *script_path) {
    // Use the system() function to execute the bash script
    int status = system(script_path);
}
