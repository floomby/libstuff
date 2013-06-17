#ifndef OPTPARSE_H_INCLUDED
#define OPTPARSE_H_INCLUDED

#include <stdarg.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#include "auto_free.h"

//TODO change from a function to a string
void set_usage(void (*usage)());
void optparse(int argc, char *argv[], char *fmt, ...);

#endif//OPTPARSE_H_INCLUDED
