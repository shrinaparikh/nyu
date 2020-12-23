print("This is the url the data was downloaded from: \n" 'https://data.cityofnewyork.us/Business/Legally-Operating-Businesses/w7w3-xahh/data\n')

print("The dataset contains information about legally operating active and inactive businesses in New York City." +
	"Each row includes data about a different license document.\n") #description of the data
print("The data is available for free online courtesy of NYC Open Data. It is published by New York City agencies and partners.\n") #description of the source
print("The data is important as it tells us about the prominence of different types of businesses requiring licenses in NYC." +
	"Data of this nature is useful for many fields and entities. For example, it is useful in understanding the city's economy.\n") #important of the data
print("From this data, we can derive interesting information. For example, we can observe the growth and decline of various industries over the years." +
	"We may also learn about where people doing business in NYC are coming from.") #examples of what the user can learn from the data

import sqlite3
def sqlite3_report():

	#connect to database
	conn = sqlite3.connect('businesses.db')
	c = conn.cursor()

	print("\n")
	#option to offer a reasonable selection from the data or display all of it
	selection = input("Do you want to see all of the data or a selection of it? Please enter A for all and S for a selection. \n")
	if(selection == "A" or selection == "a"):
		query = "SELECT * FROM businesses "
	elif(selection == "S" or selection == "s"):
		print("You can choose to see only active or only inactive licenses.")
		selection = input("Please enter A for active and I for inactive: \n")
		if(selection == "A" or selection == "a"):
			query = "SELECT * FROM businesses WHERE License_Status = 'Active' "
		elif(selection == "I" or selection == "i"):
			query = "SELECT * FROM businesses WHERE License_Status = 'Inactive' "
		else:
			print("Invalid input")
			query = "SELECT * FROM businesses "
	else:
		print("Invalid input")
		query = "SELECT * FROM businesses "

	#user can choose if they want the order sorted
	#can sort numerically by license number
	#can also sort alphabetically by name
	print("\n")
	order = input("Do you want to sort the order? Please enter Y for yes and N for no. \n")
	if(order == "Y" or order == "y"):
		order = input("What would you like to sort by, Business Name or License Number? " +
			"Enter B for Business Name or N for License Number\n")
		if(order == "B" or order == "b"):
			order = "Business_Name"
		elif(order == "N" or order == "n"):
			order = "DCA_License_Number"
		else:
			print("Invalid input")
		
		query = query + "ORDER BY " + order

	elif(order == "N" or order == "n"):
		print("Cool")	
	else:
		print("Invalid input")

	#The result can but ordered in an ascending or descending manner
	print("\n")
	orderMethod = input("Do you want to specify an ascending or descending order?\n" +
		"Please enter Y for yes and N for no.\n" +
		"If you chose not to sort the data, please respond with a N.\n")
	if(orderMethod == "Y" or orderMethod == "y"):
		orderMethod = input("Enter A to sort by ascending or D to sort by descending\n")
		if(orderMethod == "A" or orderMethod == "a"):
			orderMethod = " ASC"
		elif(orderMethod == "D" or orderMethod == "d"):
			orderMethod = " DESC"
		else:
			print("Invalid input")

		query = query + orderMethod
	elif(orderMethod == "N" or orderMethod == "n"):
		print("Cool")
	else:
		print("Invalid input")


	#limit number of results shown
	print("\n")
	limit = input("Do you want to limit the amount of results shown? There are over 200,000 rows. Please limit.\n" +
		"Enter Y for yes and N for no\n")
	if(limit == "Y" or limit == "y"):
		limitNum = input("How many results do you want to show?\n")
		query = query + " LIMIT " + limitNum
	elif(limit == "N" or limit == "n"):
		print("Cool")
	else:
		print("Invalid Input")



	print(query)

	c.execute(query)
	rows = c.fetchall()

	#attempted efficient formatting
	for DCA_License_Number, License_Type, License_Expiration, License_Status, License_Creation, Industry, Business_Name,Business_Name2, Address_City, Address_State, Address_ZIP, Address_Borough in rows:
		print('{:15} {:15} {:15} {:15} {:15} {:15} {:25} {:10} {:20} {:10} {:15} {:15}'.format(DCA_License_Number, License_Type, License_Expiration, License_Status, License_Creation, Industry, Business_Name,
				Business_Name2, Address_City, Address_State, Address_ZIP, Address_Borough))
	#print(rows)
	c.close()

sqlite3_report()



