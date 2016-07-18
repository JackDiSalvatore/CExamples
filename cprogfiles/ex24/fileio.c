/*
*	Example 24, introduction to file input and output
*/

#include <stdio.h>
#include "../dbg.h"

#define	MAX_DATA	100

/*	GLOBLES	*/

typedef enum EyeColor {

	BLUE_EYES,
	GREEN_EYES,
	BROWN_EYES,
	BLACK_EYES,
	OTHER_EYES

} EyeColor;	// creates a var type called "EyeColor" that is this enum

const char *EYE_COLOR_NAMES[] = {"Blue", "Green", "Brown", "Black", "Other"};

struct Person {

	int age;
	double height;
	double weight;
	char first_name[MAX_DATA];
	char last_name[MAX_DATA];
	EyeColor eyes;
	float income;

};

void print_results(struct Person prsnToBePrinted)
{
	printf("\n---------RESULTS---------\n\n");
	printf("First Name:\t %s", prsnToBePrinted.first_name);
	printf("Last Name:\t %s", prsnToBePrinted.last_name);
	printf("Age:\t\t %d years old\n", prsnToBePrinted.age);
	printf("Height:\t\t %.2lf inches\n", prsnToBePrinted.height);
	printf("Weight:\t\t %.2lf lbs\n", prsnToBePrinted.weight);
	printf("Eye Color:\t %s\n", EYE_COLOR_NAMES[prsnToBePrinted.eyes]);
	printf("Income:\t\t $%.2f\n", prsnToBePrinted.income);
}

int prog_body()
{
		printf("\nProgram Start...\n\n");

	/* Create Person struct called you */
	struct Person you = {
			.age = 0,		//you.age = 0;
			.height = 0,
			.weight = 0
	};

	int i = 0;
	int k = 0;
	char *in = NULL;	// char pointers to begining of unknown array


	/* First Name */
	printf("What is your First Name?: \t");
	/*
	*	fgets - "file get string"
	*	fgets( destination, size, file stream you want to get it from )
	*/
	in = fgets(you.first_name, MAX_DATA-1, stdin);
	check(in != NULL, "Did not read any input");

	/* Last Name */
	printf("What is your Last Name?: \t");
	in = fgets(you.last_name, MAX_DATA-1, stdin);
	check(in != NULL, "Did not read any input");

	/* Height */
	printf("What is your height (inches) ?: ");
	/*
	*	fscanf - "file scan"
	*	fscanf( file stream you get from, "%varType", address to save )
	*/
	k = fscanf(stdin, "%lf", &you.height);
	check(k > 0, "Did not read any input");

	/* Weight */
	printf("What is your weight (lbs) ?: \t");
	k = fscanf(stdin, "%lf", &you.weight);
	check(k > 0, "Did not read any input");

	/* Age */
	printf("What is your age (years) ?: \t");
	k = fscanf(stdin, "%d", &you.age);
	check(k > 0, "Did not read any input");

	/* Eyecolor */
	printf("Select eye color: ");
	printf("\n");
	for(i = 1; i <= OTHER_EYES; i++) {
		printf("%d) %s \n", i, EYE_COLOR_NAMES[i-1]);
	}
	printf("-> ");

	int eyes;
	k = fscanf(stdin, "%d", &eyes);
	check(k > 0 && k < OTHER_EYES, "Input must be a number listed");

	you.eyes = eyes - 1;
	check(0 <= you.eyes && OTHER_EYES >= you.eyes, "Invalid Numver, must be 0, 1, 2, 3, 4");

	/* Income */
	printf("How much do you make (usd) ?: \t");
	k = fscanf(stdin, "%f", &you.income);
	check(k > 0, "Must be floating point number");

	print_results(you);

	printf("\n\nProgram End\n\n");

	return 1;

error:
	return -1;
}

/*******************************************************************************
*	Main:
*	Arguments:
*	Returns:
*******************************************************************************/
int main(int argc, char *argv[])
{
	prog_body();

	return 1;
}