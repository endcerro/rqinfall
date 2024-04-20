int main(int ac, char **av)
{
    // int test = atoi(av[1]);
    // printf("%d AND %u", test, (unsigned int)test);

    int i = 0;
    while(1)
    {
        i -= 1;
        if ((unsigned int)i * 4 == 44 && i < 0)
        {
            printf("Found candidate : %d %u\n", i, (unsigned int)i);
            printf("memcpy size = %u\n", ((unsigned int) i) * 4);
        }
    }
    return 0;
}