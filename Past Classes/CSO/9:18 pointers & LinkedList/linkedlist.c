
#include <stdio.h>

// The file stlib.h must be #include'd in order to use malloc()

#include <stdlib.h>

// This is a struct declaration for a cEll that we can use in a linked list.
// It contains a data field holding an int and a next field that points
// to the next cell in the list.

struct cell {
  int data;
  struct cell *next;
};


// This function takes an integer parameter n and creates a linked
// list of n cells, whose data fields are the numbers from between
// 1 and n. It then prints the linked list.  Notice that since we
// are putting each new cell we create at the beginning (not the end)
// of the list, the numbers are in reverse order -- i.e. the first cell
// contains n, the second cell contains (n-1), and so on.

void build_list(int n) /////// be sure to trace this!
{
  // The head pointer will always point to the beginning of the list.
  // Initially it is NULL, i.e. it doesn't point to anything.

  struct cell *head = NULL; 
  for(int i = 1; i <= n; i++) {

    // MALLOC --> M(emory) ALLOC(ation)
    // sizeof() func takes EITHER a type or a var as its sole argument
    //malloc() needs # bytes to allocate as an arg -> why we use sizeof
    // remember to CAST return b/c malloc() returns a *char (pointer to memory it just allocated)
      
    // Each time through the loop, we call malloc() to allocate enough
    // space in memory to hold one cell.  malloc() takes as its
    // parameter, the number of bytes needed. Since we don't necessarily know
    // exactly how many bytes something occupies, we use the sizeof() operator
    // to get that information.  sizeof(...), where ... can either be a type
    // or a variable, returns the number of bytes needed for that type or variable.

    // malloc() returns a pointer to the space it just allocated. Since the
    // return type of malloc() is "char *", you need to
    // put in a cast to let the compiler know you are treating it as a
    // pointer to a different type -- in this case, as a pointer to a
    // "struct cell".

    struct cell *p = (struct cell *)  malloc(sizeof(struct cell));

    // If p is a pointer to a struct, then the way you access a field
    // of the struct via p  is by using the "->" notation (instead of
    // the dot notation).  That is, p->data is exactly the same as
    // saying (*p).data, it's just easier to read.
      
    // Set the data field of the new cell to i.
    p->data = i;

    // Have the next field of the new cell point to whatever was at
    // the beginning of the list (i.e. whatever head was pointing to).
    
    p->next = head;

    // Now head points to the new cell.
    head = p;
  }

  // Here, we print the data items in the list by using a pointer q
  // which starts at the head of the list and iterates down the list
  // by being set to the "next" field of the cell each time through
  // the loop.

  struct cell *q;
  for (q = head; q != NULL; q = q->next)
    printf("%d ", q->data);

  printf("\n");
}  



int main()
{
  build_list(10);
}

