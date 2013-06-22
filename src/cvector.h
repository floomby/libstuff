#ifndef CVECTOR_H_INCLUDED
#define CVECTOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>

//the heap trampolines that I am using are only supported on
//amd64 right now

#ifndef __x86_64__
#error "this code only runs on amd64, support for x86 and other arch is coming"
#endif

//this is what is really done when a cvector is "constructed"
#define cvector(x)	(cvector_intern(sizeof(x)))

//oviously there is no way to do type checking(or is there)
typedef struct {
	void (*push)(void *elem);
	void *(*pop)();
} cvector_t;

cvector_t cvector_intern(size_t size);

#endif//CVECTOR_H_INCLUDED
