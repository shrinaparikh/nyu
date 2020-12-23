import sqlite3
conn = sqlite3.connect('example.db') #same as sqlite3 example.db in terminal

.execute 

'''

STEPS
1. Python need to connect to SQLite and open a database
2. Drops the books table
3. create new books table
4. run INSERT queries

code uploaded already
'''

#the triple quote --> takes formatting of string 
#put SQLite code in '''
#c.execute('''sqlite instruction''') --> don't need ;

#do try,except,else for opening databases in case they don't exist
#SQLite queries are just strings to python



###for working with server
'''
first line says where python is 
import cgi 
which lets up use html in string vals

c.close
closes database 
