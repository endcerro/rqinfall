So in this case we have a big binary that reads input and reacts in different ways for certain inputs.
We can see that there is a call to /bin/sh at the bottom of the code and under a specific condition.

There is also two global variables, auth and service
The test is performed on the auth variable, the 32th char needs no to be 0
We cannot copy chars untill this poin tho, since we cannot strcpy if the copied string is more than 30 chars.

The auth value is 0 by default, and we can malloc it by entering
"auth ", it can be filed by strcpy for whats after the space.

We can also trigger another malloc via strdup and it's placed 0x10 after the auth mem location

At this point we can either do another strdup to move another 0x10 and hit the correct range, or do something like that 

python -c "print("auth " + "\n" + "service" + "123456789012345" + "\x0")

python -c 'print("auth " + "\n" + "service" + "123456789012345" + "1")'

and now login works gg 

c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a