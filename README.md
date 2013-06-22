libstuff
========

Random things to make coding in c quicker and less painful.

This project stemed from my frustration with the lack of getopt
on windows except through cygwin, which  is a bit of a pain, compared
to using an entirely native toolchain with mingw and all native code.

When writing the option parser I realized that the interface could be
more transparent to the user if they did not have to free everything
manualy. This lead me to create a system to free memory on program
ecit. While modern operating systems should not care whether you free
all your memory on exit it is still good practice and make the program
more freindly to the system. 

Freeing all the memory on exit is good, but is not true garbage
collection. True garbage collection would free memory once it goes
out of scope. I am pretty sure that unless the complier support
this it is impossible to implement in code. (If someone knows how to
do it in c I would love to here how)

Then looking for other things that I find myself missing in c is
the c++ vecotrs. Implementing them in c is not that hard if you
settle for using void pointers and not passing the pointer to the
vector to the functions that opperate on the vectors. I was not
satisfied with need to pass in the pointer to the instanve of vector
each time I opperated on it so I decided that each vector could have
a pointer to itself (this this pointer from c++) and a function that
calls the individual vector opperations by thunk. The downside of
this is the function have to be dynaically construced for each instance
of a vector. To do this I had to make the heap executable and put the
function on the heap. The function only serves as a trampoline to the
normal vector function by putting the this pointer on the stack.

This method has one huge downside, it requires the heap to be executable.
This drastcaly reduces the security of the program in the case of a heap
buffer overflow. While it would normaly be hard to take advatage of a
heap buffer overflow it is now a cake walk, so this serves as a warning
to be very carefull when using this code.

The method I am using to make the cvector object will be generalized in
a way allowing arbitarry objects to be created easily with use of macros.


NOTES:

The template objects suffer from the fact that c does not allow function
overloading nor does c have any concept of run time types. I am looking
for a way to use macros to create type indepency in the templates. This
might look like the c++ name mangaling system just all preformed by the
preprosesor. This would remove the need for void pointers entirely from
the interface that the templates have and make them nearly as powerful
as their c++ role models (minus inheritance and the like).
