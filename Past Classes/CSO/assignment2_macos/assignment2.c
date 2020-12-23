#include <stdio.h>

#include "add_array.h"


// This function prints the individual bits of a
// 32-bit quantity. Do not alter this function

void print_32_bits(void *p)
{
  unsigned int x = *((unsigned int *) p);
  unsigned int mask = 1 << 31;
  for(int i = 0; i < 32; i++) {
    if (x & mask)
      printf("1");
    else
      printf("0");
    mask >>= 1;
  }
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
// This function takes an unsigned integer x and returns an unsigned
// integer whose bits are in the reverse order of the bits of x.

// That is, bit 31 of the result is the same as bit 0 of x, bit
// 30 of the result is the same as bit 1 of x, etc.
//accessory function for above
int powerN(int x, int n) {
    
    int y = 1;
    
    for(int i = 0; i < n; ++i) {
        y *= x;
    }
    
    return (y);
}

unsigned int reverse_bits(unsigned int x)
{
    // In a loop, use masking to select each bit of x to write into
    // a bit of the result.
    
    int result = 0;

    unsigned int mask = 1 << 31;
    
    for(int i = 0; i < 32; i++) {
  
        if(x & mask)
            result += powerN(2,i);

        mask >>= 1;
    }

    return (unsigned int) result;
    
    
}

// This function multiplies two 32-bit signed integers, only using
// shifting and addition.  The result is a 64-bit signed integer.

long int multiply(int x, int y)
{
  // Need variables to store a mask and a result. These should
  // be 64-bit unsigned numbers.
    
  unsigned long int mask = 1; //1 in the rightmost value
  unsigned long int prod = 0;

  // Need to sign-extend x and y to 64 bits

  long int lx = x; //here, x is implicitly casted as a long int, which is 64 bits
  long int ly = y;

  // In a loop that uses a mask to iterate over the bits
  // of ly from right (bit 0) to left (bit 63):
  //   -- if the current bit of ly is 1, then add lx to the result.
  //   -- shift lx to the left by 1 (every time)

    for(int i = 0; i < 64; i++) {
        if(mask & ly) {
            prod += lx;
        }
        lx = lx << 1;
        mask <<= 1;
    }

    // Return the product, but as a signed long integer.
    return (int) prod;
}



// Defining as macros the expressions for extracting the
// sign, exponent, and fraction fields of a 32-bit
// floating point number.

// select bit 31, shifted all the way to the right.

#define SIGN(x) ((x >> 31) & 1)

// select bits 23 through 30, shifted right by 23 bits

#define EXP(x) ((x >> 23) & 0xFF)

// select bits 0 through 22 (the rightmost 23 bits)

#define FRAC(x) (x & 0x7FFFFF)


// This function performs a floating point addition without
// using the built-in floating point addition -- instead only
// using integer addition and subtraction. It does so
// by extracting on the sign, exponent, and fraction of the
// operands and performing operations using those to
// compute the sign, exponent, and operand of the result.

float float_add(float f, float g)
{

  // We need to treat the values stored in f and g
  // as 32-bit unsigned numbers. See the hint sheet
  // for ways to do that.  We then need to extract the
  // sign, exponent, and fraction fields from f
  // and g, using the SIGN, EXP, and FRAC macros
  // above.
    
  unsigned int sign_f = SIGN((*((unsigned int *) &f)));
  unsigned int sign_g = SIGN((*((unsigned int *) &g)));

  
  unsigned int exp_f =  EXP((*((unsigned int *) &f)));
  unsigned int exp_g =  EXP((*((unsigned int *) &g)));

  unsigned int frac_f = FRAC((*((unsigned int *) &f)));
  unsigned int frac_g = FRAC((*((unsigned int *) &g)));

  // Handle the special case where f is zero (i.e.
  // both the exp_f and frac_f are zero), 
  // in which case the value of g should be returned immediately.
  
    if((exp_f==0) && (frac_f==0)) {
        return g;
    }
  
  // Do the same for g (i.e. check if g is zero).
  
    if((exp_g==0) && (frac_g==0)) {
        return f;
    }

  // In order to perform the multiplication, the implicit
  // leading 1 in the mantissa for f and g must be made
  // explicit. That is, the mantissa for f should contain
  // a 1 in the bit 23 position, followed by the bits of frac_f.
  // The same is true for the mantissa of g.

  unsigned int mantissa_f =  ((1 << 23) | frac_f);
  unsigned int mantissa_g = ((1 << 23) | frac_g);

  // Before performing any addition, the two numbers must have the
  // same exponent. Take the mantissa of the number with the smaller
  // exponent, and shift that mantissa right by the difference in the
  // exponents, and set the smaller exponent to the larger exponent.
  // For example, if f has a smaller exponent than g, shift mantissa_f
  // the right by (exp_g - exp_f) bits and set exp_f to exp_g.

       if(exp_f < exp_g) {
           mantissa_f = mantissa_f >> (exp_g - exp_f);
           exp_f = exp_g;
       }
       else {
           mantissa_g = mantissa_g >> (exp_f - exp_g);
           exp_g = exp_f;
       }

  // Now it's time to compute the exponent, sign, and
  // mantissa of the result. 

  // The exponent of the result (before normalization) is
  // now the same as exponent_f (which is the same as
  // exponent_g).

  // This will hold the sign of the result.

  unsigned int sign_res;

  // This will hold the mantissa of the result.
  
  unsigned int mantissa_res;

  // This holds the exponent of the result.
  
  unsigned int exp_res = exp_g;

  // If  sign_f and sign_g are the same, i.e. they are both
  // 0 (positive) or 1 (negative), then:
  //    -- the sign of the result is the same sign_f and sign_g
  //    -- the mantissa of the result is just the sum of mantissa_f and
  //       mantissa_g.
  //    -- since the sum of the two mantissas may cause a carry into
  //       bit 24 of the result, the result may need to be renormalized.
  //       That is, if bit 24 of the result mantissa is 1, then the
  //       result mantissa should be shifted to the right by 1 and the
  //       exponent of the result should be incremented by 1.

  if (sign_f == sign_g) {

      sign_res = sign_f;
      mantissa_res = mantissa_f + mantissa_g;
      if(mantissa_res & (1 << 24)) {
          mantissa_res >>= 1;
          exp_res += 1;
      }
      
  }
  else {

    // Otherwise, namely if sign_f and sign_g are different (i.e. one
    // number was positive and one negative), then:
    //    -- the sign of the result is the sign of the number with the larger
    //       mantissa (since the numbers have the same exponent at this point).
    //    -- the mantissa of the result should be the result of subtracting
    //       the smaller mantissa from the larger mantissa.
    //
    //       For example, if mantissa_f > mantissa_g, then the sign of the result is
    //       set to sign_f and the mantissa of the result is set to
    //       (mantissa_f - mantissa_g).
    // 
    //    -- If the resulting mantissa is 0, then the entire result is 0 and 
    //       the function should just return 0.0.

    //    -- Otherwise, the resulting mantissa may be small enough that it has to be
    //       renormalized to have a 1 in the bit 23 position. Do this in
    //       a loop, shifting the result mantissa to the left by 1 bit and subtracting
    //       1 from the result exponent, until the mantissa has a 1 in the
    //       bit 23 position.
    
      if(mantissa_g > mantissa_f) {
          sign_res = sign_g;
          mantissa_res = mantissa_g - mantissa_f;
      }
      else if (mantissa_f > mantissa_g){
          sign_res = sign_f;
          mantissa_res = mantissa_f - mantissa_g;
      }
      
      if(mantissa_res == 0) {
          return 0.0;
      }
      
      while(!(mantissa_res & (1 << 23))) {
          print_bits(mantissa_res);
          mantissa_res <<= 1;
          exp_res -= 1;
      }
      
  }
  
  // Now construct the result from OR'ing (using bitwise-or, | ) together the
  // following components of the result:
  //  -- the sign bit of the result, shifting into the sign position
  //  -- the lowest 8 bits of the exponent, shifted into exponent position
  //  -- the lowest 23 bits of the mantissa (i.e. removing the 1 in bit 23 position,
  //     since it is implicit)

  unsigned int result  = ((sign_res << 31) | ((exp_res & 0xFF) << 23) | (mantissa_res & 0x7FFFFF));
    //printf("%d", result);

  // Return the computed result (which is an unsigned int) as a floating point number
  // Be sure that the compiler does not perform a conversion (see the hint sheet)
    
    float resultF = *((float *) &result);
    
  return resultF;
}



// No code in this function should be changed. Just uncomment the appropriate
// code as you complete each of the functions above.

int main()
{

  int x;
  int y;

  printf("Enter a number (to reverse) > ");
  scanf("%d", &x);

  printf("%d = ", x);
  print_32_bits(&x);
  printf("\n");

  int r = reverse_bits((unsigned int) x);
  printf("Reversed, the number is %d = ", r);
  print_32_bits(&r);
  printf("\n");
  
  printf("Enter two integers (to multiply) > ");
  scanf("%d %d", &x, &y);

  printf("%d * %d = %ld\n", x, y, multiply(x,y));

   float f, g;

   printf("Enter two floating point numbers (to add) > ");
   scanf("%f", &f);
   scanf("%f", &g);

   printf("Computed %f + %f = %f\n", f, g, float_add(f,g));

   int a[5] = {1,2,3,4,5};
   printf("Result of add_array(a,5) is %d\n", add_array(a,5));

}


