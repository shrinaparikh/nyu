#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Nov 15 14:28:54 2020

@author: shrinaparikh
"""

import csv
import sys
import math
import random

f = open("prog4Data.csv", "r")


num_training_rows = int(sys.argv[1])
num_testing_rows = int(sys.argv[2])

if(len(sys.argv) == 4):
    verbose = True
else:
    verbose = False
    
    
a6_freq = {} #freq of a6 values
a6_freq[1] = 0;
a6_freq[2] = 0;
a6_freq[3] = 0;

# 3 array to keep track of frequencies
# one array for each possible value of A6

a6_1 = []
a6_2 = []
a6_3 = []

#each row 1-5 (row 0 is empty for ease of programming) in each array is for A1-A5
for i in range(0,6):
    a6_1.append([0,0,0,0,0]) #a6_1[1][1] counts the number of instances of a6 and a1 being 1
    a6_2.append([0,0,0,0,0]) #a6_2[2][3] counts the number of instances of a6 being 2 and a2 being 3
    a6_3.append([0,0,0,0,0])  
    

#now read in the data and populate the arrays and dictionary
reader = csv.reader(f, delimiter = ',')
header = next(reader) #skip header line

line_counter = 0
for line in reader:
    if(line_counter >= num_training_rows):
        line_counter += 1
        continue

    if(line[5] == "1"):
        a6_freq[1] = a6_freq[1] + 1
        a6_1[1][int(line[0])] += 1
        a6_1[2][int(line[1])] += 1
        a6_1[3][int(line[2])] += 1
        a6_1[4][int(line[3])] += 1
        a6_1[5][int(line[4])] += 1
    if(line[5] == "2"):
        a6_freq[2] = a6_freq[2] + 1
        a6_2[1][int(line[0])] += 1
        a6_2[2][int(line[1])] += 1
        a6_2[3][int(line[2])] += 1
        a6_2[4][int(line[3])] += 1 
        a6_2[5][int(line[4])] += 1
    if(line[5] == "3"):
        a6_freq[3] = a6_freq[3] + 1
        a6_3[1][int(line[0])] += 1
        a6_3[2][int(line[1])] += 1
        a6_3[3][int(line[2])] += 1
        a6_3[4][int(line[3])] += 1 
        a6_3[5][int(line[4])] += 1
    
    line_counter += 1
  
        
a6_logs = {}
for i in range(0,3):
    #calculate lp for each a6 value 1,2,3
    T = a6_freq[i+1]
    log_of_val = (T + 0.1)/(num_training_rows + 0.3)
    log = -1*math.log2(log_of_val) #https://www.geeksforgeeks.org/log-functions-python/
    a6_logs[i+1] = log
   

#to store lp values for condition probabilities
lp_a6_1 = []
lp_a6_2 = []
lp_a6_3 = []

#each row 1-5 (row 0 is empty for ease of programming) in each array is for A1-A5
for i in range(0,6):
    lp_a6_1.append([0,0,0,0,0]) #lp_a6_1[1][1] stores the lp value of (X.a1 = 1 | X.a6 = 1)
    lp_a6_2.append([0,0,0,0,0]) #a6_2[2][3] counts the number of instances of a6 being 2 and a2 being 3
    lp_a6_3.append([0,0,0,0,0]) 


for attribute in range(1,6):
    for val in range(1,5):
        log_of_val = (a6_1[attribute][val] + 0.1) / (a6_freq[1] + 0.4)
        log = -1*math.log2(log_of_val)
        lp_a6_1[attribute][val] = log

for attribute in range(1,6):
    for val in range(1,5):
        log_of_val = (a6_2[attribute][val] + 0.1) / (a6_freq[2] + 0.4)
        log = -1*math.log2(log_of_val)
        lp_a6_2[attribute][val] = log

for attribute in range(1,6):
    for val in range(1,5):
        log_of_val = (a6_3[attribute][val] + 0.1) / (a6_freq[3] + 0.4)
        log = -1*math.log2(log_of_val)
        lp_a6_3[attribute][val] = log        
     
        
accuracy_counter = 0
acc = 0
Q = 0
C = 0

#testing data
f.seek(0)
testing_start = line_counter - num_testing_rows

for i in range(0, line_counter):
    if(i <= testing_start):
        next(reader)
        continue

a6_test_freq = {1:0, 2:0, 3:0}
for line in reader:

    sums = {}
    s1 = 0
    s2 = 0
    s3 = 0
    s1 += a6_logs[1]

    s2 += a6_logs[2]
    s3 += a6_logs[3]  
    if(line[5] == "1"):
        a6_test_freq[1] += 1
    elif(line[5] == "2"):
        a6_test_freq[2] += 1
    elif(line[5] == "3"):
        a6_test_freq[3] += 1
    for attribute in range(1,6):
        s1 += lp_a6_1[attribute][int(line[attribute-1])]
        s2 += lp_a6_2[attribute][int(line[attribute-1])]
        s3 += lp_a6_3[attribute][int(line[attribute-1])]
    min_val = min([s1,s2,s3])
    
    #breaking ties arbitrarily
    if((s1 == s2) & (s1 == min_val)):
        predicted = random.randint(1,2)
    elif((s1 == s3) & (s1 == min_val)):
        tie_breaker = random.randint(1,2)
        if(tie_breaker == 1):
            predicted = 1
        else:
            predicted = 3
    elif((s2 == s3) & (s2 == min_val)):
        predicted = random.randint(1,2)
    elif(s1 == s2 == s3):
        predicted = random.randint(1,3)
    
    else:    
        if(min_val == s1):
            predicted = 1
        elif(min_val == s2):
            predicted = 2
        elif(min_val == s3):
            predicted = 3
    if((predicted == 3) & (line[5] == "3")):
        accuracy_counter += 1
    if(predicted == 3):
        Q += 1   
    if( predicted == int(line[5])):
        acc += 1
        
if(verbose == True):
    print("%.4f \t %.4f \t %.4f " % (a6_logs[1], a6_logs[2], a6_logs[3]))
    print("\n")
    
    print("%.4f \t %.4f \t %.4f \t %.4f" % (lp_a6_1[1][1], lp_a6_1[1][2], lp_a6_1[1][3], lp_a6_1[1][4]))
    print("%.4f \t %.4f \t %.4f \t %.4f" % (lp_a6_2[1][1], lp_a6_2[1][2], lp_a6_2[1][3], lp_a6_2[1][4]))
    print("%.4f \t %.4f \t %.4f \t %.4f" % (lp_a6_3[1][1], lp_a6_3[1][2], lp_a6_3[1][3], lp_a6_3[1][4]))
    print("\n")
    
    print("%.4f \t %.4f \t %.4f \t %.4f" % (lp_a6_1[2][1], lp_a6_1[2][2], lp_a6_1[2][3], lp_a6_1[2][4]))
    print("%.4f \t %.4f \t %.4f \t %.4f" % (lp_a6_2[2][1], lp_a6_2[2][2], lp_a6_2[2][3], lp_a6_2[2][4]))
    print("%.4f \t %.4f \t %.4f \t %.4f" % (lp_a6_3[2][1], lp_a6_3[2][2], lp_a6_3[2][3], lp_a6_3[2][4]))
    print("\n")
    
    print("%.4f \t %.4f \t %.4f \t %.4f" % (lp_a6_1[3][1], lp_a6_1[3][2], lp_a6_1[3][3], lp_a6_1[3][4]))
    print("%.4f \t %.4f \t %.4f \t %.4f" % (lp_a6_2[3][1], lp_a6_2[3][2], lp_a6_2[3][3], lp_a6_2[3][4]))
    print("%.4f \t %.4f \t %.4f \t %.4f" % (lp_a6_3[3][1], lp_a6_3[3][2], lp_a6_3[3][3], lp_a6_3[3][4]))
    print("\n")
  
    print("%.4f \t %.4f \t %.4f \t %.4f" % (lp_a6_1[4][1], lp_a6_1[4][2], lp_a6_1[4][3], lp_a6_1[4][4]))
    print("%.4f \t %.4f \t %.4f \t %.4f" % (lp_a6_2[4][1], lp_a6_2[4][2], lp_a6_2[4][3], lp_a6_2[4][4]))
    print("%.4f \t %.4f \t %.4f \t %.4f" % (lp_a6_3[4][1], lp_a6_3[4][2], lp_a6_3[4][3], lp_a6_3[4][4]))
    print("\n")
 
    print("%.4f \t %.4f \t %.4f \t %.4f" % (lp_a6_1[5][1], lp_a6_1[5][2], lp_a6_1[5][3], lp_a6_1[5][4]))
    print("%.4f \t %.4f \t %.4f \t %.4f" % (lp_a6_2[5][1], lp_a6_2[5][2], lp_a6_2[5][3], lp_a6_2[5][4]))
    print("%.4f \t %.4f \t %.4f \t %.4f" % (lp_a6_3[5][1], lp_a6_3[5][2], lp_a6_3[5][3], lp_a6_3[5][4]))
    print("\n")

accuracy = acc / (num_testing_rows)
if(Q == 0):
    precision = 0
else:
    precision = accuracy_counter / Q
if(a6_test_freq[3] == 0):
    recall = 0
else:
    recall = accuracy_counter / (a6_test_freq[3])

print("Accuracy = %.4f \t Precision = %.4f \t Recall = %.4f" % (accuracy, precision, recall))

        
        
        
    
    
    

    
