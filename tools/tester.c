#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../src/stuff.h"

void usage_function()
{
	fprintf(stderr, "usage: -n is mandatory\n");
}

int main(int argc, char *argv[])
{
	set_usage(&usage_function);

	char *cow;
	int blah = 895;
	optparse(argc, argv, "n%md,str%ms", &blah, &cow);

	printf("%s:%d\n", cow, blah);

	return 0;
}