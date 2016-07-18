/**********************************************************************************************
* Example 27a: Safe way to copy strings
*
***********************************************************************************************/

#undef NDEBUG
#include "../dbg.h"
#include <stdio.h>
#include <assert.h>

/*
*  Naive copy that assumes all inputs are always valid
*  taken from K&R C and cleaned up a bit
*/
void copy(char to[], char from[])
{
	int i = 0;

	// while loop will not end if from isnt '\0' terminated
	while((to[i] = from[i]) != '\0') {
		++i;
	}
}

/*
*  A safer version that checks for many common errors using the length
*  of each string to control the loops and termination
*/
int safercopy(int from_len, char *from, int to_len, char *to)
{
	assert(from != NULL && to != NULL && "from and to can't be NULL");
	int i = 0;
	/* terenary operator X ? Y : Z, if X, then Y, if not X, then Z */
	/* if 'from' is larger then 'to', 'to' is max. else 'from' is max */
	int max = from_len > to_len - 1 ? to_len - 1 : from_len;

	/* to_len mush have at least 1 byte */
	if(from_len < 0 || to_len <= 0) return -1;

	for(i = 0; i < max; i++) {
		to[i] = from[i];
	}

	/* make sure that the last element of to is null */
	to[to_len -1] = '\0';

	return i;
}

int progInit()
{
	/* careful to understand why we can get these sizes */
	char from[256];
	int from_len = sizeof(from);

	/* notice that it's 7 chars + \0 */
	char to[256];
	int to_len = sizeof(to);

	printf("Enter a string to be copied\n");
	gets(from);
	check(sizeof(from) <= 256, "String to long");

	printf("Enter a string to be overwritten\n");
	gets(to);
	check(sizeof(to) <= 256, "String to long");
	printf("\n");

	debug("Copying '%s' : size of %d - to -  '%s' : size of %d", from, from_len, to, to_len);

	int rc = safercopy(from_len, from, to_len, to);
	check(rc > 0, "Failed to safercopy.");
	check(to[to_len -1] == '\0', "String not terminated.");

	debug("String copied is: '%s': size of %d", to, to_len);

	/* Now try to break it */
	rc = safercopy(from_len * -1, from, to_len, to);
	check(rc == -1, "safercopy should fail #1");
	check(to[to_len - 1] == '\0', "String not terminated.");

	rc = safercopy(from_len, from, 0, to);
	check(rc == -1, "safercopy should fail #2");
	check(to[to_len - 1] == '\0', "String not terminated");

	return 0;

error:
	return 1;
}

int main(int argc, char *argv[])
{
	/* Starting Program */
	printf("\nProgram begin ... \n\n\n");

	progInit();

	printf("\n\nEnd of program\n");

	return 1;
}
