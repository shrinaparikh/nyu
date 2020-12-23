//express setup
const express = require('express');
const app = express();

//any other middleware goes here
app.use((req,res,next) => { //remember that it has access to req,res and you have to call next afterwards
	console.log("Method: ", req.method);
	console.log("Path: :", req.path);
	next();
});

app.get('/', (req, res) => {
  res.render('all', {sortedArr});
});

app.listen(3000);






//router is a mini app with methods named after HTTP verbs
const express = require('express')
const router = express.Router();
router.get('/bar/baz', function(req, res) { //calling get on the router object
  res.send('qux');
})
// two slides on actually using router: https://cs.nyu.edu/courses/spring20/CSCI-UA.0480-008/_site/slides/14/routers.html#/4
// routers cannot listen


//flexible paths, urls, and regular expressions
//https://cs.nyu.edu/courses/spring20/CSCI-UA.0480-008/_site/slides/14/params.html?print-pdf#/
//extracting values from paths: for values prefixed with : in url you can use req.params
'http://localhost:3000/some/other/parts/hello/world' // in the browser
router.get('/some/other/parts/:var1/:var2', function(req, res) {
	res.send(req.params.var1 + ', ' + req.params.var2);
});
//example to grab the two digits after class using the fact that req.params is an array
router.get(/class(\d\d)/, function(req, res) {
  res.send(req.params[0]);
});

router.get('/movie/:slug', function(req, res) {
	var slug = req.params.slug;
	Movie.findOne({slug:slug}, function(err, movie, count) {
		res.render('movie-detail.hbs', movie);
	});
});





//starter code for handlebars --> add a form and a loop
/*
<form method="POST" action="">
<div><label>Name</label> <input type="text" name="name"></div>
<div><label>Age</label> <input type="text" name="age"></div>
<input type="submit"></div>
</form>

{{#if err}}
<ul>
{{#each err.errors}}
<li>{{message}}</li>
{{/each}}
</ul>
{{/if}}
</form>
*/

/////////////////////////////////////////table example
/*
<!DOCTYPE html>
	<head> 
		<link rel = "stylesheet" type = "type/css" href = "/css/main.css">
	</head>
	<h3>
		My Reviews
	</h3>
	<body>	
		<table>
			<thead>
				<th colspan="1">Course Number</th>
				<th colspan="1"> Course Name</th>
				<th colspan="1"> semester</th>
				<th colspan="1"> year</th>
				<th colspan="1"> professor</th>
				<th colspan="1"> review</th>
			</thead>
			<tbody>
				{{#each reviews as |review|}}
					<tr>
						<td>{{review.courseNumber}}</td>
						<td>{{review.courseName}}</td>
						<td>{{review.semester}}</td>
						<td>{{review.year}}</td>
						<td>{{review.professor}}</td>
						<td>{{review.review}}</td>
					</tr>
				{{/each}}
			</tbody>
		</table>
			{{{ body }}}			
</body>
*/





////////////////////////////////////////////////////////////////
/* FORM

<!DOCTYPE html>
<title>Course Reviews!</title>
<head>
	<link rel="stylesheet" type="text/css" href="/css/main.css">
</div>
</head>

	<h3>Add A Review!</h3>

<div class = form>
<form method="POST" action="/reviews/add">

	<label for="courseNumber"> Course Number: </label>
	<input type = "text" id="courseNumber" name="courseNumber">
	<br>

	<label for="courseName"> Course Name: </label>
	<input type = "text" id="courseName" name="courseName">
	<br>

	  <label for="semester">Semester: </label>
	  <select id="semester" name="semester">
	    <option value="All">All</option>
	    <option value="Fall">Fall</option>
	    <option value="Spring">Spring</option>
	  </select>
	  <br>

	  <label for="year">	Year:</label>
		<input type="number" id="year" name="year">
		<br>

		  <label for="professor">	Professor:</label>
		<input type="text" id="professor" name="professor">
		<br>

		<label for="review"> Review: </label>
		<input type = "string" id="review" name="review">
		<br>

	<input type="submit" value = "Submit"><br><br>
	</form>
</div>

<body> 

{{{ body }}}

</body>
</html>

*/









////////////////// links, res.locals.count
/*
<body>
	<div class="nav">
        <a href="/">All Reviews</a>
        <a href="/reviews/add">Add Reviews</a>
        <a href="/reviews/mine">My Reviews</a>
    </div>

{{{ body }}}

</body>

    <div class = "counter">
        <h2>Your session's total page visits: 
        {{count}}</h2>
    </div>
*/










////////////////////////// table
/*
<!DOCTYPE html>
	<head> 
		<link rel = "stylesheet" type = "type/css" href = "/css/main.css">
	</head>
	<h3>
		All Reviews
	</h3>

	<div class = form>
	<form method="GET" action="/">
		  <label for="semester">Semester: </label>
		  <select id="semester" name="semester">
		    <option value="All">All</option>
		    <option value="Fall">Fall</option>
		    <option value="Spring">Spring</option>
		  </select>

		  <label for="year">	Year:</label>
  		<input type="number" id="year" name="year">
  		  <label for="professor">	Professor:</label>
  		<input type="text" id="professor" name="professor">
		<input type="submit" value = "Filter"><br><br>
		</form>
	</div>
	
	<body>	
		<table>
			<thead>
				<th colspan="1">Course Number</th>
				<th colspan="1"> Course Name</th>
				<th colspan="1"> semester</th>
				<th colspan="1"> year</th>
				<th colspan="1"> professor</th>
				<th colspan="1"> review</th>
			</thead>
			<tbody>
				{{#each reviewsObj as |review|}}
					<tr>
						<td>{{review.courseNumber}}</td>
						<td>{{review.courseName}}</td>
						<td>{{review.semester}}</td>
						<td>{{review.year}}</td>
						<td>{{review.professor}}</td>
						<td>{{review.review}}</td>
					</tr>
				{{/each}}
			</tbody>
		</table>
			{{{ body }}}			
</body>

*/


