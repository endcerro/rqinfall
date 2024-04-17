void m(void *param_1,int param_2,char *param_3,int param_4,int param_5)
{
    time_t tVar1;

    tVar1 = time((time_t *)0x0);
    printf("%s - %d\n",c,tVar1);
    return;
}

int main(int ac, char** av)
{
    int *buffer1;
    void *pvVar2;
    int *puVar3;
    FILE *stream;

    buffer1 = (char *) malloc(8);   
    buffer1[0] = 1;                 //[1][x]
    buffer1[1] = malloc(8);         //[1][PTR1]
    puVar3 = (int *)malloc(8);
    puVar3[0] = 2;                  //[2][x]
    puVar3[1] = malloc(8);          //[2][PTR2]
    strcpy((char *)buffer1[1],*(char **)(av[1])); //Copies into the malloced buffers
    strcpy((char *)puVar3[1],*(char **)(av[2]));
    stream = fopen("/home/user/level8/.pass","r");
    fgets(c, 68, stream);
    puts("~~");
    return 0;
}