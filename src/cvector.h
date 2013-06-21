#ifndef CVECTOR_H_INCLUDED
#define CVECTOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>

//this is what is really done when a cvector is "constructed"
#define cvector(x)	(cvector_intern(sizeof(x)))

//oviously there is no way to do type checking(or is there)
typedef struct {
	void (*push)(void *elem);
	void *(*pop)();
} cvector_t;

cvector_t cvector_intern(size_t size);

#endif//CVECTOR_H_INCLUDED