#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    int result;
    result = atoi(argv[1]);
    if (result == 423){
        const char *execv_arg = strdup("/bin/sh");
        execv("/bin/sh", (char * const*)execv_arg);
        free((void*)execv_arg);
        }
    else
        fwrite("No !\n",1,5,stderr);
    return 0;
}
