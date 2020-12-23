
#include <stdio.h>


// Preprocessor "directives" (commands) can be
// used to define constants. The convention is to use
// upper-case letters when naming a constant.

#define MYVAL 10


// C has no built-in boolean type, rather it uses
// integers to represent true and false. In particular:
//  - zero represents "false"
//  - any non-zero value represents true.
// Thus, to make your code clearer, it is helpful to define your
// own constants TRUE and FALSE.

#define TRUE 1
#define FALSE 0

// If you want to define a function below where it is used, you'll
// need to let the compiler know the name, return type, and parameter
// type of the function above where it is first used. That is done
// by writing a "prototype" (aka "signature") for the function:

void buggy(int y);    // this is the prototype for the buggy function, below.
                      // The "void" return type means it doesn't return anything.

void fixed(int y);    // prototype for the fixed function, below.


int main()
{
  buggy(7);  // call to buggy, below, passing the value 7.

  fixed(7);  // called to fixed. See the difference in the output
             // for buggy and for fixed.
}


// Note that 7 is getting passed in to y (see above). 

void buggy(int y)
{
  int x = 5;  // Since x is 5 and y is 7, they are not equal.

  // BUG BELOW! Note that I have used the assignment operator "=" rather than the
  // equality operator "==".  Thus, x is getting assigned the value of the
  // parameter y (which is 7, see above), and the value of the "x = y" expression
  // is the value that got assigned, namely 7.  Since anything that is not zero
  // is interpreted as the boolean true, the "if" statement thinks the condition
  // is true, so "Yes, x = 7" gets printed. 

  if (x = y) 
    printf("Yes, x = %d\n", x);
  else
    printf("No, x = %d\n", x);
  
}


void fixed(int y)
{
  int x = 5;  // Since x is 5 and y is 7, they are not equal.

  int comparison_result = FALSE;
  
  // The bug in the above function has been fixed. Now the correct
  // equality operator is being used. Since x is not equal to y,
  // "No, x = 5" is printed.
  
  if (x == y) 
    printf("Yes, x = %d\n", x);
  else
    printf("No, x = %d\n", x);


  // As a suggestion, if checking to see if a variable is equal to a given constant,
  // put the constant before the equality operator and the variable after it. That
  // way, if you accidentally write a "=" instead of a "==", the compiler will generate
  // an error -- and it will be one less bug to track down.

  if (MYVAL == x)    // comparing X to the MYVAL constant, above.
    comparison_result = TRUE;
  else
    comparison_result = FALSE;

  // If you accidentally write

  //    if (MYVAL = x) ...

  // it will be a compiler error.  If instead you accidentally write

  //    if (x = MYVAL) ...

  // this is will overwrite x and be interpreted as true (whether or not
  // x was originally equal to MYVAL.

  if (comparison_result)
    printf("Yes\n");
  else
    printf("No\n");
}
