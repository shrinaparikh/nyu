
#include <stdio.h>

#define SIZE 10

// Need the prototypes of these functions since the compiler will
// see the calls to these functions before it sees their definitions.

int summ_array(); 
int buggy_array();

int main()
{
   // Calling the summ_array function with no parameters
  
   printf("Sum of the array = %d\n", summ_array());

   // Now calling the buggy_array function, which will crash
   // the program. See below.
   
   printf("Sum of the array = %d\n", buggy_array());   
}


int summ_array()
{
  
  int a[SIZE];   // this allocates a block in memory to hold an array of
                 // SIZE (i.e. 10) 4-byte integers. There is no need to
                 // use "new(...)" as in Java.

   // Initializing the array 

  for(int i = 0; i < SIZE; i++)
     a[i] = i*2;


  // compute the sum of the elements of the array.

  int sum = 0;
  for(int i = 0; i < SIZE; i++)
    sum += a[i];

  return sum;
  
}


// This function will cause the program to crash with a
// segmentation fault, because it tries to write far off
// the end of the array -- there is no array bounds checking
// in C.

int buggy_array()
{
  
  int a[SIZE]; 

  // NOTE THAT THIS LOOP, WRITING TO THE ARRAY, DOESN'T STOP AT THE
  // END OF THE ARRAY. EVENTUALLY, IT WILL WRITE TO SOMEWHERE IN MEMORY
  // THAT WILL CAUSE THE PROGRAM TO CRASH. SEE THE RESULT OF RUNNING THE PROGRAM.
  
  for(int i = 0; i >= 0; i++)   // the "i >= 0" condition is the problem.
     a[i] = i*2;


  // compute the sum of the elements of the array.
  int sum = 0;
  for(int i = 0; i < SIZE; i++)
    sum += a[i];

  return sum;
  
}
