#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Sep 13 11:28:09 2020

@author: shrinaparikh
"""
#helper functions    
def check_soln(vertices_arr, budget):
    if(get_cost(vertices_arr) > int(budget)):
        return False
    for i in vertices_arr:
        for edge in edges:
            if(edge[0] == i):
                edges[edge] = 1
            elif(edge[1] == i):
                edges[edge] = 1   
    for edge in edges:
        if(edges[edge] == 0):
            for edge in edges:
                edges[edge] = 0
            return False
    return True
        

def get_cost(vertices_arr):
    sum = 0
    for vertex in vertices_arr:
        sum += int(vertices[vertex])
    return sum



def DFS(root, depth, arr, finished):
    
    if(len(arr) < depth):
        arr.append(root)
        
    if depth <= 0:
        return False
    
    neighbors = []
    states = []
    
    if(finished != True):
        if(check_soln(arr, budget)): 
            print("Found solution ", arr, ' ', "Cost: ", get_cost(arr))
            finished = True
            return True
        if(flag == 'V'):
            print(arr, "Cost: ", get_cost(arr))
    
    index = vertices_arr.index(root)
    for vertex in vertices_arr[index+1:]:
        neighbors.append(vertex)
        
    for neighbor in neighbors:
        arr2 = arr.copy()
        arr2.append(neighbor)
        states.append(arr2)
        
    for state in states:
        if(finished == True):
            print("true")
            continue
        else:
            DFS(state[len(state)-1], depth-1, state, finished)
        
        
        
def iter_deep():
    for i in range(1,len(vertices_arr)-1):
        if(flag == 'V'):
            print("Depth", i)
        for vertex in vertices:
            if(DFS(vertex, i, [], False)):
                return True
    print("No solution")
    return False 
    
#file processing
f = open("IDinput.txt", "r")
id_input = f.read().split('\n')
line1 = id_input[0].split()
budget = line1[0]
flag = line1[1]
vertices_arr = []
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

#run
iter_deep()



