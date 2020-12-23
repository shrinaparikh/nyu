
import csv
def cleanData():
    source_file = 'Res.csv'
    rowNum = 0
    try:
        in_file = open(source_file,'r')
    except:
        print("File not found or could not be opened.")
    else:
        reader = csv.reader(in_file, delimiter=',') 
        out_file_name = 'res2.csv'
        out_file = open(out_file_name,'w')
        writer=csv.writer(out_file,delimiter=",")
        header = next(reader)
        writer.writerow((header[0], header[1], header[2], "ADDRESS", header[7], header[8],header[10], header[11],header[12],header[13],header[14],header[15], header[17]))
        for line in reader:
            #edit 1 - get rid of rows we can't work with
            #eliminate rows where no violations were recorded
            if(line[9]) == "No violations were recorded at the time of this inspection.":
                continue
            #skips over data entries with missing score because we can't do anything meaningful without that data
            #some rows have a Z in them ... unsure why it was there, and can't find anything about a 'Z' health score online, so left it in there for now
            if((line[13] == '')):
                continue
            
            
            #edit 2
            #fill in some empty fields
            if(line[1] == ''):   
                line[1] = "Unknown"
            
            #edit 3
            #concatenate address into one column
            #reduces number of columns and makes it easier to access the information, which we would likely need altogether if we needed an address
            line[3] = line[3] + ' ' + line[4] + ', ' + line[5]
            
            #edit 4
            #fill in Grade column based on health rating score
            if(line[14] == ''):
                if (int(line[13]) <= 13):
                    line[14] = line[14] + "A"
                elif( (int(line[13])) < 27):
                    line[14] = line[14] + "B"
                else:
                    line[14] = line[14] + "C"
            
            #edit 5
            #only write meaningful and relevant columns
            writer.writerow( (line[0], line[1], line[2], line[3],line[7], line[8],line[10], line[11],line[12],line[13],line[14],line[15], line[17]))
            rowNum+=1
            
            #dataset is originally 401,106 rows
            #dataset after changes is 201,249 rows
            #only working with 4000 for the purposes of this assignment
            if(rowNum == 4000):
                break
            
        out_file.close()
        in_file.close()
cleanData()
