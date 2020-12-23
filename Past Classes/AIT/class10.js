app.use(express.urlencoded({extended: false}));


function loadAllTransactions(path, done) {
	//readDir gets you the list of files: fileList
	for(const name of fileList) {
		readFile(foo, (err,data) => {
			console.log(data);
			//guard condition --> check that the length of blocks is equal to length of fileList
			//our length of blocks is === length of fileList
			done(data); //called after done reading the files, but calls in multiple times
		})
	}
	done(data) //wrong to call done here --> called immediately after you start reading the files

}

const path = require('path');
app.use(express.static(path.static(path.join(__dirname, 'public'))));
//populates req.body
//req.query available by default w.out middleware
//holds query string parameters

app.set('view engine', 'hbs');
/*
//Use express to serve files that don't change (css, images, static html)
//in production --> static files are typically served from a different server or a "cdn"
app.get 
app.post
^^ use both for any dynamic generation of html
*/



loadAllTransactions('Transactions', (blocks) => {
	//work w blocks here
	console.log(blocks)
})


recursiveFunction(fileList, done) {
	if(base case) {call done}
		done()
	otherwise 
		recurse, call func again with either reduced fileList, check if index same length, etc whatever

}



const cats = [{name: "bill furry", lives: '9'}, {name: 'kitty purry', lives: '8'}];
//display all cats' names and lives as an unordered list on / (root)
app.get('/', (req,res) => {
	res.render('cats', {cats})
});


//on the same page, want filters by # lives
/*
<form method = "GET" action="">
	Min Lives: <input type = "number" name="minLives">
	<input type= "submit" value = "Filter!!!!">
</form>
<form method = "POST" action="">
	Name: <input type = "text" name = " name" >
	Lives: <input type = "number" name="Lives">
	<input type= "submit" value = "Create new Cat!!!!">
</form>
<ul>
{{#each cats as |c|}} OR {{#each cats}}
<li>{{c.name}} - {{c.lives}}<\li> AND {{this.name}}:{{this.lives}}
{{/each}}
</ul>
//pressing button creates another request
*/


req.query contains name val pairs in url
have it by default


app.get('/', (req, res) => {
	let result = cats;
	if(req.query.hasOwnProperty('minLives')) {
		cats.filter(cat => cat.lives >= parseInt(req.query.linLives));
	}
	res.render('cats', {cats: res})
})

app.post('/', (req,res) => {
	//probs validate
	//like remove html
	// make sure data types correct etc.
	cats.push({name: req.body.name, lives: req.body.lives});
	res.redirect('/'); //why did we need to redirect?
})

//initial response to get form
GET /HTTP/1.1
(headers here)

response from the server
HTTP/1.1 200 OK
(headers)

<!DOCTYPE ... all the form>

//pushing submit button cat creation
POST / HTTP/1.1
(headers here)

name=Paw+Newman&lives=5

//response
HTTP/1.1 302 Temporary redirect
Location: /

//browser must make new request to /
GET / HTTP / 1.1
























