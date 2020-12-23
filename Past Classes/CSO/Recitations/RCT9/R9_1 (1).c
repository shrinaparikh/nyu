#include <stdio.h>
#include <stdlib.h>
  
// Representation of a node 
typedef struct node {
  int data;
  struct node *next;
} Node;
  
// Function to insert node 

Node *allocate_node()
{
  return (Node *) malloc(sizeof(Node));
}

void insert(Node** root, int item) 
{ 
    Node *temp = allocate_node();
    temp->data = item; 
    temp->next = *root; 
    *root = temp; 
} 
  
void display(Node* root) 
{ 
    while (root != NULL) { 
        printf("%d \n",root->data); 
        root = root->next; 
    } 
} 
  
Node *arrayToList(int arr[], int n) 
{ 
    Node *root = NULL; 
    for (int i = n-1; i >= 0 ; i--) 
        insert(&root, arr[i]); 
    return root; 
} 
  
// Driver code 
int main() 
{ 
    int arr[] = { 1, 2, 3, 4, 5 }; 
    int n = sizeof(arr) / sizeof(arr[0]); 
    Node* root = arrayToList(arr, n); 
    display(root); 
    return 0; 
}