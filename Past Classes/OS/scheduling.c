#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include <string.h>

void FCFS(int num_processes_int, int processes_arr[][4], FILE * file) {

    int* ready_queue = (int*)malloc(num_processes_int*sizeof(int));

    int ready_counter = 0;
    int next_process = 0;

    int* ready_by_process = (int*)malloc(num_processes_int*sizeof(int));
    int blocked = -1;
    int running = -1;

    int finish_times[num_processes_int];

    int status[num_processes_int][4];

    for(int i = 0; i < num_processes_int; i++) {
        status[i][0] = (int) i;
        status[i][1] = (int) 0; //this keeps count of CPU time used
        status[i][2] = (int) 0; //this keeps count of I/O time used
        status[i][3] = (int) processes_arr[i][3]; //arrival time

        ready_queue[i] = -1;
    }
    int time = 0;
    int exit = 0;
    int useful_cycles = 0;
    while(exit == 0){

        //if a process is completed
        if(running != -1) {
            if(status[running][1] >= processes_arr[running][1]) {
                if(status[running][2] >= processes_arr[running][2]) {
                    finish_times[running] = time;
                    ready_by_process[running] = 0;
                    running = -1;
                }
            }
        }

        //if done being blocked
        if(status[blocked][2] == processes_arr[blocked][2] && (status[blocked][2] != 0)) {
            ready_queue[ready_counter] = blocked;
            ready_counter = ready_counter+1;
            ready_by_process[blocked] = 1;
            blocked = -1;
        }
    
        //move to blocked state
        if(running > -1) {
            if(blocked == -1) {
                if((status[running][1] >= (processes_arr[running][1]/2)) && (status[running][2] == 0) && (processes_arr[running][2] >= 0)) {
                    ready_by_process[running] = 0;
                    blocked = running;
                    running = -1;
                }
            }        
        }

        //if nothing running, start running next process in queue
        if(running == -1) {
            if(ready_queue[next_process] > -1) {
                running = ready_queue[next_process];
                ready_queue[next_process] = -1;
                if(num_processes_int == 2) {
                    next_process = (next_process + 1) % (num_processes_int);
                }
                else {
                    next_process = (next_process + 1) % (num_processes_int+1);
                }
                ready_by_process[running] = 0;
            }           
        }

        char arrived[4] = {num_processes_int}; //keep track of process IDs that are now arrived
        int arrived_counter = 0;

        for(int i = 0; i < num_processes_int; i++) {
            if(status[i][3] == time) {
                arrived[arrived_counter] = status[i][0];
                arrived_counter += 1;
            }
        }

        if(arrived[0] != num_processes_int && (arrived[1] == num_processes_int)) { //just one
            
            if(running == -1){
                int p_id = arrived[0];
                running = p_id;
                ready_by_process[p_id] = 0;
            }
            else {
                int p_id = arrived[0];
                ready_queue[ready_counter] = p_id;
                ready_counter = (ready_counter+1)%(num_processes_int+1);
                ready_by_process[p_id] = 1;
            }

        } else {
            for(int i = 0; i < arrived_counter; i++) {
                int min_val = num_processes_int;
                int min_index = -1;
                for(int j = 0; j < arrived_counter; j++) {
                    int process = arrived[arrived_counter];
                    if(process < min_val) {
                        min_val = process;
                        min_index = j;
                    }
                }
                if(min_val == num_processes_int) {
                    break;
                }
                else {
                    arrived[min_index] = num_processes_int;
                    ready_by_process[min_val] = 1;
                    ready_queue[ready_counter] = min_val;
                    ready_counter = (ready_counter+1)%(num_processes_int+1);
                }

    
            }
        }

        //update statuses
        if(running != -1) {
            status[running][1] += 1;
            useful_cycles += 1;
        }
        for(int i = 0; i < num_processes_int; i++) {
            if(blocked == i) {
                status[i][2] += 1;
            }
            
        }
        //exit conditions
        for(int i = 0; i < num_processes_int; i++) {
            if(ready_by_process[i] == 1) {
                break;
            }
            if(running != -1) {
                break;
            }
            if(blocked != -1) {
                break;
            }

            //all exit conditions met
            if(i == num_processes_int - 1) {
                exit = 1;
            }
            
        }

        if(exit == 1) {
            float util = (float)useful_cycles / (float)time;
            fprintf(file, "%s","\n");
            fprintf(file, "%s %d %s", "\nFinishing time: ", time-1, "\n");
            fprintf(file, "%s %.2f %s", "CPU utilization: ", util, "\n");
            for(int j = 0; j < num_processes_int; j++) {
                fprintf(file, "%s %d%s %d %s","Turnaround process ", j, ":",(finish_times[j] - processes_arr[j][3]), "\n");
            }
        } 
        else {
            fprintf(file, "%s %d %s","\n", time, " ");
            for(int i = 0; i < num_processes_int; i++) {
                if(blocked == i){
                    fprintf(file, "%d%s",i, ":blocked ");
                    continue;
                }
                if(running == i){
                    fprintf(file, "%d%s",i, ":running ");
                    continue;
                }
                if(ready_by_process[i] == 1) {
                    fprintf(file, "%d%s",i, ":ready ");
                    continue;
                }  
                        
            }     
        }
        time++;
    }
    free(ready_queue);
    free(ready_by_process);

}

void RR(int num_processes_int, int processes_arr[][4], FILE * file) {   
    int* ready_queue = (int*)malloc(num_processes_int*sizeof(int));

    int ready_counter = 0;
    int next_process = 0;

    int* ready_by_process = (int*)malloc(num_processes_int*sizeof(int));
    int blocked = -1;
    int running = -1;

    int finish_times[num_processes_int];

    int status[num_processes_int][5];

    for(int i = 0; i < num_processes_int; i++) {
        status[i][0] = (int) i;
        status[i][1] = (int) 0; //this keeps count of CPU time used
        status[i][2] = (int) 0; //this keeps count of I/O time used
        status[i][3] = (int) processes_arr[i][3]; //arrival time
        status[i][4] = (int) 0; //keeps track of consecutive cycles

        ready_queue[i] = -1;
    }
    int time = 0;
    int exit = 0;
    int useful_cycles = 0;
    while(exit == 0){

        //if a process is completed
        if(running != -1) {
            if(status[running][1] >= processes_arr[running][1]) {
                if(status[running][2] >= processes_arr[running][2]) {
                    finish_times[running] = time;
                    ready_by_process[running] = 0;
                    running = -1;
                }
            }
        }


        //if done being blocked
        if(status[blocked][2] == processes_arr[blocked][2] && (status[blocked][2] != 0)) {
            ready_queue[ready_counter] = blocked;
            ready_counter = ready_counter+1;
            ready_by_process[blocked] = 1;
            blocked = -1;
           
        }
    
        //move to blocked state
        if(running > -1) {
            if(blocked == -1) {
                if((status[running][1] >= (processes_arr[running][1]/2)) && (status[running][2] == 0) && (processes_arr[running][2] >= 0)) {
                    ready_by_process[running] = 0;
                    blocked = running;
                    status[running][4] = 0;
                    running = -1;
                   
                }
            }        
        }

        //if a process has been running for 2 cycles now, move on to next
        if(running != -1 && (status[running][4] == 2)) {
            ready_queue[ready_counter] = running;
            ready_counter = (ready_counter+1) % (num_processes_int+1);
            ready_by_process[running] = 1;
            running = -1;
        }

        //if nothing running, start running next process in queue
        if(running == -1) {
            if(ready_queue[next_process] > -1) {
                running = ready_queue[next_process];
                ready_queue[next_process] = -1;
                
                if(num_processes_int == 2) {
                    next_process = (next_process + 1) % (num_processes_int);
                }
                else {
                    next_process = (next_process + 1) % (num_processes_int+1);
                }
                ready_by_process[running] = 0;
            }           
        }

        char arrived[4] = {num_processes_int}; //keep track of process IDs that are now arrived
        int arrived_counter = 0;

        for(int i = 0; i < num_processes_int; i++) {
            if(status[i][3] == time) {
                arrived[arrived_counter] = status[i][0];
                arrived_counter += 1;
            }
        }

        if((arrived[0] != num_processes_int)) { //just one
            
            if(running == -1){
                int p_id = arrived[0];
                running = p_id;
                ready_by_process[p_id] = 0;
            }
            else {
                int p_id = arrived[0];
                ready_queue[ready_counter] = p_id;
                ready_counter = (ready_counter+1)%(num_processes_int+1);
                ready_by_process[p_id] = 1;
            }

        } else {
            for(int i = 0; i < arrived_counter; i++) {
                int min_val = num_processes_int;
                int min_index = -1;
                for(int j = 0; j < arrived_counter; j++) {
                    int process = arrived[arrived_counter];
                    if(process < min_val) {
                        min_val = process;
                        min_index = j;
                    }
                }
                if(min_val == num_processes_int) {
                    break;
                }
                else {
                    arrived[min_index] = num_processes_int;
                    ready_by_process[min_val] = 1;
                    ready_queue[ready_counter] = min_val;
                    ready_counter = (ready_counter+1)%(num_processes_int+1);
                }
            }
        }

        //update statuses
        if(running != -1) {
            status[running][1] += 1;
            status[running][4] += 1;
            useful_cycles += 1;
        }
        for(int i = 0; i < num_processes_int; i++) {
            if(blocked == i) {
                status[i][2] += 1;
            }
            
        }
        //exit conditions
        for(int i = 0; i < num_processes_int; i++) {
            if(ready_by_process[i] == 1) {
                break;
            }
            if(running != -1) {
                break;
            }
            if(blocked != -1) {
                break;
            }

            //all exit conditions met
            if(i == num_processes_int - 1) {
                exit = 1;
            }
            
        }
        if(exit == 1) {
            float util = (float)useful_cycles / (float)time;
            fprintf(file, "%s","\n");
            fprintf(file, "%s %d %s", "\nFinishing time: ", time-1, "\n");
            fprintf(file, "%s %.2f %s", "CPU utilization: ", util, "\n");
            for(int j = 0; j < num_processes_int; j++) {
                fprintf(file, "%s %d%s %d %s","Turnaround process ", j, ":",(finish_times[j] - processes_arr[j][3]), "\n");
            }
        } 
        else {
            fprintf(file, "%s %d %s","\n", time, " ");
            for(int i = 0; i < num_processes_int; i++) {
                if(blocked == i){
                    fprintf(file, "%d%s",i, ":blocked ");
                    continue;
                }
                if(running == i){
                    fprintf(file, "%d%s",i, ":running ");
                    continue;
                }
                if(ready_by_process[i] == 1) {
                    fprintf(file, "%d%s",i, ":ready ");
                    continue;
                }  
                        
            }     
        }

        time++;
    }
    free(ready_queue);
    free(ready_by_process);    
}

void SRJF(int num_processes_int, int processes_arr[][4], FILE * file) {

    int* ready_by_process = (int*)malloc(num_processes_int*sizeof(int));
    int blocked = -1;
    int running = -1;

    int finish_times[num_processes_int];

    int status[num_processes_int][5];

    for(int i = 0; i < num_processes_int; i++) {
        status[i][0] = (int) i;
        status[i][1] = (int) 0; //this keeps count of CPU time used
        status[i][2] = (int) 0; //this keeps count of I/O time used
        status[i][3] = (int) processes_arr[i][3]; //arrival time
        status[i][4] = (int) processes_arr[i][1]; //remaining CPU time left
    }
    int time = 0;
    int exit = 0;
    int useful_cycles = 0;
    while(exit == 0){

        //if a process is completed
        if(running != -1) {
            if(status[running][1] >= processes_arr[running][1]) {
                if(status[running][2] >= processes_arr[running][2]) {
                    finish_times[running] = time;
                    ready_by_process[running] = 0;
                    running = -1;
                }
            }
        }

        //if done being blocked
        if(status[blocked][2] == processes_arr[blocked][2] && (status[blocked][2] != 0)) {
            ready_by_process[blocked] = 1;
            blocked = -1;
        }
    
        //move to blocked state
        if(running > -1) {
            if(blocked == -1) {
                if((status[running][1] >= (processes_arr[running][1]/2)) && (status[running][2] == 0) && (processes_arr[running][2] >= 0)) {
                    ready_by_process[running] = 0;
                    blocked = running;
                    running = -1;
                }
            }        
        }

        //get largest poss cpu time
        int longest = 0;
        for(int i = 0; i < num_processes_int; i++) {
            if(processes_arr[i][1] > longest) {
                longest = processes_arr[i][1];
            }
        }

        char arrived[4] = {num_processes_int}; //keep track of process IDs that are now arrived
        int arrived_counter = 0;

        for(int i = 0; i < num_processes_int; i++) {
            if(status[i][3] == time) {
                arrived[arrived_counter] = status[i][0];
                arrived_counter += 1;
            }
        }

        if((arrived[0] != num_processes_int) && (arrived[1] == num_processes_int)) { //just one
            
            if(running == -1){
                int p_id = arrived[0];
                running = p_id;
                ready_by_process[p_id] = 0;
            }
            else {
                int p_id = arrived[0];
                ready_by_process[p_id] = 1;
            }

        } else {
            for(int i = 0; i < arrived_counter; i++) {
                int min_val = num_processes_int;
                int min_index = -1;
                for(int j = 0; j < arrived_counter; j++) {
                    int process = arrived[arrived_counter];
                    if(process < min_val) {
                        min_val = process;
                        min_index = j;
                    }
                }
                if(min_val == num_processes_int) {
                    break;
                }
                else {
                    arrived[min_index] = num_processes_int;
                    ready_by_process[min_val] = 1;
                }

            }
        }

        //if nothing running, start running next process in queue based on shortest time remaining
        int min_process = -1;
        int min_val = longest;

        for(int i = 0; i < num_processes_int; i++) {
            if((ready_by_process[i] == 1) && (status[i][4] <= min_val)) {
                min_process = i;
                min_val = status[i][4];
            }
        }

        if(min_process != -1) {
            if(running == -1) {
                running = min_process;
                ready_by_process[min_process] = 0;   
            }
            else if(running > -1 && status[running][4] > status[min_process][4]){
                ready_by_process[running] = 1;
                running = min_process;
                ready_by_process[min_process] = 0;   
            }
        }
  


        //update statuses
        if(running != -1) {
            status[running][1] += 1;
            status[running][4] -= 1;
            useful_cycles += 1;
        }
        for(int i = 0; i < num_processes_int; i++) {
            if(blocked == i) {
                status[i][2] += 1;
            
            }
            
        }
        //exit conditions
        for(int i = 0; i < num_processes_int; i++) {
            if(ready_by_process[i] == 1) {
                break;
            }
            if(running != -1) {
                break;
            }
            if(blocked != -1) {
                break;
            }

            //all exit conditions met
            if(i == num_processes_int - 1) {
                exit = 1;
            }
            
        }
        if(exit == 1) {
            float util = (float)useful_cycles / (float)time;
            fprintf(file, "%s","\n");
            fprintf(file, "%s %d %s", "\nFinishing time: ", time-1, "\n");
            fprintf(file, "%s %.2f %s", "CPU utilization: ", util, "\n");
            for(int j = 0; j < num_processes_int; j++) {
                fprintf(file, "%s %d%s %d %s","Turnaround process ", j, ":",(finish_times[j] - processes_arr[j][3]), "\n");
            }
        } 
        else {
            fprintf(file, "%s %d %s","\n", time, " ");
            for(int i = 0; i < num_processes_int; i++) {
                if(blocked == i){
                    fprintf(file, "%d%s",i, ":blocked ");
                    continue;
                }
                if(running == i){
                    fprintf(file, "%d%s",i, ":running ");
                    continue;
                }
                if(ready_by_process[i] == 1) {
                    fprintf(file, "%d%s",i, ":ready ");
                    continue;
                }  
                        
            }     
        }

        time++;
    }

    free(ready_by_process);

}

int main(int argc, char* argv[]) {

    char* processes = argv[1];
    char* type_str = argv[2];
    int type =  atoi(type_str);

    FILE * filepointer = fopen(processes, "r");
    
    char num_processes[5];
    fgets(num_processes, 5, filepointer);
    int num_processes_int = num_processes[0] - '0';

    int line_counter = 1;
    int processes_arr[num_processes_int][4];
    while(line_counter <= num_processes_int){
        char str[10];
        fgets(str, 10, filepointer);
        int p_id = str[0] - '0';
        int cpu_time = str[2] - '0';
        int i_o_time = str[4] - '0';
        int arrival = str[6] - '0';
        processes_arr[p_id][0] = p_id;
        processes_arr[p_id][1] = cpu_time;
        processes_arr[p_id][2] = i_o_time;
        processes_arr[p_id][3] = arrival;
        line_counter++;
    }
    fclose(filepointer);

    //output file
    char* output_file_name = (char*)(malloc(sizeof(processes)));
    char* dot = ".";
    for(int i = 0; i < sizeof(processes)+2; i++) {
        if( processes[i] == dot[0]) {
            break;
        }
        output_file_name[i] = processes[i];
    }

    strcat(output_file_name, "-");
    strcat(output_file_name, argv[2]);
    strcat(output_file_name, ".txt");

    //printf("%s", output_file_name);
    FILE* fp_out = fopen(output_file_name, "a");

    if(type == 0) {
        FCFS(num_processes_int, processes_arr, fp_out);
    }
    else if(type == 1) {
        RR(num_processes_int, processes_arr, fp_out);
    }
    else if(type == 2) {
        SRJF(num_processes_int, processes_arr, fp_out);
    }

    fclose(fp_out);

}