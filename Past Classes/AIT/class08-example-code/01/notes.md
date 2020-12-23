v8 engine (js engine that powers chrome)
node
net module <-- for making tcp/ip servers / clients
http module <-- for making http servers / clients
express <-- built on top of http module, smooths over some of the lack of features
from http module

our web framework:

* mechanism for routing was not really scalable
	* doesn't deal with casing
	* doesn't handle trailing slashes well
	* doesn't deal with query strings
* routing was a cumbersome to add new routes (we had to go into existing code and modify it rather than bring in a module that exposed an api for adding routes)
	* there was no abstraction / encapsulation
* does not support "single page web application" - a web that allows for parts of a page to be updated (serving json, xml)
* templating - inject content into a template
* database (or "the cloud", such as firebase, etc.) persisting data
* authentication, authorization and users
* form handling
* middleware - generic system of adding things to do before request is processed and after request is processed (like authentication, logging, serving static files)















