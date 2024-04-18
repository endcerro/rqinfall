

void p(char *param_1,char *param_2)
{
    char read_buffer [4104];

    puts(param_2);
    
    read(0,read_buffer,4096);
    {
        char *tmp = strchr(read_buffer, '\n');
        *tmp = '\0';
    }
    strncpy(param_1, read_buffer, 20);
    return;
}

void pp(char *param_1)
{
    char local_buff1 [20];
    char local_buff2 [20];

    p(local_buff1," - ");
    p(local_buff2," - ");
    strcpy(param_1,local_buff1);
    {        
        char *tmp = strchr(param_1, '\0')
        *tmp = ' ';
    }
    strcat(param_1,local_buff2);
    return;
}

int main(void)
{
    char base_buffer [54];

    pp(base_buffer);
    puts(base_buffer);
    return 0;
}
