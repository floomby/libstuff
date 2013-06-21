#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "../src/stuff.h"

void usage_function()
{
	fprintf(stderr, "usage: -n is mandatory\n");
}

int main(int argc, char *argv[])
{
	//set_usage(&usage_function);

	//char *cow;
	//int blah = 895;
	//optparse(argc, argv, "n%d,str%s", &blah, &cow);

	//printf("%s:%d\n", cow, blah);

	int blah = 947;

	cvector_t vec = cvector(int);
	vec.push(&blah);

	printf("%d\n", *(int *)vec.pop());

	return 0;
}