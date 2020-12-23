#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h> 

int main() {
    while(1) {
        printf("lab1>"); 

        char input[10];
        scanf("%s", input);
        printf("Parent Process %d\n", getpid()); 

        if(strcmp(input, "exit") == 0) {
            exit(1); //https://www.tutorialspoint.com/c_standard_library/c_function_exit.htm
        }
        else if(strcmp(input, "printid") == 0) {
            printf("The ID of the current process is: %d \n", getpid()); 
        }
        else if(strcmp(input, "greet") == 0) {
            printf("Hello\n");
        }
        else {
            int pid = fork(); 
            if(strcmp(input, "ls") == 0) {
                if(pid == 0) {
                    printf("Child process %d will execute the command %s\n", pid,input);
                    char * argv[]= {"ls", NULL};
                    execve("/bin/ls", argv, NULL); 
                    printf("Command Not Found!\n");
                    exit(0);
                }           
            }
            else if(strcmp(input, "pwd") == 0){
                if(pid==0) {
                    printf("Child process %d will execute the command %s\n", pid,input);
                    char * argv[]= {"pwd", NULL};
                    execve("/bin/pwd", argv, NULL); 
                    printf("Command Not Found!\n");
                    exit(0);                    
                }
            }
            
            else if(strcmp(input, "ps") == 0) {
                if(pid==0) {
                    printf("Child process %d will execute the command %s\n", pid,input);
                    char * argv[]= {"ps", NULL};
                    execve("/bin/ps", argv, NULL); 
                    printf("Command Not Found!\n");
                    exit(0);                    
                }               
            }
            
            else if(strcmp(input, "date") == 0) {
                if(pid==0) {
                    printf("Child process %d will execute the command %s\n", pid,input);
                    char * argv[]= {"date", NULL};
                    execve("/bin/date", argv, NULL); 
                    printf("Command Not Found!\n");
                    exit(0);                    
                } 
            }
            else if(strcmp(input, "lscpu") == 0) {
                 if(pid==0) {
                    printf("Child process %d will execute the command %s\n", pid,input);
                    char * argv[]= {"lscpu", NULL};
                    execve("/bin/lscpu", argv, NULL); 
                    printf("Command Not Found!\n");
                    exit(0);                    
                }                
            }  
                     
            wait(NULL); //https://www.geeksforgeeks.org/wait-system-call-c/
        }
        
    }
} 
