#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Sep 15 16:36:47 2020

@author: shrinaparikh
"""
     
import random #for random restarts

#file processing
f = open("HCinput.txt", "r")
id_input = f.read().split('\n')
line1 = id_input[0].split()
budget = line1[0]
flag = line1[1]
vertices_arr = []
restarts = line1[2]
vertices = dict()
edges = dict()
mode = True

for line in id_input:

    if line == id_input[0]: 
        continue
    if line == "":
        mode = False
        continue
    line = line.split()
    if(mode == True):
        vertex = line[0]
        cost = line[1]
        vertices[vertex] = cost
        vertices_arr.append(vertex)
    else:
        vertex1 = line[0]
        vertex2 = line[1]
        edge = vertex1+vertex2
        edges[edge] = 0

#verify solution is valid
def check_soln(vertices_arr, budget):
    
    #verify solution is under budget
    if(get_cost(vertices_arr) > int(budget)):
        return False  
    #check edges for solution
    for i in vertices_arr:
        for edge in edges:
            if(edge[0] == i):
                edges[edge] = 1
            elif(edge[1] == i):
                edges[edge] = 1   
    for edge in edges:
        if(edges[edge] == 0):
            return False   
    return True    
   
#get neighbor states of current state    
def get_neighbors(vertices_arr):
    neighbors = []
    length = len(vertices_arr)
    if(length < len(vertices)):
        for vertex in vertices:
            #adding a vertex
            if(not (vertex in vertices_arr)):
                neighbor = vertices_arr.copy()
                neighbor.append(vertex)
                neighbors.append(neighbor)
    if(length != 0):
        for vertex in vertices_arr:
            if(vertex in vertices_arr):
                #removing a vertex
                neighbor = vertices_arr.copy()
                neighbor.pop(vertices_arr.index(vertex))
                neighbors.append(neighbor)
    return neighbors

#get cost of a state
def get_cost(vertices_arr):
    sum = 0
    for vertex in vertices_arr:
        sum += int(vertices[vertex])   
    return sum

#get error of a state
def get_error(vertices_arr):
    error = max(0, (get_cost(vertices_arr) - int(budget))) + int(sum_uncovered_edges(vertices_arr))
    return error
   
#get_error helper function to get cost of uncovered edges of a state
def sum_uncovered_edges(vertices_arr):
    sum_ = 0
    for i in vertices_arr:
        for edge in edges:
            if(edge[0] == i):
                edges[edge] = 1
            elif(edge[1] == i):
                edges[edge] = 1  
    for edge in edges:
        if(edges[edge] == 0):
            v1 = str(edge[0])
            v1_cost = vertices[v1]
            v2 = str(edge[1])
            v2_cost = vertices[v2]
            if(v1_cost < v2_cost):
                sum_ += int(v1_cost)
            else:
                sum_ += int(v2_cost)
    for edge in edges:
        edges[edge] = 0
    return sum_
  
#return random state
def random_restart():
    state = []
    for vertex in vertices:
        decision = random.randint(1,2)
        if(decision == 1):
            state.append(vertex)
    return state
        
             
def hill_climbing(start_state, restarts):
    states = []
    if(flag == 'V'):
        print("Randomly chosen start state: ", start_state)
    states.append(start_state)
    if(flag == 'V'):
        print("Cost:", get_cost(start_state), "Error", get_error(start_state))
    if(check_soln(start_state, budget)):
        print("Solution found", start_state, "Cost:", get_cost(start_state), "Error", get_error(start_state))
        return
    while(int(restarts) > 0):
        errors = [] #store error values of each neighbor of state
        curr_error = get_error(start_state) #store for comparison
        neighbors = get_neighbors(start_state)
        if(flag == 'V'):
            print("Neighbors: ")
        for neighbor in neighbors:
            error = get_error(neighbor)
            if(flag == 'V'):
                print(neighbor,"Cost:", get_cost(neighbor), "Error", get_error(neighbor))
            errors.append(error)
        if(flag == 'V'):
            print('\n')
        min_error = min(errors) #get best option from neighbors, lowest error
        index = errors.index(min_error)
        start_state = neighbors[index] #update current state to lowest error option

        #no better option
        if(min_error >= curr_error):
            if(flag == 'V'):
                print("Search Failed")
            restarts = int(restarts) - 1
            start_state = random_restart()
            if(int(restarts) == 0):
                continue
            if(flag == 'V'):
                print("Randomly chosen start state: ", start_state, "Cost:", get_cost(start_state), "Error", get_error(start_state))
        else: 
            if(flag == 'V'):
                print("Move to:", start_state, "Cost:", get_cost(start_state), "Error", get_error(start_state))
            if(check_soln(start_state, budget)):
                print("Solution found")
                return    
    print("No solution found")

#create initial random start state, then function call
init_start = random_restart()
hill_climbing(init_start, restarts)

    
