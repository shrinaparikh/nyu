//sessions 
/*
checks requests for a cookie header, if none then it generates a session id
npm install express-session
app.use(express.urlencoded({ extended: false }));
req.session.ID and req.sessionID --> both are the same, read-only, the id for the session
*/
const session = require('express-session');
const sessionOptions = { 
  secret: 'secret for signing session id', //used to sign the cookie
  saveUninitialized: false, //keep false
  resave: false //keep false
}; 
app.use(session(sessionOptions));
app.use(function(req, res, next){
	if(req.session.count === undefined) {
		req.session.count = 0;
		res.locals.count = 0;
	}
	else {
		req.session.count += 1;
		res.locals.count = req.session.count;
	}
	next();
});

req.session.myName = req.body.firstName; //in app
//<h1>myName: {{myName}}</h1> // in hbs template

app.post('/reviews/add', function(req,res) {
	if(req.body.length !== 0) {
		new Review({ 
			courseNumber: req.body.courseNumber,
			courseName: req.body.courseName,
		}).save(function(err, review, count) { 
			req.session.reviews.push(review); //can use req.sessions anywhere
			res.redirect('/');
		});
	}
});

//cookies
/*
HTTP stateless but sometimes we want to keep state --> auth, sessions, cookies
session ids link to a particular client
can link session ids back to user information stored on the server --> mongoose/mongo
the secret to this session id is cookies
when your browser makes a request to the server, it sends this identifier and the server finds the session associated with it
*/
//in http response: Cookie-Header --> can specify name=value pairs sep by ;
// ex in an http response: Set-Cookie: foo=bar
//you can use res.set or res.append to set the Set-Cookie header
// https://cs.nyu.edu/courses/spring20/CSCI-UA.0480-008/_site/slides/10/sessions.html#/8
app.use((req, res, next) => {
  const cookieHeader = req.get('Cookie'); //this is session management to get the cookie header
  const parts = cookieHeader.split('; ');
  const cookiesObj = parts.reduce((cookies, nameValue) => { //first arg is object, second is object being worked with
    const [name, value] = nameValue.split('=');
    cookies[name] = value;
    return cookies;
  }, {}); //start with empty cookie object
  req.cookies = cookiesObj; //you can use res.set or res.append to set the Set-Cookie header
  //https://cs.nyu.edu/courses/spring20/CSCI-UA.0480-008/_site/slides/10/sessions.html#/13
  //next slide is about managing cookies on the client side
  res.append('Set-Cookie', 'MY_SESSION_ID=123; HttpOnly');
  res.append('Set-Cookie', 'color=#00ff00');
  console.log("The cookie header contains: ", cookiesObj);
  //console.log(req.session);
  next();
});