## -*- coding: utf-8 -*-

#downloaded in .csv format from following link
#https://data.cityofnewyork.us/Business/Legally-Operating-Businesses/w7w3-xahh/data


import csv
def cleanData():
    source_file = 'Legally_Operating_Businesses.csv'
    rowNum = 0
    try:
        in_file = open(source_file,'r')
    except:
        print("File not found or could not be opened.")
    else:
        reader = csv.reader(in_file, delimiter=',') 
        out_file_name = 'cleanedBusinesses.csv'
        out_file = open(out_file_name,'w')
        writer=csv.writer(out_file,delimiter=",")
        
    
        header = next(reader)
        #writer.writerow((header[0], header[1], header[2], header[3], header[4], header[5],header[6], header[7],header[11],header[12],header[13],header[15]))
        
        
        for field in reader:

            for word in field:
                if(word == ''):
                    word = 'null'
                    
            if(field[6] == ''):
                continue

                
            #edit 5
            #only write meaningful and relevant columns
            writer.writerow( (field[0], field[1], field[2], field[3],field[4], field[5],field[6], field[7],field[11],field[12],field[13],field[15]) )

            rowNum+=1
            
            
        out_file.close()
        in_file.close()
cleanData()
"""
Spyder Editor

This is a temporary script file.
"""

