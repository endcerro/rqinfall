#include <stdlib.h>
#include <stdio.h>
int m = 0;
void v(void)
{
    char input_buffer[520];
    fgets(input_buffer, 512, stdin);
    printf(input_buffer);
    if (m == 64) 
    {
        fwrite("Wait what?!\n",1,12,stdout);
        system("/bin/sh");
    }
    return;
}

void main(void)
{
    v();
    return;
}


