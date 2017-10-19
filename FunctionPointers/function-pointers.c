#include <stdio.h>

int TheRealFunction (unsigned long address);
int (*pointerToFunction) (unsigned long address);

const char *(*pointerToFunctionThatReturnsAPointerToChar) (void);

int *pointer;
int *returnedPointer;


int TheRealFunction (unsigned long address)
{
    return address;
}

int *FunctionReturnsPointerToInt(void)
{
    static int a[10];
    int i;
    
    for(i = 0; i < 10; ++i)
        a[i] = i;
    
    return a;
}

const char *FunctionReturnsPointerToChar(void)
{
    const char *message = "Hello World";
    
    return message;
}

int main()
{
    int idx;
    int normalInteger = 10;
    pointer = &normalInteger;

    /* This is a normal pointer */
    printf("%d\n", *pointer);

    /* This variable points to a function 
       and you can now use it just like said function */
    pointerToFunction = &TheRealFunction;
    printf("%d\n", TheRealFunction(53));
    printf("%d\n", pointerToFunction(53));

    /* This function returns a pointer */
    returnedPointer = FunctionReturnsPointerToInt();

    for(idx = 0; idx < 10; idx++)
        printf("%d\n", *(returnedPointer + idx));

    /* This function points to another function
       and you can use it just like said function */
    pointerToFunctionThatReturnsAPointerToChar = &FunctionReturnsPointerToChar;
    printf("%s\n", FunctionReturnsPointerToChar());
    printf("%s\n", pointerToFunctionThatReturnsAPointerToChar());

    printf("\n-DONE-\n");
    return 0;
}
