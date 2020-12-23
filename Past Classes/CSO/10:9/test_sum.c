#include <stdio.h>

// This function is defined in sum_unix.s or sum_windows.s, containing
// handwritten assembly code.

int sum_from(int start, int end);

int main()
{
  printf("The sum from %d through %d is %d\n", 3, 12, sum_from(3,12));
}
