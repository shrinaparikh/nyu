/* CSCI-UA.60-1 - Class Worksheet */


/* Leading causes of death
SOURCE
https://catalog.data.gov/dataset/age-adjusted-death-rates-for-the-top-10-leading-causes-of-death-united-states-2013
*/


DROP TABLE IF EXISTS 'deaths';
CREATE TABLE IF NOT EXISTS 'deaths' (
	'Year'	TEXT,
	'Code_CauseName'	TEXT,
	'CauseName'	TEXT,
	'State'	TEXT,
	'Deaths'	INTEGER,
	'Age-adjustedDeathRate'	REAL
);

.mode csv
.import deathCauses.csv deaths