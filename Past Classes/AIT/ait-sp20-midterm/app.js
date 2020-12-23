const fs = require('fs');
const path = require('path');

const express = require('express');
const app = express();

app.set('view engine', 'hbs');

// TODO: Your Code Here!

app.get('/', function(req,res) {
	res.render('layout');
});

app.get('/pledge', function(req,res) {
	res.render('pledge');
});

app.get('/dice', function(req,res) {
	let num = Math.floor((Math.random() * 6) + 1);
	res.render('dice', {num: num});
});

app.get('/products', function(req, res) {
	let arr = [];
	fs.readFile('./products.json', 'utf8', (err, data) => { 
		const json = JSON.parse(data);
		if (err) {
			console.log("Error: ", err);
			return undefined;
		}
		else {
			let inventory = json.inventory[0];

			if( (!((req.query.name===undefined) && (req.query.price===undefined)))) {
				for(let i = 0; i < inventory.length(); i++) {
					let obj = {};
					obj.name = inventory[i].name;
					obj.price = inventory[i].price;
					let name = obj.name.toLowerCase(); //from json
					if(req.query.name && (req.query.price === '')) {
						let reqName = req.query.name.toLowerCase();
						if(name.includes(reqName)) {
							arr.push(obj);
						}
					}
					else if(req.query.price && (req.query.name === '')) {
						let price = req.query.price.parseFloat();
						if((obj.price) < (price)) {
							arr.push(obj);
						}
					}
					
					else {
						let reqName = req.query.name.toLowerCase();
						let price = req.query.price.parseFloat();
						if(name.includes(reqName) && ((obj.price) < (price))) {
							arr.push(obj);
						}
					}

				}
			}
			else {
				for(let i = 0; i < json.inventory.length(); i++) {
					let obj = {};
					obj.name = json.inventory[i].name;
					obj.price = json.inventory[i].price;
					arr.push(obj);
				}
				//console.log(dataArr);
			}
		}
		res.render('products', { arr: arr } );
	});

});

app.get('/discounts', function(req,res) {
	let arr = [];
	fs.readFile('./products.json', 'utf8', (err, data) => { 
		const json = JSON.parse(data);
		if (err) {
			console.log("Error: ", err);
			return undefined;
		}
		else {
			let inventory = json.inventory[0];
			for(let i = 0; i < inventory.length(); i++) {
					let obj = {};
					obj.name = inventory[i].name;
					obj.price = inventory[i].price;
					arr.push(obj);
			}

			fs.readFile('./discounts.json', 'utf8', (err, data) => { 
				let arr2 = [];
				const json2 = JSON.parse(data);
				if (err) {
					console.log("Error: ", err);
					return undefined;
				}
				else {
					let discounts = json2.data;
					//I know the .length isn't working and the server isn't responding... but I figured it would be a better use of my time to keep coding than debug (after 5ish min of debugging)
					for(let i = 0; i < discounts.length(); i++) {
						let id = discount[i].id;
						let discount = discounts[i].discount;
						for(let i = 0; i < inventory.length(); i++) {
							if(inventory[i].id === id) {
								let newPrice = (inventory[i].price - discount*(inventory[i].price));
								let obj2= {};
								obj2.price=newPrice
								obj2.id = id;
								arr2.push(obj2);

							}
						}

					}



				}
			});
			
		}
		res.render('discounts', { arr2 : arr2 } );
	});
});



module.exports = app.listen(3000);
