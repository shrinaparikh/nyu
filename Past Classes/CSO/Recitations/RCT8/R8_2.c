
#include <stdio.h>

void test();

int main()
{
  test();
}

int fibonacci_step(int x, int y)
{
  int z;
  z = x + y;
  return z;
}

void print_int(int y)
{
  printf("%d\n", y);
}
