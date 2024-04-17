void n(void)
{
    char read_buffer [512];

    fgets(read_buffer, 512, stdin);
    printf(read_buffer);
    /* WARNING: Subroutine does not return */
    exit(1);
}

void o(void)
{
    system("/bin/sh");
    /* WARNING: Subroutine does not return */
    _exit(1);
}
void main(void)
{
    n();
    return;
}

