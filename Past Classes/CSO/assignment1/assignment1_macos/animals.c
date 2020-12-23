#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node_utils.h"

#define BOOL int
#define TRUE 1
#define FALSE 0

NODE *root = NULL;


// Returns true if user types "yes" or "y" (upper or lower case)
// and returns false if user types "no" or "n". Keeps
// prompting otherwise.

BOOL yes_response() {
    char *y = "yes";
    char *n = "no";
    char s[10];
    
    while(1) {
        printf("Please enter 'yes' or 'no'\n");
        fgets(s, 10, stdin);
        strtok(s, "\n");
        
        if (strcasecmp(s,y) == 0 || strcasecmp(s,"yes") == 0) {
            return TRUE;
        }
        else if (strcasecmp(s, n) == 0 || strcasecmp(s, "no") == 0) {
            return FALSE;
    }
    
}
  //Hint: You might consider using the C library function strcasecmp()
}

// This procedure creates a new NODE and copies
// the contents of string s into the 
// question_or_animal field.  It also initializes
// the left and right fields to NULL.
// It should return a pointer to the new node

NODE *new_node(char *s)
{
    NODE* n;
    n = (NODE *) malloc(sizeof(NODE));
    
    strcpy(n->question_or_animal, s);
    
    n->left = NULL;
    n->right = NULL;

    return n;
}

// This is the procedure that performs the guessing.
// If the animal is not correctly guessed, it prompts
// the user for the name of the animal and inserts a
// new node for that animal into the tree.


void guess_animal()
{
  // If the root is NULL, then there are no animals in 
  // the tree. Prompt the player for the name of an 
  // animal, create a node for that animal, and make
  // that node the root of the tree.
    NODE* curr = root;
    char s[50];
    if(root == NULL) {
        printf("Enter the name of an animal: \n");
        fgets(s, 50, stdin);
        strtok(s, "\n");
        NODE* n = new_node(s);
        root = n;
    }

    /*
      Otherwise (i.e. if the root is not NULL)
      Then descend down the tree. At each node encountered:

      If the left and right fields of the node are not NULL, i.e. the node
      is an interior node and must contain a question, then:
      - print the question_or_answer field, which will be a yes/no question.
      - read the response from the user
      - If the response is yes, follow the left field to the next node. Otherwise,
        follow the right field.
    */
    while(curr->left != NULL) {
        //while descending down the tree
        printf("%s\n", curr->question_or_animal);
        if(yes_response())
            curr = curr->left;
        else
            curr = curr->right;
    }
    
        
    if (curr->left == NULL) { //then both children are null
            
        printf("I'm guessing %s \n", curr->question_or_animal);
        printf("Am I right?\n");
            
        int answer = yes_response();
        if(answer == TRUE) {
            return;
        }
        else if(answer == FALSE) {
            char a[50];
            char q[200];
            char ans[10];
            
            printf("Oops! What animal you were thinking of? \n");
            fgets (a, 50, stdin);
            strtok(a, "\n");
            printf("Enter a yes or no question distinguishing a %s from a %s \n", a, curr->question_or_animal);
            fgets (q, 200, stdin);
            strtok(q, "\n");
            
            NODE* nAnimal;
            nAnimal = new_node(a); //new animal
            
            NODE* nGuess = new_node(curr->question_or_animal); //program's guess
            
            printf("What is the answer for a %s \n", a);
            if(yes_response()) {
                curr->left = nAnimal;
                curr->right = nGuess;
            }
            else {
                curr->right = nAnimal;
                curr->left = nGuess;
            }
            
            strcpy(curr->question_or_animal, q);
    
        }
    }
    
    curr = root;

    
}






/*
 Otherwise, if the left and right fields are NULL (i.e. the node is a leaf),
 then the question_or_animal field contains an animal. Print the
 the question_or_animal field as the guess and prompt the user
 if the guess was correct. If the guess was correct, then
 return. Otherwise, do the following:
 - prompt the user for the name of the new animal she was thinking of
 - prompt the user for a yes or no question distinguishing the new animal from the guessed animal
 - ask the user what the answer for the new animal would be (yes or no)
 - create a new node with the new animal in the question_or_animal field
 - create another new node that has the guessed animal in the question_or_animal field
 - make the two new nodes the children of the current node, where the animal for which the
 answer to the question is "yes" is the left child and the other animal is the right child
 - overwrite the question_or_animal field of the current node with the new question.
 
 Note that the tree is a stricly binary tree, i.e. left and right fields of each node are either both NULL or
 both valid pointers to child nodes (in other words, each node is a leaf or has exactly two children).
 */


//This code is complete. Just add comments where indicated.

int main()
{ int i;
  BOOL done = FALSE;

  //fopen here opens the file for reading and returns a file pointer (FILE*). You use this pointer when accessing the file
  FILE *datafile = fopen("data.dat", "r"); 

  if (datafile == NULL) {
    printf("data.dat not found\n");
    exit(1);
  }

  //fopen here open the file for writing and returns a file pointer called backupfile
  FILE *backupfile = fopen("data.dat.bak", "w");

  //calls read_tree from node_utils.c. This function creates a binary tree based on the contents of the FILE* argument, which is datafile here. It is assigned to root because the function returns the root of the newly created binary tree
  root = read_tree(datafile);

  //call write_tree() to write the initial tree to the
  //backup file (i.e. to backup the tree data)
  write_tree(root,backupfile);

  //close both files (for now)
  fclose(backupfile);
  fclose(datafile);

  printf("Welcome to the animal guessing game (like 20 questions).\n");
  do { 
    printf("\nThink of an animal...\n");
    guess_animal();  //This is the function in which the binary tree is traversed and asks the user questions until it reaches a leaf. All leaves stores animal names instead of questions, and the player is asked whether the animal is correct or not. If so, that round of the game is over. Otherwise, the current node is reset to a distinguishing question and the children are set to the 1. the animal the user was thinking and 2. the animal that was previously stored in that leaf
    printf("\nDo you want to play again? (yes/no) >");
  } while (yes_response());  //Since yes_response asks the user for a yes or no answer and returns TRUE for yes or FALSE for no, this loop continues running as long as the user wants to keep playing


  //now open the "data.dat" file for writing
  datafile = fopen("data.dat", "w");

  //calls the write_tree function from node_utils.c. This method uses pre-order traversal (middle, left, right) to recursively print the question_or_animal field of every node into the file specified by datafile
  write_tree(root, datafile);

  //close the data.dat file
  fclose(datafile);

}

