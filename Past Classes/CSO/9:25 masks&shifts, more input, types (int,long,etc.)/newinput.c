
#include <stdio.h>

// This program gives examples of different ways for inputting strings.
// The first, using scanf(), is susceptible to buffer overflow attacks,
// where the user inputs a longer string than the space allocated for it.
// The other two, using getchar() and using fgets(), are safer. As you
// can see below, using fgets() is often easiest.

// For these examples, we'll assume a maximum string size of 20 characters.

#define MAXLENGTH 20

int main()
{
  char s[MAXLENGTH + 1];  // need a byte for the zero at the end

  printf("Enter string (no spaces) > ");

  // Example 1: Using scanf()
  // Since scanf() will keep reading from the keyboard until the
  // user types enter, there's nothing to stop it from reading
  // in more bytes than has been allocated for s.

  //  scanf("%s", s);     // commented out, since it interferes with the
                          // getchar() and fgets() code further down.
  //  printf("s is: %s\n", s);


  // Example 2: Using getchar()
  // getchar() reads in a single character and returns it. If there
  // are no more characters to read, it returns EOF (a constant).

  // To be sure that you don't write too many bytes into s, keep
  // a count of how many characters you've read so far.

  printf("Enter a string > ");
  
  char c = getchar();   // read character.
  int count = 0;

  // Keep looping as long as you haven't hit the end of the input,
  // the user hasn't hit carriage-return ('\n'), and the 
  // count of the characters read doesn't exceed MAXLENGTH.
  
  while ((c != EOF) && (c != '\n') && (count < MAXLENGTH)) {
    s[count] = c;
    count++;
    c = getchar();   // read the next character.
  }

  // Need to write a zero into s, following the characters
  // read in.
  
  s[count] = 0;  // end with a zero!


  // if we stopped reading due to count being equal to
  // MAXLENGTH, we want to read and discard the rest of
  // the input typed in.
  
  while ((c != EOF)  && (c != '\n'))
    c = getchar();   // not writing c into s anymore.

  printf("s is: %s\n", s);  

  // Example 3: Using fgets()
  // fgets() reads a string from a file or standard input.  It
  // takes three parameters:
  //    - the address of where to put the characters (e.g. the
  //      char array)
  //    - the maximum number of characters to read
  //    - the file pointer for the file you want to read from.
  //      If you want to read from standard input, specify stdin.

  printf("Enter a third string > ");

  // Here, we are reading a string of at most MAXLENGTH characters
  // from the standard input (stdin), storing them in the array s.
  // Note that fgets() will automatically put a zero at the end.
  
  fgets(s, MAXLENGTH, stdin);
  printf("s is: %s\n", s);  

}
