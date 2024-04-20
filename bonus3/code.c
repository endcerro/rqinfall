
int main(int param_1,char** av)
{
  int retval;
  int test_value;
  undefined4 *puVar3;
  byte bVar4;
  char read_buffer[16];
  char local_56 [66];
  FILE *file_ptr;
  
  file_ptr = fopen("/home/user/end/.pass","r");
  puVar3 = read_buffer;
  for (test_value = 33; test_value != 0; test_value -= 1) 
  {
    *puVar3 = 0;
    puVar3 = puVar3  + 1;
  }
  if ((file_ptr == 0) || (param_1 != 2)) 
  {
    retval = -1;
  }
  else 
  {
    fread(read_buffer,1,66, file_ptr);
    test_value = atoi(av[1]);
    read_buffer[test_value] = 0;
    fread(local_56,1,65,file_ptr);
    fclose(file_ptr);
    test_value = strcmp((char *)read_buffer,*(char **)(av[1]));
    if (test_value == 0) 
    {
        execl("/bin/sh","sh",0);
    }
    else 
    {
      puts(local_56);
    }
    retval = 0;
  }
  return retval;
}