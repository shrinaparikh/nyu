import urllib.request
def nasa_data2():
    url = 'http://i6.cims.nyu.edu/~de32/dbw_class/nasa.txt'
    lines_read,lines_written=0,0 
    try:
        response=urllib.request.urlopen(url)
    except Exception as e:
        print("Error - your online resource is not currently accessible." )
        print(e)
    else:  # the web page is accessible
        data=response.read().decode('utf-8')
        # Next, open the target file
        target_file = 'nasa_out_using_urllib.txt'
        out_file = open(target_file,'w')
        dataset = data.split("\n")
        for line in dataset:
            lines_read +=1
            out_file.write(line+"\n")
            lines_written +=1
        out_file.close()
        print("Lines read: ", lines_read)
        print("Lines written: ",lines_written)
    
nasa_data2()

