//Mixing signed and unsigned integers in arithmetic operations

#include <stdio.h>

int main(void)
{ 
    unsigned int a = 1000;
    signed int b = -1;

    if (a > b) puts("a is more than b");
    else puts("a is less or equal than b"); 

    return 0;
}  
//--------------------------------------------------------
// Overstepping Array Boundaries
// WRONG

#include <stdio.h>
int main()
{
    int x = 0;
    int myArray[5] = { 1,2,3,4,5}; //Declaring 5 elements

    for(x=1; x<=5; x++) //Looping from 1 till 5.
       printf("%d\t",myArray[x]);

    printf("\n");
    return 0;
}


//Output: 2 3 4 5 GarbageValue

// CORRECT

#include <stdio.h>
int main()
{
    int x = 0;
    int myArray[5] = { 1,2,3,4,5}; //Declaring 5 elements

    for(x=0; x<5; x++) //Looping from 0 till 4.
       printf("%d\t",myArray[x]);

    printf("\n");
    return 0;
}

//Output: 1 2 3 4 5

//--------------------------------------------------------
// Missing out the Base Condition in Recursive Function
// WRONG

#include <stdio.h>

int factorial(int n)
{
       return n * factorial(n - 1);
}

int main()
{
    printf("Factorial %d = %d\n", 3, factorial(3));
    return 0;
}
//Typical output: Segmentation fault

// CORRECT

#include <stdio.h>

int factorial(int n)
{
    if (n == 1) // Base Condition, very crucial in designing the recursive functions.
    {
       return 1;
    }
    else
    {
       return n * factorial(n - 1);
    }
}

int main()
{
    printf("Factorial %d = %d\n", 3, factorial(3));
    return 0;
}

//Output :  Factorial 3 = 6

//--------------------------------------------------------
// Using character constants instead of string literals, and vice versa
// Example 1

#include <stdio.h>

int main(void) {
    const char *hello = 'hello, world'; /* bad */
    puts(hello);
    return 0;
}

// Example 2

#include <stdio.h>

int main(void) {
    char c = "a"; /* bad */
    printf("%c\n", c);
    return 0;
}

//--------------------------------------------------------
// Floating point literals are of type double by default

#include <stdio.h>
int main() {
    float  n = 0.1;
    if (n > 0.1) printf("Weird\n");
    return 0;
}
// Prints "Weird" when n is float

//--------------------------------------------------------
// Adding a semicolon to a #define

// WRONG
#define MAX 100;
int arr[MAX];

// The code will be converted to
int arr[100;];

//--------------------------------------------------------
// Be careful with semicolons

if (x > a);
   a = x;

//Means

if (x > a) {}
a = x;

//Another erratic code
if (i < 0) 
    return
day = date[0];
hour = date[1];
minute = date[2];

//--------------------------------------------------------
// Mistakenly writing = instead of == when comparing

/* assign y to x */
if (x = y) {
     /* logic */
}

//Means

if ((x = y) != 0) {
    /* logic */
}

// CORRECT

/* compare if x is equal to y */
if (x == y) {
    /* logic */
}