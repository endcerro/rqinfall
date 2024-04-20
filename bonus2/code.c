void greetuser(void)

{
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined2 local_3c;
  undefined local_3a;
  
  if (language == 1) {
    local_4c._0_1_ = 'H';
    local_4c._1_1_ = 'y';
    local_4c._2_1_ = 'v';
    local_4c._3_1_ = -0x3d;
    local_48._0_1_ = -0x5c;
    local_48._1_1_ = -0x3d;
    local_48._2_1_ = -0x5c;
    local_48._3_1_ = ' ';
    local_44._0_1_ = 'p';
    local_44._1_1_ = -0x3d;
    local_44._2_1_ = -0x5c;
    local_44._3_1_ = 'i';
    local_40 = 0xc3a4c376;
    local_3c = 0x20a4;
    local_3a = 0;
  }
  else if (language == 2) {
    local_4c._0_1_ = 'G';
    local_4c._1_1_ = 'o';
    local_4c._2_1_ = 'e';
    local_4c._3_1_ = 'd';
    local_48._0_1_ = 'e';
    local_48._1_1_ = 'm';
    local_48._2_1_ = 'i';
    local_48._3_1_ = 'd';
    local_44._0_1_ = 'd';
    local_44._1_1_ = 'a';
    local_44._2_1_ = 'g';
    local_44._3_1_ = '!';
    local_40 = CONCAT22(local_40._2_2_,32);
  }
  else if (language == 0) {
    local_4c._0_1_ = 'H';
    local_4c._1_1_ = 'e';
    local_4c._2_1_ = 'l';
    local_4c._3_1_ = 'l';
    local_48._0_3_ = 'o';
  }
  strcat((char *)&local_4c,&stack0x00000004);
  puts((char *)&local_4c);
  return;
}


int main(int param_1,char* av)
{
    undefined4 uVar1;
    int iVar2;
    undefined4 *puVar3;
    undefined4 *puVar4;

    char buffer1 [40];
    char buffer2 [36];
    char *env_ptr;

    if (param_1 == 3) 
    {
        puVar3 = buffer1;
        for (iVar2 = 19; iVar2 != 0; iVar2 = iVar2 -1) 
        {
            *puVar3 = 0;
            puVar3 = puVar3 + 1;
        }
        strncpy((char *)buffer1,*(char **)(av[1]),40);
        strncpy(buffer2,*(char **)(av[2]),32);
        env_ptr = getenv("LANG");
        if (env_ptr != (char *)0x0) 
        {
            iVar2 = memcmp(env_ptr,"fi",2);
            if (iVar2 == 0) 
                language = 1;
            else 
            {
                iVar2 = memcmp(env_ptr, "nl", 2);
                if (iVar2 == 0) 
                    language = 2;
            }
        }
        puVar3 = buffer1;
        puVar4 = (undefined4 *)&stack0xffffff50;
        for (iVar2 = 0x13; iVar2 != 0; iVar2 = iVar2 + -1) 
        {
            *puVar4 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar4 = puVar4 + 1;
        }
        uVar1 = greetuser();
    }
    else 
    {
        uVar1 = 1;
    }
    return uVar1;
}

