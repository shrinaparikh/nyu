# Using the csv module to work with data files in python
import csv
def nasa_data3():
    source_file = 'nasa.txt'
    lines_written = 0
    try:
        in_file = open(source_file,'r')
    except:
        print("File not found or could not be opened.")
    else:
        reader=csv.reader(in_file,delimiter=' ',skipinitialspace=True) #skipinitialspace -> when true, white space immediately following the delimiter is ignored
        out_file_name = 'nasa_out_using_csv_module.csv'
        out_file      = open(out_file_name,'w')
        writer=csv.writer(out_file,delimiter=",")
        for line in reader:
            if len(line)>0:
                writer.writerow(line)
                lines_written+=1
        out_file.close()
        in_file.close()
        print("Lines written: ",lines_written)
nasa_data3()