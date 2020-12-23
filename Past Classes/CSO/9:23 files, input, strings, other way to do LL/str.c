
#include <stdio.h>
#include <string.h>   // This is for the string library functions

// This program gives examples of the use of command-line parameters
// and string functions from the C string library.


// main() can two take two parameters:
//  argc:  The count of the number of words typed on the command line
//         when the program is run, including the name of the program
//         itself. Therefore, argc >= 1.
// argv:  This is an array of strings, with each string being a word
//        typed on the command line. argv[0] contains the string (i.e.
//        a char pointer) representing the name of the file.
//
// For example, if you compile this program by typing
//
//  % gcc -o str str.c
//
// and then run it by typing
//
//  % str one two
//
// then arc will be 3, arg[0] will be the string "str", arg[1] will
// be the string "one", and arg[2] will be the string "two".

int main(int argc, char *argv[])
{
  // let's require two arguments following the program name

  if (argc != 3) {
    printf("Wrong number of arguments\n");
    return 1;
  }

  // Now just print out the words typed on the command line
  // when this program is run.
  
  printf("You typed > ");
  for(int i = 0; i < argc; i++)
    printf("%s ", argv[i]);
  printf("\n");


  // The code below gives some examples of the use of functions
  // from the C string library.
  
  char s[50];

  // The function strcpy(s1, s2) copies the characters in the string
  // s2 into the string s1.  IMPORTANT: It is your responsibility to
  // allocate space for s1.

  // For "hello", the compiler creates enough space to store the
  // characters 'h', 'e', 'l', 'l', 'o', and the one-byte value 0 (zero).
  // So, this line copies those 6 one-bye values into s.
  
  strcpy(s, "hello");

  // strlen(s) returns the length of s, which is defined to be
  // the number of characters (one-byte values) encountered before
  // the zero.  So, since s contains "hello", strlen(s) will be 5.
  
  printf("strlen(s) = %lu\n", strlen(s));

  // The function strcmp(s1,s2) compares the strings s1 and s2 alphabetically
  // (i.e. lexicographic or "dictionary" order) and returns an integer result.
  // If that result is negative, then s1 < s2 (i.e. s1 comes before s2 in the
  // dictionary). If the result is zero, then s1 == s2 (i.e. they are the same
  // string. Otherwise, if the result is positive, then s1 > s2.

  // Note that the comparison is case-senstive. Since all upper-case letters
  // come before any lower-case letter in the ASCII table, any word starting
  // with an upper-case letter will be less than any word starting with a
  // lower-case letter.
  
  int res = strcmp(s, "bye");
  printf("res = %d\n", res);
  if (res < 0)
    printf("hello is before bye\n");
  else if (res == 0)
    printf("hello is equal to bye\n");
  else
    printf("hello is after bye\n");
}

