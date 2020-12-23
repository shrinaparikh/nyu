
#include <stdio.h>

// This are simple functions that, other than main(), are called from the assembly
// code found in go.s (for the system, Unix or Windows) that you are using.


void go();

// It's often easiest to leave main() in C, rather than writing it in assembly
// language. In this case, it just calls the go() function defined in the
// assembly code in go.s. 

int main()
{
  go();
}


// A simple recursive factorial. It takes a single parameter, which it is
// expecting to be in the register dictated by the calling convention
// to be used to hold the first parameter (%edi in Unix, %ecx in Windows,
// since x is a 32-bit value).

// Of course, the return value will be put in %eax, consistent with
// calling convention for both OS's.

int fac(int x)
{
  if (x == 0)
    return 1;
  else
    return x * fac(x-1);
}


// This function prints the value of the integer that it receives
// as a parameter in %edi (Unix) or %ecx (Windows).

void print_int(int y)
{
  printf("%d\n", y);
}

// This function takes 8 integer parameters and is used to
// illustrate that, consistent with the calling convention,
// some of the parameters are expected to be found in registers
// and some on the stack.

// See the comments in go.s (for your OS) describing the assembly
// code passing the parameters to the silly() function.

int silly(int a, int b, int c, int d, int e, int f, int g, int h)
{
  printf("g = %d, h = %d\n", g, h);
  return a+b+c+d+e+f+g+h;
}

