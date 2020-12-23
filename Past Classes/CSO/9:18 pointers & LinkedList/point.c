
#include <stdio.h>



// This defines a struct (record type)  named "myStruct" with
// integer fields x, y, and z. In order to declare variables
// of this type, you need to say "struct myStruct". See below.

struct myStruct {
  int x;
  int y;
  int z;
};


// C uses "Pass by value" parameter passing, in which the value
// of the actual parameter (aka "argument") copied into the
// formal parameter. Thus, within a function, assigning to
// the formal parameter will have no effect on the actual parameter. (ex below)

// This is an example of a function that modifies it's formal parameter,
// but that has no effect on the actual parameter. Note that
// bad_increment(y) is called below, but incrementing x has
// no effect on the value of y.

void bad_increment(int x)
{
  x++;
  printf("x = %d\n", x);
}

// In order for a function to be able to modify a variable where the
// function is called, the address of the variable has to be passed
// into the function. See the call to increment(&y) below, using the
// address-of operator. Therefore, the formal parameter in increment()
// has to be declared to be a pointer.

void increment(int *px)   // the formal parameter px is an int pointer.
{
  *px = *px + 1;     // could also write "(*px)++;"
    
    //this changes the actual parameter as it does an operation on the val the pointer points to
}


// Here's what happens when you do pointer arithmetic when you
// shouldn't. You may end up accidentally overwriting stuff you need.

void yuck()
{
  int a = 3;
  int b = 4;
  int c = 5;
  int *p = &b;  // p points to b.
  
  printf("a = %d, b = %d, c = %d\n", a, b, c);
  p++;  // What does p point to now? Who knows!

  *p = 10;  // Overwriting whatever p points to with 10
  
  printf("a = %d, b = %d, c = %d\n", a, b, c);  // Check the output.
                                                // a has changed!!!
}
  

int main()
{
  int y = 8;
  bad_increment(y);  // passing in the value of y has no effect.
  printf("y = %d\n", y);   // y is still 8

  increment(&y);  // now passing the address of y.

  //Sure enough, y is changed.
  
  printf("After the good increment, y = %d\n", y);

  yuck();


  // See the above definition of "struct myStruct".
  // Here, we are declaring a variable struc of type
  // "struct myStruct" and accessing its fields using
  // the dot notation, struc.x, etc.
  

  struct myStruct struc;
  struc.x = 30;
  struc.y = 50;
  struc.z = 70;

  printf("The total is %d\n", struc.x + struc.y + struc.z);
}
