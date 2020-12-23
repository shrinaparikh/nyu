//mongodb, NoSQL --> document, json, a doc u basically a record with a bunch of key value pairs
//collection is a group of documents, aka schema in mongoose
//db.Person.insert({'first':'bob', 'last':'bob'})
//db.Person.update({'first':'foo'}, {$set: {'last':'bar'}})
//in mongoose terms: model is the constructor we use to create an object, which is a single document

//MONGOOSE Validation
//https://cs.nyu.edu/courses/spring20/CSCI-UA.0480-008/_site/slides/15/validation.html?print-pdf#/ 
//mongoose validates fields, for example it will not add a document if the schema specifies a number but that isn't entered. This wil be captured in the err object
const mongoose = require('mongoose');
const Cat = new mongoose.Schema({
	name: String,
	updated_at: Date,
	courseNumber: {type: String, required: true},
	courseName: {type: String, required: true},
});
mongoose.model('Cat', Cat); //register it
mongoose.connect('mongodb://localhost/catdb');
///or
mongoose.connect('mongodb://localhost/hw08', (err, database) => {
  if (err) {
    return console.log(err);
  } else {
    console.log('Connected to database'); 
  }
});




//in app.js
require( './db' ); 
const mongoose = require('mongoose');
const Cat = mongoose.model('Cat');

Cat.find(function(err, cats, count) { //what does count do? //or findOne
	res.render( 'cats', { cats: cats }); //in hbs can use {{#each cats}} <p>{{name}}</p>
});

///ex saving
app.post('/reviews/add', function(req,res) {
	//console.log(req.body);
	if(req.body.length !== 0) {
		new Review({ 
			courseNumber: req.body.courseNumber,
			courseName: req.body.courseName,
			semester: req.body.semester,
			year: req.body.year,
			professor: req.body.professor,
			review: req.body.review
		}).save(function(err, review) { 
			req.session.reviews.push(review);
			res.redirect('/');
		});
	}

});

SomeModel.find({search: criteria}, function(err, varToStoreResult, count) {
console.log(varToStoreResult); // <---- variable contains found documents!
});

//ex of finding and updating, using $push
Pizza.findOneAndUpdate({slug:'small-2'}, {$push: {toppings: {name:'peppers'}}}, function(err, pizza, count) {
	console.log(err, pizza, count);
});
Model.find({price: {$lt: 4}}) //same query operators
Message.find(q).sort('dateSent').exec(callback)
User.find({name: 'John'}).exec();

//you either use a callback or exec: https://stackoverflow.com/questions/31549857/mongoose-what-does-the-exec-function-do
Review.find(function() {
	res.render('myReviews', {reviews: req.session.reviews});
});

const filtered = Review.find({ year: parseInt(req.query.year)});
filtered.exec(function(err, reviewsObj) {
	res.render('reviews', {reviewsObj : reviewsObj});
});

Review.find(function() {
	res.render('add');
});









//inserting at command line
db.reviews.insert({ courseNumber: "CSCI-UA.0101", courseName: "Intro to CS", semester: "Fall", year: 2015, professor: "McTeacherson", review: "Now I can sort like pro!" });










//slugs --> human readable string unique for each document for all objects
//what is the difference between an object and document?
//ex: 
{
	size: 'medium',
	crust: 'thin',
	slug: 'medium-thin-2'
	toppings: [{name:'mushroom', extra:true}, {name:'peppers'}]
}
//but there is a plug in to do this for us:
npm install --save mongoose mongoose-url-slugs
const URLSlugs = require('mongoose-url-slugs'); //at beg of db.js

//example schema
const Topping = new mongoose.Schema({
	name: String,
	extra: {type: Boolean, default:false}
});

const Pizza = new mongoose.Schema({
	size: {type: String, enum: ['small', 'medium', 'large']},
	crust: String,
	toppings: [Topping] //this is a relationdhip defined by a document embed in another, toppings is an array of Topping objects
});

//finding by embedded document: https://cs.nyu.edu/courses/spring20/CSCI-UA.0480-008/_site/slides/12/mongoose.html#/17
//next slide is findind and updating modified documents

Pizza.plugin(URLSlugs('size crust')); //this should be before registering the model in app.js







///////////////////HW06

let dbconf;
if (process.env.NODE_ENV === 'PRODUCTION') {
 const fs = require('fs');
 const path = require('path');
 const fn = path.join(__dirname, '../config.json');
 const data = fs.readFileSync(fn);
 const conf = JSON.parse(data);    ///////////////////////use this if config.json contains the connection string
 //ex: {"dbconf":"mongodb://myTester:password@localhost/hw05"}
 dbconf = conf.dbconf;
} else {
 dbconf = 'mongodb://localhost/YOUR_DATABASE_NAME_HERE';
}

mongoose.connect(dbconf); //'mongodb://localhost/hw05'