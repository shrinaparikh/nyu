Python 3.6.4 (v3.6.4:d48ecebad5, Dec 18 2017, 21:07:28) 
[GCC 4.2.1 (Apple Inc. build 5666) (dot 3)] on darwin
Type "copyright", "credits" or "license()" for more information.
>>> WARNING: The version of Tcl/Tk (8.5.9) in use may be unstable.
Visit http://www.python.org/download/mac/tcltk/ for current information.
#NASA data
>>> 
>>> #NASA data
>>> # http://data.giss.nasa.gov/gistemp/tabledata_v3/SH.Ts+dSST.txt from NASA - http://data.giss.nasa.gov/
>>> #https://cs.nyu.edu/courses/spring20/CSCI-UA.0060-001/notes/dbw_readings_pythonDataScrubbing_sp20.html
>>> 
>>> #Data scrubbing
>>> # 1. remove the header
>>> # 2. remove the footer
>>> # 3. remove the blank rows
>>> # 4. remove the "year" column on the right side
>>> # 5. remove the annual mean columns and the seasons columns
>>> # 6. remove duplication columns with the year and the rows (except for the header first instance row)
>>> # 7. We will omit 2019 values due to the absence of the last 5 months of data
