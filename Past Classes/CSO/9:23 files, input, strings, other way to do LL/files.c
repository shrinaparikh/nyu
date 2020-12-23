
#include <stdio.h>

// This program shows the use of file I/O, using
// fscanf and fprintf instead of scanf and printf.

// The names of the files to be read and written to
// are specified as the two command-line parameters.
// Therefore, argc should be 3, argv[1] is
// the string containing the input file name, and
// argv[2] is the string containing the output file name.

// To compile and run this file, you might type:
//
//   % gcc -o files files.c
//   % ./files infile.txt outfile.txt
//
// where infile.txt must already exist.

int main(int argc, char *argv[])
{
  if (argc != 3) {
    printf("Need two filenames as parameters\n");
    return 1;
  }

  // Getting the input and output file names.
  
  char *in_file_name = argv[1];
  char *out_file_name = argv[2];

  // Using fopen() to open the files for reading
  // and writing, respectively. fopen() returns
  // a file pointer, of type FILE *, that you'll
  // need to use when accessing the file.
  
  FILE *infile = fopen(in_file_name, "r");
  FILE *outfile = fopen(out_file_name, "w");

  int num;

  // This code uses a loop to read an integer from
  // the input file, double it, and write the result
  // to the output file.
  
  while (fscanf(infile, "%d", &num) == 1)
    fprintf(outfile, "%d\n", num * 2);

  // Always a good idea to close the files.
  fclose(infile);
  fclose(outfile);
}


  
