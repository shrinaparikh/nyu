
#include <stdio.h>

// This prints out the bits in any 32-bit quantity (int, unsigned int, float, etc.).
// It's necessary to pass the address of the quantity, and for the parameter p
// to be pointer, to avoid the compiler performing a conversion on the value.

void print_32_bits(void *p)   // p is a void *, so can be a pointer to anything.
{
  unsigned int mask = 1 << 31;
  unsigned int x =  *((unsigned int *) p);   // cast p to an (unsigned int *) before
                                             // dereferencing p.
  for(int i = 0; i < 32; i++) {
    if (x & mask)
      printf("1");
    else
      printf("0");
    mask >>= 1;
  }
  printf("\n");
}

#define EXP_SIZE 8
#define FRACTION_SIZE 23

// This prints out the bits in each field of an IEEE 32-bit floating point number,
// namely the sign bit, the 8 exponent bits, and the 23 fraction bits.

void print_bits_fp32(float f)
{

  // This code is a little different from the print_32_bits() code, above.
  // Here, we set p to point to the floating point number and then
  // dereference p each time through the loop.  Either way is fine.
  
  unsigned int mask = (1 << 31);
  unsigned int *p = (unsigned int *) &f;
  printf("%4.2f is stored as follows:\n", f);
  printf("Sign bit is ");
  if (*p & mask)
    printf("1\n");
  else
    printf("0\n");

  mask >>= 1;
  printf("Exponents bits are: ");
  for(int i = 0; i < EXP_SIZE; i++) {
    if (*p & mask)
      printf("1");
    else
      printf("0");
    mask >>= 1;
  }
  printf("\n");

  printf("Fraction bits are: ");
  for(int i = 0; i < FRACTION_SIZE; i++) {
    if (*p & mask)
      printf("1");
    else
      printf("0");
    mask >>= 1;
  }
  printf("\n");
}


int main()
{
  // Printing the bits of an int.
  int y = 33;
  printf("y = %d = ", y);
  print_32_bits(&y);

  // Printing the bits of a floating point number,
  // represented in 32-bit IEEE floating point format.
  float f = 32.5;
  printf("f = %4.2f = ", f);
  print_32_bits(&f);

  // Print the bits of the floating point number, showing the
  // individual fields (sign, exponent, fraction).
  
  print_bits_fp32(f);
}
   
