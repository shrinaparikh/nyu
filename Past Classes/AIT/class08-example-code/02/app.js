// application object
//
// * configuring your app
// * adding middleware - adding funtions to be called before / 
//   after your routes
// * adding routes - mappings from paths as strings (as well as
//   request method) to functions ... work with request and
//   response objects
// * bind to a certain port (analogous to listen in net module)
//
// request
//
// * http request
// * path, method, ipaddress, headers, get
// * nice interface to http request
//
// response 
//
// * send a body, send a file, set the status code
// * send, status, set, sendFile
//
// gives back a function...
const express = require('express');
const path = require('path');

const app = express();

// app.set ...wil configure application
// use hbs as our templating system
app.set('view engine', 'hbs');

// hbs requires a "views" folder
// layout.hbs <--- all of the surrounding markup for your templates


// middleware can be added using app.use
// middleware is just a function that can take a request
// response object... and a next function to call
// middleware gets called before / after your routes

// express.static returns middleware function
const staticPath = path.resolve(__dirname, 'public');
app.use(express.static(staticPath));


// it adds a route for GET requests
// 1st arg is the path that we want to handle
// 2nd arg is our route handling function (callback)
// callback(requestObject, responseObject)
// only thing that callback should do is
// ...send back a response (res.send, res.end, res.sendFile)
// this callback is invoked when a request comes in and matches
// the path of our route handler... it's invoked with a request
// and response object, request representing the actual req 
// from the client, whereas response is our potential response
app.get('/harry', (req, res) => {
  // by default determine type based on argument
  // a string ... text/html
  // an object ... application/json
  // ... also implicitly sets status code to 200 OK
  // res.send('<h1>harry potter</h1>');
  // render will take template and put prop names / values from
  // second argument into template variables (based on prop name)
  // keys - variables names
  // values - the values to sub in
  res.render('harry', {character: 'harry', greeting:'HELLO!!!'});
});

app.get('/mickey', (req, res) => {
  // you can overwrite content type
  // res.set('Content-Type', 'text/plain');
  // res.set is used to set any response header
  res.set('X-Foo', 'Bar');
  res.status(200).send('<em>a mouse!</em>')
});


app.get('/dipper', (req, res) => {
  res.send('<h1>dipper</h1><img src="/img/dipper.gif">');
})

app.listen(3000);








