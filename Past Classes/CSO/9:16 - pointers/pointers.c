
#include <stdio.h>

#define SIZE 10

void fun_with_pointers_and_arrays();  // defined below.
void fun_with_strings();
void the_most_fun(); 

int main()
{
  int x;

  // This is a declaration of the variable p of type
  // "int *", which means it is a pointer to an int.
  // A pointer is simply an address.
  int *p;  

  x = 6;

  printf("x is initially %d\n", x);

  // The & operator is the "address of" operator, so that &x
  // returns the address x. In this case, the address of
  // x is being written into p, so that p points to x.
  
  p = &x;  // p now points to x

  // The * operator is the dereferencing operator, which simply
  // indicates that a pointer should be followed.  That is,
  // *p refers not to p itself, but to whatever p points
  // to -- in this case, p points to x.
  
  *p = 7; // This actually modifies x to be 7.
  
  printf("p points to %d\n", *p);
  printf("Now x = %d\n", x);

  fun_with_pointers_and_arrays();  // see the function definition below

  fun_with_strings();  // see below
 
  the_most_fun();      // see below
  
}

void fun_with_pointers_and_arrays()
{

  printf("\nIn fun_with_pointers_and_arrays()\n");
  
  // When you declare an array, such as the array "arr" below,
  // and specify its size, then space in memory is allocated
  // for the array.  The name of the array, in this case arr,
  // is just a constant pointer to the first element of the array.
  
  int arr[SIZE];

  // Notice that, in this case, arr and &arr[0]  (the address of the
  // first element of a, are the same thing -- they're both addresses.

  printf("arr = %p, &arr[0] = %p\n", arr, &arr[0]);

  // Now we're declaring an int pointer q and setting it to
  // point to the first element of the array (which arr already
  // points to).
  
  int *q = arr;

  // Here is a loop that shows that as we increment q (using q++) to point
  // to subsequent elements of arr, q is being incremented by 4 each time,
  // since q is an int pointer and int's are 4 bytes.  That is, if q
  // points to an int, then in order for q to point to the next int, the 
  // address stored in q to be incremented by 4.  IMPORTANT: The compiler
  // takes care of adding 4 (rather than 1) to q when q++ is executed. The
  // programmer doesn't need to worry about it.

  for(int i=0; i< SIZE; i++) {
    printf("q = %p\n", q);  // printing q in hex each time to show the increment by 4
    *q = i*2;  // writing to where q points to, which is an element of arr.
    q++;       // incrementing q to point to the next element of arr.
  }

  // Using ordinary array notation, arr[i], we print out the
  // elements of arr.
  
  for(int i=0; i< SIZE; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

}


void fun_with_strings()
{

    printf("\nIn fun_with_strings()\n");
    
  // There is no separate "string" type in C. A string is simply an
  // array of char's (bytes). In order to treat such an array as
  // a string, you need to write a 0 (not the character '0') at
  // the end of the string. This way, the printf function, and lots
  // of other functions that you will use to operate on strings,
  // knows where the end of the string is (at the 0).

  // declaring a variable as an array of char's, which we will
  // treat below as a string by making sure there's a 0 at the
  // end.
  
  char s[80];

  // declaring a char pointer r and initializing it to point to
  // the start of the array s.
  
  char *r = s;

  // Declaring a char variable c and initializing it to the character 'a'.
  // Remember that a char is just a one-byte number, so in this case 'a'
  // is the ASCII value representing the lower-case character 'a'.
  // If you look that up in the ACII table, you'll see the value is
  // 97 in decimal and 61 in hexadecimal.

  char c = 'a';

  printf("The character %c is %d decimal and %x hex in the ASCII table.\n",
	 c, c, c);

  // This loop shows three things: (1) The use of the pointer r to iterate
  // over the elements of the char array s, (2) Since r is a char pointer,
  // and a char is one byte, incrementing r only increases it by 1, and
  // (3) since c is a one-byte number (containing an ASCII code), you can
  // increment it to refer to the next character in the ASCII table.
  
  for(int i = 0; i < 26; i++) {
    printf("r = %p\n", r);   // Printing the address stored in r
    *r = c;                  // Writing into s via the pointer r
    r++;                     // Incrementing r, increasing it by 1.
    c++;                     // Incrementing c so it contains the ASCII value for the
                             // next character.
  }
  
  *r = 0;  // REMEMBER to write a 0 into the end of the array, so the
           // printf function will know when to stop printing.

  // In printf, the %s format specifier will cause a char array to be
  // printed as a string.  That is, it will print the character corresponding
  // to the ASCII code in each element of the array and will stop when
  // it hits a 0.
  
  printf("s = %s\n", s);

}


// This function shows some fun C code that uses pointers.

void the_most_fun()
{
  printf("\nIn the_most_fun()\n");
  // (I didn't discuss this in class yet)
  // If you just want a variable to point to a string, an easy way
  // to do this is by putting the string in double quotes.  The compiler will
  // generate code that allocates sufficient space for the specified string,
  // including a 0 at the end.

  // Here, s1 is a char pointer that points to an array containing the ASCII
  // values for the characters 'H', 'e', 'l', 'l', 'o', ' ' (space), 'W', 'o'
  // 'r', 'l', 'd'. The last element of the array is 0 (not the character '0').
  
  char *s1 = "Hello World";

  // Declaring an character array s2.
  
  char s2[80];

  // p1 is a pointer to the first element of the array (string) that s1 points to.

  char *p1 = s1;

  // p2 is a pointer to the first element of the array s2.

  char *p2 = s2;

  // The code below copies the characters in s1 into s2, but in a very 
  // concise and difficult-to-read way. YOU SHOULD NOT WRITE CODE LIKE THIS.
  // It relies on the fact that (1) the value of an assignment
  // operation, =, is whatever value is assigned and (2) C treats
  // 0 as false, so that when the 0 is copied from *p1 into *p2,
  // the value of assignment expression is 0, so that the while
  // loop stops.
  // Note: the way to read the expression "*p2++ = *p1++" is "take the
  // value that p1 points to and write it into the place that p2 points
  // to, then increment p1 and increment p2."
  
  while ((*p2++ = *p1++));  // the extra parenthesis is to suppress a compiler warning.

  // Sure enough, "Hello World" has been copied into s2:
  
  printf("s2 = %s\n", s2);
  
}
