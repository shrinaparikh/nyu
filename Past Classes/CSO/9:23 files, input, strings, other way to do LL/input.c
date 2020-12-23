
#include <stdio.h>

// This is shows how to use scanf() to read data from
// the keyboard (standard input).

int main()
{
  int x;
  printf("Enter x > ");

  // scanf takes a format specifier string, just like printf(), to
  // indicate how to read the input (as an integer, string, etc.) and
  // the address in memory where you want the input written.

  // In this case, we want to read a decimal number, hence the "%d",
  // into the memory at the address corresponding to x. Thus, we
  // need to tell scanf to write the number from the input into &x.
  
  scanf("%d", &x);
  printf("x = %d\n", x);

  char s[100];
  printf("Enter a string > ");

  // If you tell scanf to read a string, using the format specifier "%s",
  // then you need to provide the address where you want the string
  // written. Remember that if s is declared as an array, above, then the
  // name s indicates the address of the first element of the array.  That
  // is, there is no difference between s and &(s[0]).
  
  scanf("%s", s);
  printf("You entered: %s\n", s);
}

