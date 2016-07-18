#include <stdio.h>
#include "dbg.h"
#include <dlfcn.h>

// A function pointer "lib_function" that takes const char *data
typedef int (*lib_function)(const char *data);

int main(int argc, char *argv[])
{
	int rc = 0;
	check(argc == 4, "USAGE: ex29 libex29.so function data");

	char *lib_file = argv[1];		// first argument = file
	char *func_to_run = argv[2];	// second argument = fucntion
	char *data = argv[3];			// third arg = data

	// dlopen(const char *file, int mode);
	void *lib = dlopen(lib_file, RTLD_NOW);			// load library file
	check(lib != NULL, "Failed to open the library %s: %s", lib_file, dlerror());

	// dlsym(void  *restrict handle, const char *restrict name);
	lib_function func = dlsym(lib, func_to_run);	// get function by string name
	// returns func which is the function in the library
	check(func != NULL, "Did not find %s function in the library %s: %s", func_to_run, lib_file, dlerror());

	rc = func(data);
	check(rc == 0, "Function %s return %d for data: %s", func_to_run, rc, data);

	rc = dlclose(lib);
	check(rc == 0, "Failed to close %s", lib_file);

	return 0;

error:
	return 1;	
}