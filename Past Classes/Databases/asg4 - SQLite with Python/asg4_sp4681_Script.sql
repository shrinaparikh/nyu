
DROP TABLE IF EXISTS businesses;
CREATE TABLE IF NOT EXISTS 'businesses' (
	DCA_License_Number	text,
	License_Type	text,
	License_Expiration Date,
	License_Status	text,
	License_Creation Date,
	Industry	text,
	Business_Name text,
	Business_Name2 text,
	Address_City text,
	Address_State text,
	Address_ZIP text,
	Address_Borough text
);


.mode csv
.import cleanedBusinesses.csv businesses