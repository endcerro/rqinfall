char *auth = 0;
char *service = 0;

int main(void)
{
    char    *gets_buffer;
    char    actual_buffer[5];
    char    second_buffer[2];
    char    big_buffer[125];
    bool    test1;
    while(true)
    {
        printf("%p, %p \n",auth,service);
        if (fgets(actual_buffer, 128, stdin) == 0)
            return;
        test1 = false;

        if (strncmp("auth ", actual_buffer, 5))
        {
            auth = malloc(4);
            *auth = 0;
            if (strlen(actual_buffer) < 31)
            {
                strcpy(auth, second_buffer);
            }
        }
        if (strncmp("reset", actual_buffer, 5))
        {
            free(auth);
        }
        if (strncmp("service", actual_buffer, 6))
        {
            service = strdup(second_buffer);
        }
        if (strncmp("login", actual_buffer, 5))
        {
            if (auth[32] == 0)
            {
                fwrite("Password:\n",1 ,10, stdout);
            }
            else
            {
                system("/bin/sh");
            }
        }
    }
}