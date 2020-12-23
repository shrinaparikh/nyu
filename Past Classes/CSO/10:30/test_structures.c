
#include <stdio.h>
#include <stdlib.h>

// This is the CELL struct type that the assembly code will operate on.
// As we see when we run main() below, the size of a CELL is 16 bytes, the val field is
// at offset 0 bytes from the start of the cell and the next field is at offset 8 bytes
// from the start of the cell.

typedef struct cell {
  int val;
  struct cell *next;
} CELL;

// This is the function that, in assembly, calls malloc() to allocate one
// CELL.  See the corresponding C code (not being used) below.

CELL *allocate_cell();

// This is the function that, in assembly, creates a linked list
// of ten CELLs, whose val fields contain 1 through 10 in order.  See
// the corresponding C code (not being used) below.

CELL *create_list();

// This is the function that, in assembly, traverses a linked
// list of CELLs, starting from the specified head, and print out the val
// field of each cell.  See the corresponding C code (not being used)
// below.
void print_list(CELL *head);


int main()
{
  // We need to print out sizeof(CELL) to see how big the
  // compiler has decided to make a CELL (in this case, 16 bytes).
  
  printf("sizeof(CELL) is %lu\n", sizeof(CELL));

  // To see where each field is within a CELL, we print out the
  // difference between the address of the field and the address
  // of the start of the cell. In this case, the val field starts
  // where the cell starts, i.e. the difference is 0. The next
  // field starts at 8 bytes past the start of the cell, i.e. the
  // difference is 8.
  
  CELL x;
  printf("Offset of val field is %ld\n", ((long) &(x.val)) - ((long) &x));
  printf("Offset of next field is %ld\n", ((long) &(x.next)) - ((long) &x));

  // Set head to point to the linked list resulting from calling the
  // create_list() function in assembly (see the unused C code below).
  
  CELL *head = create_list();

  // Print out the linked list by calling the print_list() in assembly,
  // passing the head pointer (see the unused C code below).
  print_list(head);
}

// This function calls malloc() to allocate one
// CELL.  It returns the address of the cell.

// COMMENTED OUT:  SEE THE ASSEMBLY LANGUAGE VERSION

// CELL *allocate_cell()
// {
//   return (CELL *) malloc(sizeof(CELL));
// }



// This creates a linked list of ten CELLs, whose val fields contain
// 1 through 10 in order. It returns the head of the list, i.e. a
// pointer to the first cell.

// COMMENTED OUT:  SEE THE ASSEMBLY LANGUAGE VERSION

// CELL *create_list()
// {
//   CELL *head = NULL;
//   for (int i=10; i > 0; i--) {
//     CELL *p = allocate_cell();
//     p->val = i;
//     p->next = head;
//     head = p;
//   }
//   return head;
// }


// This function takes the head of a linked list of CELLs as a parameter and
// and traverses the list, printing out the val field of each cell. 

// COMMENTED OUT:  SEE THE ASSEMBLY LANGUAGE VERSION

// void print_list(CELL *head)
// {
//   CELL *p = head;
//   while (p != NULL) {
//     printf("%d ", p->val);
//     p = p->next;
//   }
//   printf("\n");
// }
