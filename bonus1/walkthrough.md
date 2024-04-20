This time arround there is a exec shell in the main so no need for a shellcode.

The path to this exec is behind two conditions: 
    The result of an atoi that's taken from our first parameter must be less than 10
    But at the same times it needs to be equal to 0x574f4c46

So the value needs to change in between the checks, thankfully we have a memcpy call that targets a 40 wide buffer that's located above our int

So we should try and overflow it into our int to set a good value for it, or maybe overflow the return pointer to the exec call

The target looks like this
```
HexInspector: 0x574f4c46 (4B)

Decimal:  1,464,814,662
Binary:   01010111 01001111 01001100 01000110
Float32:  227926498869248
Ascii:    FLOW
```

But we still have an issue, we cannot overflow the buffer with a positive value that's less than ten, so we should try a negative number in atoi, since it will pass the check and memcpy will take it as un unsigned int, so a big number

With the code in ressources, we seem to find two candidates that will pass the check and allow us to copy 44 bytes into the buffer, enough to fill it and overflow into our int


-1073741813 and -2147483637

So now we can build our second arg

$(python -c 'print("A" * 40 + "FLOW")')

