#ifndef AUTO_FREE_H_INCLUDED
#define AUTO_FREE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

void auto_free_add(void *x);
int auto_free_count();

#endif//AUTO_FREE_H_INCLUDED