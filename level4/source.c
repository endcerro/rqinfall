unsigned int m;

void p(char *param_1)
{
    printf(param_1);
    return;
}
void n(void)
{
    char read_buffer [512];
    fgets(read_buffer, 512, stdin);
    p(read_buffer);
    if (m == 0x1025544) {
        system("/bin/cat /home/user/level5/.pass");
    }
    return;
}

void main(void)
{
    n();
    return;
}

