# NASA data - class exercise
# Data source: (downloaded 01/30/2020)
# NASA Land-Ocean Temperature Index in 0.01 degrees Celsius s 1880-2013 - 
# http://data.giss.nasa.gov/gistemp/tabledata_v3/SH.Ts+dSST.txt
# from NASA - http://data.giss.nasa.gov/
##
# Data scrubbing / modifications required as follows:
# 1. remove the header
# 2. remove the footer
# 3. remove the blank rows
# 4. remove the "year" column on the right (duplicate column)
# 5. remove the annual mean columns
# 6. remove the season columns
# 7. keep only the first instance of the header record ("Year Jan Feb ... ")
# 8. omit 2019 values due to absence of the last five months of data
#
# Steps
# 1. open the data file and read the contents
#    - open a target file and set it up for writing
# 2. store the contents as a list line by line for processing
# 3.    -- for each line, check to see if it should be included
#          in the output file (look for a year at the left)
#       -- keep the leftmost 13 columns
#       -- write corrected data to the output file
# 4. close both the input and the output files
def file_prepare():
    print("Attempting to open file:")
    source_file = "nasa.txt" # or you could use an input function here
    target_file = "nasa_out.csv"
    lines_read,lines_written = 0,0
    header_row_needed = True
    try: 
        data_in = open(source_file,'r')        
    except:
        print("The file could not be found or could not be opened.")
    else:   
        # the file opened like a charm!
        print("File opened successfully.")
        data_out = open(target_file,'w')
        for line in data_in:
            lines_read +=1
            # processing the data will happen here:
            if line[0:4].isdigit() or (line[:4]=="Year" and header_row_needed): #here [0:4] is getting a substring
                if header_row_needed and line[:4]=="Year":
                    header_row_needed = False
                values = line.split()
                values = values[0:13] #here [0:13] is getting a subarray
                # Next we will check for asterisks in the individual values.
                # This is to make sure there are no asterisks
                # outside of 2019 and to step through this for class.
                for i in range(len(values)):
                    if "*" in values[i]:
                        values[i] = "n/a"
                new_line = ",".join(values)  
                # We decided to exclude 2019.
                if new_line[:4] != '2019':
                    data_out.write(new_line+"\n")
                    lines_written+=1
        data_in.close()
        data_out.close()
        print("Lines read: "+str(lines_read))
        print("Lines written: "+str(lines_written))  
file_prepare()