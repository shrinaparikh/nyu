#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Oct  1 13:15:56 2020

@author: shrinaparikh
"""
import copy
clause_states = []
peg_states = []
clauses = []
pegs = {}
f = open("frontend_output.txt", "r")
dp_input = f.read()
dp_input = dp_input.split('\n0')
backmatter = dp_input[1]
dp_input = dp_input[0]
dp_input = dp_input.split('\n')
pegs_check = {}

w = open("dp_output.txt", "w")


for clause in dp_input:
    clause = clause.split()
    for item in clause:
        item = item.strip()
        clause[clause.index(item)] = int(item)
        if(abs(int(item)) not in pegs):
            pegs_check[abs(int(item))] = 1
    if(clause != []):
        clauses.append(clause)
      
def hasPureLiteral(clauses_arr):
    atoms = {}
    for i in clauses_arr:
        for j in i:
            if((-1*j) in atoms):
                atoms[j] = 0
            elif(j in atoms):
                pass
            else:
                atoms[j] = 1
    if(0 in atoms.values()):
        return False
    return True
                
def easyCaseIn(clauses_arr, pegs):
    for clause in clauses_arr:
        if(len(clause) == 1):
            return True
    if(hasPureLiteral(clauses_arr)):
        return True

def easyCase(clauses_arr, pegs):
    for clause in clauses_arr:
        if(len(clause) == 1):
            atom = clause[0]
            if(atom < 0):
                value = 'F'
            else:
                value = 'T'
            return propogate(clauses_arr, pegs, atom, value)   
        #pure literal case
    atoms = {}
    for i in clauses_arr:
        for j in i:
            if((-1*j) in atoms):
                atoms[j] = 0
            elif(j in atoms):
                pass
            elif(j not in atoms):
                atoms[j] = 1
    if(1 in atoms.values()):
        for key, val in atoms.items():
            if val == 1:
                atom = key
                if(atom < 0):
                    value = 'F'
                else:
                    value = 'T'                
                return propogate(clauses_arr, pegs, atom, value)
           

def propogate(clauses_arr, pegs, atom, value): #must pass in atom as an int
    to_pop = [] 
    popping_counter = 0;
    pegs[abs(atom)] = value
    if(value == 'T' and atom > 0):
        for i in range(len(clauses_arr)):
            if (atom in clauses_arr[i]):
                to_pop.append(i)
        for index in to_pop:
            clauses_arr.pop(index - popping_counter)
            popping_counter += 1
        for i in range(len(clauses_arr)):
            if ((-1*atom) in clauses_arr[i]):
                clauses_arr[i].pop(clauses_arr[i].index(atom*-1))
    elif (value == 'T' and atom < 0):
        for i in range(len(clauses_arr)):
            if ((-1*atom) in clauses_arr[i]):
                to_pop.append(i)
        for index in to_pop:
            clauses_arr.pop(index - popping_counter)
            popping_counter += 1
        for i in range(len(clauses_arr)):
            if (atom in clauses_arr[i]):
                clauses_arr[i].pop(clauses_arr[i].index(atom))            
    elif (value == 'F' and atom > 0): 
        for i in range(len(clauses_arr)):
            if((-1*atom) in clauses_arr[i]):
                to_pop.append(i)
        for index in to_pop:
            clauses_arr.pop(index - popping_counter)
            popping_counter += 1  
        for i in range(len(clauses_arr)):
            if (atom in clauses_arr[i]):
                clauses_arr[i].pop(clauses_arr[i].index(atom)) 
    elif (value == 'F' and atom < 0): 
        for i in range(len(clauses_arr)):
            if(atom in clauses_arr[i]):
                to_pop.append(i)
        for index in to_pop:
            clauses_arr.pop(index - popping_counter)
            popping_counter += 1
        for i in range(len(clauses_arr)):
            if ((-1*atom) in clauses_arr[i]):
                clauses_arr[i].pop(clauses_arr[i].index(atom*-1)) 
    to_pop = []

    return (clauses_arr, pegs)


def choose_atom(clauses):
    p = 1001 
    for i in clauses:
        for atom in i:
            if((abs(atom)) < p):
                p = abs(atom)
    return p
   

         
    
#DP
def davis_putnam(clauses, pegs):
    loop = True
    while(loop == True):
        loop1 = False
        loop2 = False
        loop3 = False
        
        if(len(clauses) == 0):
            loop1 = True
            if(len(pegs) < len(pegs_check)):
                for peg in pegs_check:
                    if(peg not in pegs):
                        pegs[abs(peg)] = 'T'
            return pegs
        for clause in clauses:
            if(clause == []):
                loop2 = True
                return 'Fail'
        if(easyCaseIn(clauses, pegs)):
            loop3 = True
            clauses, pegs = easyCase(clauses, pegs)
        if(loop1 == False and loop2 == False and loop3 == False):
            loop = False
            
    CScopy = copy.deepcopy(clauses)
    Bcopy = pegs.copy()
    
    P = choose_atom(clauses)
    
    CScopy, Bcopy = propogate(CScopy, Bcopy, P, 'T')
    
    answer = davis_putnam(CScopy,Bcopy)
    if (answer != 'Fail'):
        return answer
    

    clauses, pegs = propogate(clauses, pegs, P, 'F')
    
    return davis_putnam(clauses, pegs)


result = davis_putnam(clauses,pegs)   

if(result == 'Fail'):
    w.write("NO SOLUTION")
else:
    for key in sorted(result):
        w.write(str(key) + " " + str(result[key]) + "\n")
        print(str(key) + " " + str(result[key]) + "\n")
    w.write("0\n")
    w.write(backmatter)

