const mongoose = require('mongoose');

const ArticleSchema = new mongoose.Schema({
  title: {type: String, required: true},
  author: {type:String, required:true},
  slug: {type:String, required: true}
});

mongoose.model('Article', ArticleSchema);
const Article = mongoose.model('Article');

// TODO: if you've enabled authentication, change the dsn here
// however, make sure to change it back to this when uploading
mongoose.connect('mongodb://localhost/sp20-ait');

const fs = require('fs');

function loadFile(fn) { //fn is a json file to read as a string


   fs.readFile(fn, 'utf-8', function read(err, data) {
   		json = JSON.parse(data);
   		//console.log(json);
   		let art = new Article({title: json.title, author: json.author, slug: json.slug});
   		//console.log(json.slug);
   		Article.find({slug: json.slug}, function(err, varToStoreResult, count) {
			//console.log(varToStoreResult);
			if(varToStoreResult.length !== 0) {
				art.save(function(err,review) {
   				if(err) {
   					console.log('ERROR READING: ', fn);
   				}
   				});
			}
			else {
				console.log('ARTICLE EXISTS: ',  Article.find({slug: json.slug}))
			}
		});
   	
   });


}

loadFile('article2.json');
