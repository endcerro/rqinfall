This is more tricky.

There is no hidden function, and the only vulnerable function, strcpy, is protected before it being called so no luck arround here.

We can see that we may have a bash call without breaking anything.

There is however two global char*, auth and service.

There is also a system call that launches a shell.

For it to be called, we need to input 'login' while the 32th character of the buffer pointed to by auth is not a 0;

But there is a protection that prevents a copy in the auth buffer for more than 31 chars, so we cannot write directly to the zone that the condition is checking.

But let's remember that stack goes up, heap goes down, as all things do.

We can trigger mallocs with "auth " and "service"

If we launch auth and service one after another, we get two pointers that have only a 0x10 difference it their address, that's 16 bytes.

the service commands also trigger a strdup of some of the content it read.

So at this point we have two solutions.

Trigger auth then two services call, that will move 16 + 16 = 32 bytes in the address range, and we end up on top of the 32 bytes used by the test for the bash

Or we add a bunch of characters after our first 'service' so that they get strdupped and it goes past the contion range.




We cannot spot any function that wants negs to be exploited, but we do find a system /bin/sh call

While we can see a clear path to this call, it cannot be easily obtained.

It will check for one global variable, called auth, at its index 32.

The only issue being that, the only time we will write to it's pointer it will be up to 30 chars even if the malloc.

Which is weird in the first place since the malloc seems to be allocating only 5 bytes.

We can see that when called two su
