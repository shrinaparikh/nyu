#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Oct 29 14:09:26 2020

@author: shrinaparikh
"""
import random

#parse input
f = open("input.txt", "r")
input = f.read().split('\n')

line1 = input[0].split()
num_nonterm_states = int(line1[0])
n = num_nonterm_states
num_term_states = int(line1[1])
num_rounds = int(line1[2])
print_freq = int(line1[3])
M = int(line1[4])

actions = []
actions_by_state = dict()

rewards = dict()
line2 = input[1].split()
for i in range(0,len(line2)-1, 2):
    rewards[int(line2[i])] = int(line2[i+1]) 
transition_probs = dict()
for i in range(2,len(input)):
    line = input[i].split()
    key = line[0]
    parsing_key = key.split(":")
    if(int(parsing_key[1]) not in actions):
        actions.append(int(parsing_key[1]))
    if(int(parsing_key[0]) in actions_by_state):
        temp = actions_by_state[int(parsing_key[0])]
        temp.append(int(parsing_key[1]))
        actions_by_state[parsing_key[0]] = temp
    else:
        arr = []
        arr.append(int(parsing_key[1]))
        actions_by_state[int(parsing_key[0])] = arr

    values = dict()
    for j in range(1, len(line)-1, 2):
        values[int(line[j])] = float(line[j+1])
    transition_probs[key] = values  
    
   
#learning
count = []
total = []
for i in range(num_nonterm_states):
    row = []
    row2 = []
    for j in range(len(actions)): 
        vals = actions_by_state[str(i)]
        if(j in vals):
            row.append(int(0))
            row2.append(int(0))
        else:
            row.append("N/A")
            row2.append("N/A")
    count.append(row)
    total.append(row2)

#calculating best action
def chooseAction(s, count, total, M):
    n = len(count[s]) 
    
    untried = []
    for i in range(0,n):
        if (count[s][i] == int(0)): #choosing an untried action arbitrarily 
            untried.append(i) #appending the indices of the untried     

    #pick a random value if untried as values in it 
    if (not(len(untried) == 0)):
        index = random.randint(0,len(untried)-1)
        return untried[index] 
    
    avgs = [] 
    for i in range(0,n):
        if(count[s][i] != "N/A"):
            avgs.append(total[s][i] / count[s][i])
  
    bottom = min(rewards.values()) 
    top = max(rewards.values()) 
    
    savgs = []
    for i in range(0,n):
        if(count[s][i] != "N/A"):
            savgs.append(0.25 + 0.75*(avgs[i] - bottom) / (top - bottom))
    
    c = 0
    for i in range(0,n):
        if(count[s][i] != "N/A"):
            c += count[s][i]
       
    up = []
    for i in range(0, n):
        if(count[s][i] != "N/A"):
            up.append(savgs[i]**(c/M))
    
    norm = 0
    for i in range(0, n):
        if(count[s][i] != "N/A"):
            norm += up[i]
        
    p = []
    for i in range(0, n):
        if(count[s][i] != "N/A"):
            p.append(up[i]/norm)
    
    choices = []
    for i in range(0,n):
        if(count[s][i] != "N/A"):
            choices.append(i)

    i = random.choices(choices, p, k=1) 
    
    return [i[0],p[i[0]]]

round_ = 1
    
while(round_ <= num_rounds):
    visits = dict()
    action = -1
    s = random.randint(0,n-1)                 #generate random start state

    while(s < num_nonterm_states):
        get = chooseAction(s, count, total, M)

        if(type(get) is int):
            action = get
        elif(type(get) is list): 
            action = get[0]
            prob = get[1]
            
   
        if(s in visits.keys() and (action in visits[s])):
            pass
        elif (s in visits.keys() and (action not in visits[s])):
            temp = visits[s].copy()
            temp.append(action)
            visits[s] = temp
        else:        
            visits[s] = [action]
                     
        
        move = str(s) + ":" + str(action)
        val = transition_probs[move]
        
        s_arr = random.choices(list(val.keys()), list(val.values()), k=1)
        s = s_arr[0]

    #total reward of those rounds
    
    if(s in range(n, n+num_term_states)):
        for key in visits:
            if(visits[key]):
                for ele in visits[key]:
                    count[key][ele] += 1
                    total[key][ele] += rewards[s]
            
        if(round_ % print_freq == 0):
            print("\nAfter " + str(round_) + " rounds:")
            print("Count")
            for i in range(0,n):
                for j in range(0,len(count[i])):
                    print("[" + str(i) + "," + str(j) + "]" + " = " + str(count[i][j]))
            
            print("\nTotal")
            for i in range(0,n):
                for j in range(0,len(total[i])):
                    print("[" + str(i) + "," + str(j) + "]" + " = " + str(total[i][j]))  
                
        #to calculate best options 
        best_options = dict()
        for i in count:
            index = count.index(i)
            highest_reward = 0
            row = 0
            column = 0
            for j in range(0,(len(i))):
                if(i[j] == 0): 
                    best_options[index] = "U" 
                    continue
                    
                if(i[j] != "N/A" and i[j] > 0):                    
                    avg_reward = total[index][j] / i[j]
                    if(avg_reward >= highest_reward):
                        highest_reward = avg_reward
                        row = index
                        column = j

            if(index not in best_options):
                best_options[index] = str(column)

        if(round_ % print_freq == 0):
            print("Best action")
            for key in best_options:
                print(str(key) + ":" + best_options[key])
        

                    
        round_ += 1


    

    
        
    
    
