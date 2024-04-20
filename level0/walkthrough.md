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
No RELRO        No canary found   NX enabled    No PIE          No RPATH   No RUNPATH   /home/user/level0/level0
```

For this first level we have a suid binary in our home.
https://reverseengineering.stackexchange.com/questions/13928/managing-inputs-for-payload-injection


```ls -l
-rwsr-x---+ 1 level1 users 747441 Mar  6  2016 level0
./level0 Segmentation fault (core dumped)
```
It segfaults with no args so it uses our input for processing somehow.

We cannot ltrace it, go gdb

Looking at main we see two lines that are promising

```gdb
   0x08048ed4 <+20>:	call   0x8049710 <atoi>
   0x08048ed9 <+25>:	cmp    $0x1a7,%eax
   (gdb) printf "%d\n", 0x1a7
   423
```
