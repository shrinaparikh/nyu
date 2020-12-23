#include <stdio.h>
#include <string.h> 
int func1(int, int[]); 
  
int main(int argc, char *argv[]) 
{ 
    if (argc != 2)
    {
        printf("Wrong number of arguments\n");
        return 1;
    }
    
    int i, a;
    printf("Input value for a:\n");
    scanf("%d", &a);
    
    // **********************TODO**********************
    printf("input 5 values for array:\n");
    
    int arr[5];
    for(int i = 0; i < 5; i++) {
        scanf("%d", &arr[i]);
    }
    a = func1(a, &arr[i]);
    
    // Use scanf to read five integers and store them
    // in an array arr. Give the address of each array 
    // element accordingly. Call the function func1
    // giving it appropriate arguments. (solved above)
    
    printf("value of a is %d\n", a); 
    for (i = 0; i < 5; i++) { 
        printf("value of arr[%d] is %d\n", i, arr[i]); 
    }

    printf("Enter a filename > ");  

    //////////////////////////////////////////////////////////////
    
    char str[100];
    printf("ENter a string > ");
    scanf("%s", str);
    printf("You entered: %s\n", str);
    
    char *in_file_name = argv[1];
    char *out_file_name = str;
    
    FILE *infile = fopen(in_file_name, "r");
    FILE *outfile = fopen(out_file_name, "w");
    
    // **********************TODO**********************
    // Take a string input using scanf and store it in
    // fname. This will be your output file name. Open the
    // input file in read only mode and the output file in
    // write mode.  (above)

    char c;
    
    while (fscanf(infile, "%c", &c) == 1)
        fprintf(outfile, "%c", c + 1);

    // Always a good idea to close the files.
    fclose(infile);
    fclose(outfile);

    // **********************TODO**********************
    // open the output file again and print its contents
    // on the screen.
    
    FILE *output = fopen(out_file_name, "r");
    while(fscanf(output, "%c", &c) == 1)
        printf("%c",c);
    
    fclose(output);

    // **********************TODO**********************
    // Create a new function fileread which takes the 
    // outfile name as input. The function will read the 
    // contents of the file and store them in a string after
    // converting them into capitals.
    
    arr[100] fileread(out_file_read) {
        
    }

    fileread(out_file_name);

    return 0;  
} 
  
int func1(int a, int* arr) 
{ 
    int i; 
    a = a + 20; 
    arr[0] = arr[0] + 50; 
    arr[1] = arr[1] + 50;
    arr[2] = arr[2] + 50; 
    arr[3] = arr[3] + 50; 
    arr[4] = arr[4] + 50; 
    return a; 
} 
