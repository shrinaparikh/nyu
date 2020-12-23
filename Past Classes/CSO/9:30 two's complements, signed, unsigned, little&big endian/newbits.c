
#include <stdio.h>

void print_bits(int x);


int main()
{
  // This code is used to indicate the byte-order ("little endian"
  // or "big endian") of integers.  On an Intel x86 processor,
  // which is little endian, the least significant byte will
  // occupy the lowest (i.e. first) of the four consecutive bytes
  // in memory.

  // In this example, on an Intel processor, the output will
  // be 0b 0a 09 08, since 0b is the value of the least
  // significant byte (and thus the first byte of the four
  // bytes occupied by x).
  
  unsigned int x = 0x08090a0b;
  printf("x = %08x\n", x);

  // To print the individual bytes, set an unsigned char
  // pointer to point to x, then use it to print out the
  // bytes.
  unsigned char *p = (unsigned char *) &x;   // don't forget the cast.
    
  // Iterate over the bytes. Since there is really no difference
  // between a pointer and an array, you can use array notation
  // with p (i.e. "p[...]").

  printf("The order of the bytes of x in memory is: ");

  for(int i = 0; i < sizeof(unsigned int); i++)
    printf("%02x ", p[i]);  // In "%02x", the "0" means print leading zeros
                            // and the "2" specifies a minimum width of 2.
  printf("\n");

  // This is the same information as above, but the address of each
  // byte of x is shown, as well as the value in that byte.
  
  printf("\nHere is the address and value of each byte of x in memory:\n\n");
  printf("Address            Byte Value\n");
  for(int i = 0; i < sizeof(unsigned int); i++)
    printf("%p       %02x \n", &p[i], p[i]);  

  
  // This code shows that the negative of a signed integer, using
  // the two's complement representation that all modern computers use,
  // is computed by flipping ever bit and then adding one.
  
  x = 15;
  int y  = (~x) + 1;  // the bitwise not (~) operator flips the bits
  printf("\nFlipping the bits of %d and adding 1 results in %d\n", x, y);

  // It works going from positive to negative or negative to positive.

  x = -12;
  y = (~x) + 1;
  printf("Flipping the bits of %d and adding 1 results in %d\n", x, y);

  // BE CAREFUL WRITING EXPRESSIONS USING A MIX OF SIGNED AND UNSIGNED
  // INTEGERS. The compiler, by default, will cast signed numbers to
  // unsigned numbers. Here is an example with an unexpected result.
  
  int a = -5;
  unsigned int b = 20;

  printf("\nWarning: Accidental mixing of signed and unsigned integers\n");
  
  if (a > b)   // a is automatically cast to unsigned int, which is a large number
               // due to two's complement. Now the comparison is unsigned.
    printf("Yes, %d is greater than %d (huh?)\n", a, b);
  else 
    printf("No, %d is not greater than %d\n", a, b);

  printf("\nFixed by casting the unsigned int to an int\n");
  
  if (a > (int) b)  // by casting b to a signed int, the comparison is on signed ints.
    printf("Yes, %d is greater than %d (huh?)\n", a, b);
  else 
    printf("No, %d is not greater than %d\n", a, b);
}

