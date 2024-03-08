#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    char *auth = NULL;
    char *service = NULL;
    char read_buffer[128]; // Uses to be local90
    while (true)
    {
        printf("%p, %p \n",auth, service);
        if (fgets(read_buffer, 128, stdin) == NULL)
        {
            return 0; // Case if stdin sent EOF
        }
        if (strncmp(read_buffer, "auth ", 5) == 0)
        {
            auth = malloc(4);
            *auth = 0;
            unsigned int test = UINT_MAX;
            
        }
    }
    return 0;
}