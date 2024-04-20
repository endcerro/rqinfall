int main(undefined4 param_1,int param_2)
{
    undefined4 uVar1;
    undefined local_3c [40];
    int result;

    result = atoi(*(char **)(param_2[1]));
    if (result < 10) 
    {
        memcpy(local_3c,*(void **)(param_2[2]),result * 4);
        if (result == 0x574f4c46) 
        {
            execl("/bin/sh","sh",0);
        }
        uVar1 = 0;
    }
    else 
    {
        uVar1 = 1;
    }
    return uVar1;
}
