npm init
npm install --save mongoose


////////////if like hw07
app.get('/',function(req,res) {
  res.sendFile('index.html');
});

//////////////HW06 is req.query for filtering, using exec, ex:
	if(req.query.semester === undefined || req.query.semester === '' || ((req.query.semester) === 'All' && (req.query.year === '') && (req.query.professor === '') ) ) {
		Review.find(function(err, reviewsObj) { ////req.query.nameOfFormSubmission
			res.render('reviews', {reviewsObj : reviewsObj});
		});
	}
	else if (req.query) {
		if(req.query.semester === 'All') {
			if(req.query.year === '') {
				const filtered = Review.find({ professor: req.query.professor});
				filtered.exec(function(err, reviewsObj) {
					res.render('reviews', {reviewsObj : reviewsObj});
				});
			}




//path info 
/*
__dirname === the path of the currently running file
//const path = require("path");
//const publicPath = path.resolve('./public', "public");
//const publicDir = path.join(__dirname, 'public');
https://www.hostingadvice.com/how-to/nodejs__dirname/
*/


//working with json files
const headerArr = dataObj.resultSets[0].headers;

const json = JSON.parse(data);
const letter = json.playerLetter; //string
if('computer' in json)

//reading files
const fs = require('fs');
fs.readFile(fileName, 'utf-8', function read(err, data)
fs.readFile(process.argv[2], 'utf8', function(err, data) {

//function names, comma after each
module.exports = { 
	repeat:repeat,
	getValidMoves: getValidMoves,
};
//then in the other file:
const rev = require('./reversi.js');
rev.repeat(appropriate, args, here)

//copy an array board into array arr
let arr = [...board];

//forEach
const data = JSON.parse(jsonData);
data.images.forEach(image => {
	allData.push(new Image(image.url, image.name.split('-')));
});

//reduce
//https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/reduce
function teamRebounds(city, data) {
	const rebounds = (data.reduce((previous, current) => {
		if(current["TEAM_CITY"] === city) {
			return previous + current.REB;
		}
		else {
			return previous;
		}
	}, 0));
	return rebounds;
}

//map
//https://www.w3schools.com/jsref/jsref_map.asp
const cities = data.map(function(player) {
	return player["TEAM_CITY"];
});

//filter --> returns a new array
//https://www.w3schools.com/jsref/jsref_filter.asp
function removeDuplicates(cities) {
	return cities.filter((a, b) => cities.indexOf(a) === b);
} //a is current value and b is index

//date object
//https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Date
let tempDate = new Date(tx[0].time);
	for(let i = 0; i < tx.length; i++) {
		let compare = new Date(tx[i].time);
		if((compare - tempDate) > 0) {
			tempDate = compare;
			tempTx = tx[i];
		}
	}


// check if a string has certain characters
algebraicNotation is a string
const pattern = new RegExp(/[~`@()!#$%&*+=\-\]\\';,/{}|\\":<> ]/);
pattern.test(algebraicNotation)