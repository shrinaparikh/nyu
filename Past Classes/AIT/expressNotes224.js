const express = require('express');
const app = express();
//adding routes to your application
function logger(req,res,next) {
	console.log(req.method + ' ' + req.path);
	next();
}

app.set('view engine', 'hbs');

//////static file serving middleware
app.use(express.static('/tmp/foo'));

app.use((req,res,next) => {
	res.send('done');
	next();
});

//called for every path, can register multiple funcs
app.use((req,res,next) => {
	console.log('hello');
	next();
})
app.get('/', (req,res) => {
	//formulate your response here
	//you can use res.send
	//it'll take arg that you pass it and send back the approp http res w/ arg as the body
	//send will change content type based on object passed in:
	//string --> text/html
	//object --> application/json
	res.send('<h1>This is the dune fanfic site</h1>')
	//think of call to send as call to sock.write and sock.end
});
app.get('/error', (req,res) => {
	//if you don't give back a response with something like send, or render, or sendFile, no response is sent back
	//res.status gives back same response object you called it on so you can chain like this vv
	res.status(400).send('generic client error');
	//just sets status of the response, can chain a send
});
/*
app.get('/sting.jpg',(req,res) => {
	res.sendFile('/tmp/dune.jpg');
	// res.json -- explicitly send back json string ... putting in obj serializes
	// res.set(header name, header value)
	// res.append
	// res.type ... set content type explicitly
});
*/

app.get('/about', (req,res) => {
	//it looks up template
	//drops in values for those template variables w/ in template
	res.render('about', {});
	//leave off extension
});

app.get('/worms', (req,res) => {
	//props will be used as variable names w/in template
	/*
	const data = {
		name1: 'wallace',
		name2: 'lowly'
	}
	*/
	const data = {
		names: ['wallace','lowly'];
	}
	res.render('worms',data);
})


///objects


app.listen(3000);



//install express