express <-- built on top of http module
http module <-- create http servers and clients
net module <-- tcp/ip stuff... connect to some host ... create tcp/ip servers and clients
node <-- js server side networking framework
v8 engine <-- js engine for chrome


* serving static files was lacking in features
	* serving static files required the addition of a check for a specific path
	* manually setting content type (for images)
* dealing w/ http at low level (no req and res objects)
	* manual parsing of http request, manual creation of http response
* routing was primitive
	* a large conditional / switch case not really scalable
	* web server and web app intertwined... changing a route required working in web server code
* no templating
	* only static html / handcoded strings were possible
* middleware - functions that are called before the route handling functions are called
	* ... these have functions have access to the request and potential response
	* they can manipulate the request and response prior to hitting the actual route handling functions
	* they can circumvent route handlers to send back a response immediately
	* a generic way of adding additional functionality that works off of request and response
	* authentication, logging, serving static files
* authentication
* logging
* persistent data storage - database, just files on the fs, "the cloud" (firebase, s3, etc.)









