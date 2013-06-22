/********************************************************
 * There is a bug in the make_tramp function
 * to function screws up the stack a little
 * the return anddress and the first parameters
 * on the stack are correct, but it only copies
 * 4 bytes of the last parameter to the stack,
 * Then the push/pop functions segfault when the
 * last parameter is dereferanced(remeber that this
 * is the first paramter of the c function since c 
 * reverses the order of the parameters on the 
 * stack)
 * 
 * To fix this the assembly in the code.asm needs
 * to be fixed and the new assembly moved into the
 * make_tramp function.
 * 
 ********************************************************/

#include "cvector.h"

//if this is the best value then it should not be defined like this
#define GROW_FACTOR	2

//this structure is a bit confusing
struct env {
	struct {
		unsigned size;
		unsigned grow;
		unsigned cur;
		void *data;
	} mem;

	struct {
		size_t size;
	} elem;

	struct env *this_env;		//this points to the current env on the heap
	cvector_t funcs;	//the functions for the object
};

void make_tramp(struct env *vec, void *func, void **member);
void cvector_push(struct env *vec, void *elem);
void *cvector_pop(struct env *vec);

//really this can just be an internal function, otherwise the "constructor" does not have a
//way to know the size of the type being used
cvector_t cvector_intern(size_t size)
{
	struct env *vec = malloc(sizeof(struct env));
	if(!vec){
		perror("malloc");
		exit(ENOMEM);
	}

	printf("made at: %zu\n", vec);

	vec->this_env = vec;

	vec->mem.grow = GROW_FACTOR;
	vec->mem.cur = 0;
	vec->mem.size = 1;
	vec->mem.data = malloc(size);
	if(!vec->mem.data){
		perror("malloc");
		exit(ENOMEM);
	}

	vec->elem.size = size;

	make_tramp(vec, (void *)&cvector_push, (void **)&vec->funcs.push);
	make_tramp(vec, (void *)&cvector_pop, (void **)&vec->funcs.pop);

	return vec->funcs;
}

//if we make the env the first agument then all we have to do is
//make the trampoline push the env* onto the stack
void make_tramp(struct env *vec, void *func, void **member)
{
	//TODO the bug is in this function, half of the assembly properly
	//assumes that this is 64 bit but the pointers are not copied
	//to the stack properly
	
	//TODO since the code is only for amd64 then the complier
	//should throw an error on compilation on none amd64 machines
	
	//this is only the x86_64 code
	char *tramp = malloc(19);
	if(!tramp){
		perror("malloc");
		exit(ENOMEM);
	}

	tramp[0]	= '\xff';
	tramp[1]	= '\x34';
	tramp[2]	= '\x24';
	tramp[3]	= '\x90';
	tramp[4]	= '\x48';
	tramp[5]	= '\xc7';
	tramp[6]	= '\x44';
	tramp[7]	= '\x24';
	tramp[8]	= '\x10';
	memcpy(tramp+9, &vec, 4);
	tramp[13]	= '\x68';
	memcpy(tramp+14, &func, 4);
	tramp[18]	= '\xc3';

	*member = tramp;
}

//all of these functions need speacial care, it is very important
//that the first argument is the env*
void cvector_push(struct env *vec, void *elem)
{
	printf("called push with: %zu\n", vec);

	if(vec->mem.cur == vec->mem.size){
		vec->mem.data = realloc(vec->mem.data, vec->mem.size * vec->mem.grow);
		if(!vec->mem.data){
			perror("realloc");
			exit(ENOMEM);
		}

		vec->mem.size *= vec->mem.grow;
	}

// 	memcpy(vec->mem.data /*+ (vec->elem.size * vec->mem.cur)*/, elem, vec->elem.size);

	vec->mem.cur++;
}

void *cvector_pop(struct env *vec)
{
	printf("called pop with: %zu\n", vec);

	vec->mem.cur--;
	return vec->mem.data /*+ (vec->elem.size * vec->mem.cur)*/;
}

