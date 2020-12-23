// review working with express
// lets say you installed express, hbs via npm

const express = require('express');
const path = require('path');
//TODO: directory serving
///resolve vs. join
const app = express();

app.use((req,res,next) => {
	console.log(req.method, req.path);
	next();
});

//this makes your app runnable from any directory 
//express.static's arg is "root directory" 
//this is the absolute path we get 
//if you wanted to do relative could just say publicDir = 'public'
const publicDir = path.join(__dirname, 'public');
//const publicDir =' public'
app.use(express.static('publicDir'));
//.use expects middleware func --> 3 required args
//function in () returns func

//templating system is handlebars
//hbs (but there are others)
//create a directory called views that contains templates and layout

// {{{body}}} --> drops in the contents of the actual template here
// does do without escaping special html characters

//when creating a form we have GET and POST
//use POST when you don't want data in url
//POST is like creating a new resource or adding data, or update data
//use GET if you want something to be bookmarkable
//GET - strictly reading data

//res.redirect --> so browser doesnt send another post request

//app.get returns app object
app.get('/', (req, res) => {
	res.send('this is the home page');
	//res.json
	//res.status ... and then .send
	// res.set ... set response headers
	//res.render
})

//forms --> another way of submitted a GET request

app.get('/numbers', (req,res) => {
	let results = numbers;
	if(req.query.n) {
		const results = numbers.filter(n => n > parseInt(req.query.n));

	}
	res.render('numbers', {numbers: results});
});


//path.resolve('..')

//if a file exists send back res w file as body
//if file doesn't exist... go to next middleware/route handler.. 404

//app object allows itself to be configured:
//app.set
//http "verbs" /methods as actual method names:
//app.get -GET
//app.post -POST

app.listen(3000);