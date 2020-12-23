#1. query to count how many records there are in your table
SELECT COUNT(*) FROM businesses;

#2. query to list the first 10 records in your table based on a sort in a reverse order
# sorted by descending license expiration date
SELECT * FROM businesses ORDER BY License_Expiration DESC LIMIT 10;


#3. Display three (did 4) important fields; at least one should be in alphabetical order; 
#show only the first 10 records of an appropriate selection using WHERE
SELECT License_Type, Business_Name, Industry, Address_City FROM businesses 
WHERE Address_City = 'New York' 
ORDER BY Industry 
LIMIT 10;

#4. use the COUNT function
####this produces an extremely long output (sorry!)
####this output highlights a lot of the problems with this dataset 
SELECT Address_City, COUNT(*) FROM businesses 
GROUP BY Address_City 
ORDER BY Address_City ASC; 

#5. write a query using HAVING
SELECT DISTINCT Address_State , COUNT(Address_State) as c FROM businesses
GROUP BY Address_State
HAVING c > 1 
ORDER BY Address_State ASC;

#6. user-friendly listing of the first 15 records in alphabetical order by creating a text field using concatenation
#note --> all of these businesses start with '#1' and there are some repeats
SELECT Business_Name, (DCA_License_Number || ":" || " " || Industry) 
FROM businesses
ORDER BY Business_Name 
LIMIT 15;

###########REDO
#7 use functions we have not used in class
# I use the date() function
# I know this isn't the most efficient way to answer this question about the data
# Just did it to use a function --> coudln't use a lot because all of the data here is text
SELECT DISTINCT Business_Name, License_Creation, date(License_Creation) as l
FROM businesses
ORDER BY l ASC
LIMIT 10;

#8 use functions we have not used in class
# I use the length() function to identify zip codes that are most likely incorrect 
# or need further investigation, at least
SELECT DISTINCT Address_ZIP, length(Address_ZIP) as l
FROM businesses
WHERE l < 5
ORDER BY l ASC;

#9. How many active operating businesses are there currently that were licensed 
# after 12/31/2017
SELECT COUNT(*) from businesses 
WHERE License_Status = 'Active'
AND License_Creation > '12/31/2017';

#10. How many active businesses are in NJ for each distinct Industry 
#(that is covered in the data set, at least)
SELECT DISTINCT Industry, COUNT(Industry) as c
FROM businesses 
WHERE Address_State = 'NJ'
AND License_Status = 'Active'
GROUP BY Industry
ORDER BY c DESC;

#11. What are the 20 longest operating and currently active businesses in the dataset?
SELECT * FROM businesses
WHERE License_Status = 'Active'
ORDER BY License_Creation ASC
LIMIT 20;


#12
SELECT DISTINCT Address_Borough, COUNT(Address_Borough) as c
FROM businesses
GROUP BY Address_Borough
HAVING c > 0;
