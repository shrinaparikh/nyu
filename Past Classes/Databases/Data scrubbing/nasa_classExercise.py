# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

def file_prepare():
    print("Attmepting to open a file:")
    source_file = "nasa.txt" #or you can use an input function
    target_file = "nasa_out.txt"
    lines_read, lines_written = 0,0
    header_row_needed = True
    try:
        data_in = open(source_file,'r')
    except:
        print("File could not be found or opened")
    else:
        #file opened
        data_out = open(target_file, 'w')
        for line in data_in:
            lines_read += 1
            #now processing the data
            ##data = line
            if line[0:4].isdigit() or (line[:4]=="Year" and header_row_needed):
                if header_row_needed and line[:4]=="Year":
                    header_row_needed = False
                values = line.split()
                values = values[0:13]
                #print(values)
                #next we will check for asterisks in the indiv
                for i in range(len(values)):
                    if "*" in values[i]:
                        values[i] = "n/a"
                new_line = ",".join(values)
                if new_line[:4] != '2019':
                    data_out.write(new_line+"\n")
                    lines_written+=1

            #new_line = line
            #data_out.write(new_line)
            
            lines_written += 1
            
        data_in.close()
        data_out.close()
        print("Lines read: " +str(lines_read))
        print("Lines written: " +str(lines_written))
        #print(values)
file_prepare()