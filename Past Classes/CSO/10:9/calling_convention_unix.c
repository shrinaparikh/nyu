
// Demonstrating the Unix (incl. macOS and linux) calling convention

// This code, when compiled into X86-64 assembly code,
// shows what registers are used to pass the first
// five parameters in a function call, and what register
// is used to hold the return value.

// See the assembly code in 
//   calling_convention_unix.s

int f(int a, int b, int c, int d, int e);

int foo()
{
  int z = f(1,2,3,4,5);
  return z+1;
}
