
#include <stdio.h>

// Global variable. This one is an int, i.e. holds a signed
// (i.e. negative or non-negative) integer. The size
// depends on the compiler and machine. For GCC on an
// Intel x86 processor (32 or 64-bit), the size is
// 32 bits(4 bytes).

int x = 0;

int main()
{
  // The "char" type is 1 byte (8 bits). It can be used to hold
  // a character (represented by an 8-bit number according to the
  // ASCII table) or an 8-bit signed integer.
  
  char y = 'A';  // The ASCII code for the letter 'A' is 65. So, what
                 // is stored in the variable y is the number 65.

  char z = 65;  // The variable z also stores the 8-bit number 65. That is,
                // z's value is exactly the same as y's.


  // Note that you can print y az a number and z as a character. That is
  // there is no difference between a character and the corresponding
  // 8-bit number ASCII value.
  
  printf("%d\n", y);  // prints 65
  printf("%c\n", z);  // prints 'A'
  

  // The "float" type represents a floating point number. In our case,
  // using GCC on an x86 processor, the number is represented by 32 bits.
  
  float f;
  f = 45.67;

  { // A "block", i.e. a portion of the program starting with "{" and
    // ending with "}", defines a new "scope".  A "scope" defines where
    // variables are visible. In particular, any variable declared within
    // this scope is only visible within the scope (starting from where the
    // variable is declared.

    // This is a new variable f, totally unrelated to the f declared in the
    // outer scope (above).
    
    int f = 20;
    printf("f = %d\n", f);  // This prints 20.

  } // This ends the nested scope in which the integer variable f was declared.

  printf("f = %f\n", f);  // This prints the value of the floating point f
                          // above, since we are outside the scope in which
                          // the integer variable f was declared.
                          // SEE MY SHELL SESSION TO SEE WHAT WAS ACTUALLY PRINTED.
                          // It wasn't 45.67, since 32-bit floating point numbers
                          // may not be able to precisely represent the real number
                          // you may be thinking of.
  
}

