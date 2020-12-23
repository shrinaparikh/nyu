/*
browser response headers to set some cookies
Set-Cookie: foo=bar; httponly; secure
Set-Cookie: baz=qux
Set-Cookie: sessionid=123; httponly; secure

on every request:
Cookie: foo=bar; bar=qux
*/


const express = require('express');
const app = express();

const sessions = {}; //in memory session store... or use actual database
// express-session ... you can specify the session store u want
// {123: {name: 'joe', favColor: 'green'}}
// good scenario... if the session id is manipulated, then session is invalid because it doesn't exist
// the browser has to send a cookie with session=123

//use middleware so we don't have to do this in every route path
app.use((req,res,next) => {
	const cookieHeader = req.get('Cookie');
	const parts = cookieHeader.split(';');
	const cookiesObj = parts.reduce((cookies, nameValue) => {
		const [name,value] = nameValue.split('='); //gets name val pairs
		cookies[name] = value; //do parsing here
		return cookies;
	}, {})
	req.cookies = cookiesObj;
	next();
})

//this middleware will provie access to in memory session store based on session id sent via cookies
app.use((req,res,next) => {
	if(req.cookies.hasOwnProperty('sessionId')) {

	}else {
		//browser has not sent any cookies
		//or cookies sent does not have sessionId
		const sessionId = crypto.randomBytes(16).toString('base64');
		sessions[sessionId] = {}
		req.session = sessions[sessionId]
	}
	next();
})

app.get('/', (req,res) => {
	console.log(req.cookies);
	res.send();
})

app.get('/bake', (req,res) => {
	res.send('cookies header is' + cookieHeader);
	//res.set() //overwrites exisitng
	//res.append() // add headers of the same name
	res.append('Set-Cookie', 'foo=bar');
	res.append('Set-Cookie', 'session_id=123; httponly'); // use secure when over ssl
	//inspect --> application, network
	res.send('make u a cookie');
})
