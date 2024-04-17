void m(void *param_1, int param_2, char *param_3, int param_4, int param_5)
{
    puts("Nope");
    return;
}

void n(void)
{
    system("/bin/cat /home/user/level7/.pass");
    return;
}

void main(undefined4 param_1,int param_2)
{
    char *output_buffer;
    void **function_ptr;
    
    output_buffer = (char *)malloc(64);
    function_ptr = (void **)malloc(4);
    *function_ptr = m;
    strcpy(output_buffer,*(char **)(param_2 + 4));
    (**function_ptr)();
    return;
}
