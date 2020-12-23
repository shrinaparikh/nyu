#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Oct 10 17:02:33 2020

@author: shrinaparikh
"""

f = open("dp_output.txt", "r")
w = open("backend_output.txt", "w")

backend_input = f.read()

if(backend_input == "NO SOLUTION"):
    w.write("NO SOLUTION")
else:
    backend_input = backend_input.split('\n0')
    soln = backend_input[0].split('\n')
    jumps = backend_input[1].split('\n')
    soln2 = []
    jumps2 = []
    for ele in soln:
        ele = ele.split()
        soln2.append(ele)
    for ele in jumps:
        ele = ele.split()
        jumps2.append(ele)
    for soln in soln2:
        if(soln[1] == 'F'):
            continue
        index = soln[0]
        for jump in jumps2:
            if(jump == []):
                continue
            if(jump[0] == index and jump[1][0] == 'J'):
                w.write(jump[1])
                w.write('\n')