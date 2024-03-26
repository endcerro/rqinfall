#include <stdio.h>
#include <string.h>
#include <unistd.h>
void p(char *str)
{
    char *space = " - ";
    char local_buffer[4104];

    puts(space);
    read(0,local_buffer, 0x1000);
    char *pos = strchr(local_buffer, '\n');
    *pos = '\0';
    strncpy(str, local_buffer, 20);
}

void pp(char *str)
{
    char buffer1[20];
    char buffer2[20];

    p(buffer1);
    p(buffer2);
    strcpy(str, buffer1);
    //dest, src

    // char *tmp = strchr(str, '\0');
    // *tmp = ' ';
    strcat(str, buffer2);
    //Dest, stc
}

int main()
{
    char buffer[54];

    pp(buffer);
    puts(buffer);
    return 0;
}