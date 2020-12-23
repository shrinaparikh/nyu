
#include <stdio.h>

// This code shows the sizes of int, long int, short int,
// float, and double.
// It also shows that the size of a struct is not necessarily
// just the sum of the sizes of its fields.


// Since int fields start on a word (4-byte) boundary, this
// struct will occupy 12 bytes, even though the sum of
// the sizes of its fields is 4 + 1 + 4 = 9.

typedef struct {
  int y;  // 4 bytes
  char z; // 1 byte
  int w;  // 4 bytes, but starts on 4-byte boundary.
} MYTYPE;


int main()
{

  printf("Sizeof(MYTYPE) is %lu\n", sizeof(MYTYPE));
  
  long int x;
  printf("An int is %lu bytes, x is %lu bytes\n",
	 sizeof(int), sizeof(x));

  short int y;
  printf("An int is %lu bytes, y is %lu bytes\n",
	 sizeof(int), sizeof(y));

  float f;
  double g;

  printf("An float is %lu bytes, a double is %lu bytes\n",
	 sizeof(f), sizeof(g));

}
