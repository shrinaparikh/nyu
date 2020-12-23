
#include <stdio.h>

// This program uses masks and shifts to read and 
// write individual bits. 


// This function, given an integer x, prints out all of the
// individual bits of x. That is, it prints x as a binary number.
// It is defined below.

void print_bits(int x); 



int main()
{
  int x, bit;

  // This portion of the code reads in an integer and a
  // bit position and indicates if that bit position in
  // the integer contains a 1 or  a 0.
  
  printf("Enter a number and bit position > ");
  scanf("%d %d", &x, &bit);

  // A mask variable should always be unsigned (see email to class).
  // In this case, the mask is a 1 in the specified bit
  // position and a 0 everywhere else. This is accomplished
  // by taking the value 1 and shifting it to the left until
  // the 1 resides in the desired bit position.

  unsigned int mask = 1 << bit ;

  // Performing the bitwise and (&) operation on x and
  // the mask results in a non-zero value if x has a 1
  // in the specified bit position, and a zero otherwise.
  // The "if (...)" below only works because any non-zero
  // value is interpreted as TRUE and zero is interpreted
  // as FALSE.
  
  if (x & mask)
    printf("bit %d of %d is 1\n", bit, x);
  else
    printf("bit %d of %d is 0\n", bit, x);


  // Printing out x as a binary number (with leading zeros).
  
  printf("%d as a %lu-bit binary number is: ", x, sizeof(x) * 8);
  print_bits(x);

  
  // The above code gave examples of reading a particular
  // bit position in a variable.

  // The code below gives examples of setting (to 1) a bit
  // in a variable and clearing (to 0) a bit in the variable.
  
  // Use bitwise-OR and a mask to set a bit position to 1. 


  printf("Which bit should be set to 1? > ");
  scanf("%d", &bit);

  // The mask should be (1 << bit), which gets OR'd with x.
  // Be sure to write the resulting value back to x, otherwise
  // x won't be changed.

  x = x | ( 1 << bit);   // sets the specified bit of x to 1
    
  printf("x is now %d, which is ", x);
  print_bits(x);
  
  // To clear a bit (set it to 0):
  //  - use ~ (complement) to create a mask,
  //  - use & (and) to clear the bit using the mask

  printf("Which bit should be cleared (set to 0)? > ");
  scanf("%d", &bit);

  // Here, the mask we use should have a 0 in the specified bit
  // position and a 1 everywhere else.  We do that by initially
  // creating a value that has a 1 in the specified bit position
  // and a 0 everywhere else, i.e. (1 << bit), and then flipping
  // every bit using the ~ (not) operator, i.e. ~(1 << bit).
  // We then AND that mask with x to create a zero in the specified
  // bit position of x. Again, be sure to write the value back to x.
  
  x = x & ~(1 << bit);

  printf("x is now %d, which is ", x);
  print_bits(x);
}

  


void print_bits(int x)
{


  // To print the individual bits of x, a mask is used. 
  // The mask starts off with a 1 in the leftmost
  // bit position and, in a loop, is shifted to the right by
  // one bit each time.

  // It is important to declare the mask as an unsigned int.

  unsigned int mask;

  // Rather than assume that x is 32 bits, we use "sizeof(x) * 8"
  // to convert the number of bytes in x to bits.

  // The mask is set to a 1 in the leftmost position, followed by all 0's.
  
  mask = 1 << ((sizeof(x) * 8) - 1);

  for (int i = 0; i < sizeof(x) * 8; i++) {
    if (x & mask)
      printf("1");
    else
      printf("0");
    mask = mask >> 1;
  }
  printf("\n");
}
