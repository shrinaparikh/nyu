#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Oct  5 21:11:01 2020

@author: shrinaparikh
"""
import re
f = open("frontend_input.txt", "r")
dp_input = f.read()
dp_input = dp_input.split('\n')
line1 = dp_input[0].split()
holes = int(line1[0])
empty_hole = int(line1[1])
potential_jumps = []
for line in dp_input:
    line = line.split()
    if(len(line) == 2):
        continue
    potential_jumps.append([line[0], line[1], line[2]])

###file to write to 
f = open("frontend_output.txt", "w")


max_time = holes - 1

axioms = []
jumps = []
pegs = []
axiom_counter = 0

#turning input into sentences - jumps, appending to axioms as well
for jump in potential_jumps:
    for time in range(1, max_time):
        j = "Jump(" + jump[0] + "," + jump[1] + "," + jump[2] + "," + str(time) + ")"
        axioms.append(j)
        jumps.append(j)
    for time in range(1, max_time):
        j2 = "Jump(" + jump[2] + "," + jump[1] + "," + jump[0] + "," + str(time) + ")"     
        axioms.append(j2)
        jumps.append(j2)
#now append pegs to axioms     
for i in range(1,holes+1):
    for j in range(1, max_time+1):
        peg = "Peg(" + str(i) + "," + str(j) + ")"
        axioms.append(peg)       

#create starting state, as an array
def create_starting():
    pegs = []
    for h in range(1,holes+1):
        if (h == empty_hole):
            pegs.append("-Peg(" + str(h) + ",1)")
        else:
            pegs.append("Peg(" + str(h) + ",1)")
    return pegs
create_starting()
            
#for h in range(1,holes+1):
#    if (h == empty_hole):
#        pegs.append("-Peg(" + str(h) + ",1)")
#        for t in range(2,max_time+1):
#            pegs.append("Peg(" + str(h) + "," + str(t) + ")")
#        continue
#    for t in range(1,max_time+1):
#        pegs.append("Peg(" + str(h) + "," + str(t) + ")")


#create starting state sentence, now as a string
#start = ''
#for peg in pegs:
#    if(peg == pegs[0]):
#        start = peg
#        continue
#    start = start + " ^ " + peg
#print("\n Starting State: ", start)

def get_nums(jump):
    nums = []
    jump_arr = re.split('\(|\)|,',jump)
    nums.append(jump_arr[1]) #peg1
    nums.append(jump_arr[2]) #peg2
    nums.append(jump_arr[3]) #peg3
    nums.append(jump_arr[4]) #time
    return nums

    
####GETTING ALL AXIOMS AS STRINGS
precondition_axioms = []
def get_precondition_axioms(jumps):
    for jump in jumps:
        nums = get_nums(jump)
        peg1 = nums[0]
        peg2 = nums[1]
        peg3 = nums[2]
        time = nums[3]
        
        axiom = jump + " => " + "Peg(" + peg1 + "," + time + ")" 
        axiom = axiom + " ^ " + "Peg(" + peg2 + "," + time + ")" + " ^ " + "-Peg(" + peg3 + "," + time + ")"
        precondition_axioms.append(axiom)  
get_precondition_axioms(jumps)



casual_axioms = []
def get_casual_axioms(jumps):
    for jump in jumps:
        nums = get_nums(jump)
        peg1 = nums[0]
        peg2 = nums[1]
        peg3 = nums[2]
        time = str(int(nums[3]) + 1)
        axiom = jump + " => " + "-Peg(" + peg1 + "," + time + ")" + " ^ "
        axiom = axiom + "-Peg(" + peg2 + "," + time + ")" + " ^ " + "Peg(" + peg3 + "," + time + ")"
        casual_axioms.append(axiom) 
get_casual_axioms(jumps)

##frame axioms now
frame_axioms = []
def get_frame_axioms():
    for i in range(1,holes+1):
        for j in range(1, max_time):
            options = ''
            peg1 = "Peg(" + str(i) + "," + str(j) + ")"
            peg2 = "-Peg(" + str(i) + "," + str(j+1) + ")" 
            for jump in jumps:
                nums = get_nums(jump)
                peg1_num = nums[0]
                peg2_num = nums[1]
                time = nums[3]
                if((peg1_num == str(i) or peg2_num == str(i)) and (peg1[-2] == time)):
                    if(options == ''):
                        options = jump
                    else:
                        options = options + " V " + jump                   
            axiom = peg1 + " ^ " + peg2 + " => " + options
            frame_axioms.append(axiom)
get_frame_axioms()
   


#No two axioms can be executed at the same time
one_at_a_time = []
def check():
    for i in range(0,len(jumps)):
        one = jumps[i]
        for j in range(i+(max_time-1), len(jumps), max_time-1):
            two = jumps[j]
            axiom = "-(" + one + " ^ "
            axiom = axiom + two + ")" 
            one_at_a_time.append(axiom)    
check()



ending = []
def check_ending():
    for i in range(1, holes):
        peg1 = "Peg(" + str(i) + "," + str(max_time) + ")"
        for j in range(i+1, holes+1):
            peg2 = "Peg(" + str(j) + "," + str(max_time) + ")"
            ending.append("-(" + peg1 + " ^ " + peg2 + ")")
check_ending() 










def encoding():
    
    for jump in axioms:
        if (jump[0] != 'J'):
            break
        else:
            for ele in precondition_axioms:
                if jump in ele:
                    ele = ele.split()
                    f.write("-" + str(axioms.index(jump) + 1) + " " + str(axioms.index(ele[2]) + 1) + "\n")
                    f.write("-" + str(axioms.index(jump) + 1) + " " + str(axioms.index(ele[4]) + 1) + "\n")
                    f.write("-" + str(axioms.index(jump) + 1) + " -" + str(axioms.index(ele[6][1:]) + 1) + "\n")
    for jump in axioms:
        if(jump[0] != 'J'):
            break;
        else:
            for ele in casual_axioms:
                if jump in ele:
                    ele = ele.split()
                    f.write("-" + str(axioms.index(jump) + 1) + " -" + str(axioms.index(ele[2][1:]) + 1) + "\n")
                    f.write("-" + str(axioms.index(jump) + 1) + " -" + str(axioms.index(ele[4][1:]) + 1) + "\n")
                    f.write("-" + str(axioms.index(jump) + 1) + " " + str(axioms.index(ele[6]) + 1) + "\n")
    

    
    for ele in frame_axioms:
        ele = ele.split()
        out = "-" + str(axioms.index(ele[0]) + 1) + " " + str(axioms.index(ele[2][1:]) + 1) + " " 
        for i in range(4, len(ele), 2):
            out = out + str(axioms.index(ele[i]) + 1) + " "
        out = out + "\n"
        f.write(out)
        

    for ele in one_at_a_time:
        ele = ele.split()
        f.write("-" + str(axioms.index(ele[0][2:])+1) + " -" + str(axioms.index(ele[2][:-1])+1) + "\n")
    start = create_starting()
    for ele in start:
        if(ele[0] == '-'):
            f.write("-" + str(axioms.index(ele[1:]) + 1) + '\n')
        else:
            f.write(str(axioms.index(ele) + 1) + '\n')
        

    for ele in ending:
        ele = ele.split()
        f.write("-" + str(axioms.index(ele[0][2:])+1) + " -" + str(axioms.index(ele[2][:-1])+1) + "\n")
        
    f.write("0\n")
    
    for item in axioms:
        f.write(str(axioms.index(item) + 1) + " " + item + "\n")
    
        
    
    
        
encoding()           
f.close()       