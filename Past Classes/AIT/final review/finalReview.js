//functions review: https://www.dofactory.com/tutorial/javascript-function-objects

////https://cs.nyu.edu/courses/spring20/CSCI-UA.0480-008/_site/examples/ajax-promises/public/js/main.js

//AJAX: for real time apps and webpages, background requests, server sends back data rather than an HTML document, async web apps
//stack: HTML/CSS,JS and DOM, JS and XMLHTTPREQUEST,server side apps, json
//XMLHttpRequest is analogous to request module, it allows browser based javascript
const req = new XMLHttpRequest();
req.open('GET', url, true); // (request method, url, async boolean t or f)
//can use event listener
req.addEventListener('load') { ... };
req.addEventListener('error') { ... };
//also has its own properties
req.onload = function() { ... };
req.onerror = function() { ... };
//use status to det if request was successful
if (req.status >= 200 && req.status < 400) {
	const messages = JSON.parse(req.responseText);
	messages.forEach(function(obj) {
		document.body.appendChild(
			document.createElement('div')).
			textContent = obj.message;
	});
}
req.responseText()
//always remember: 
//but event listeners must be set before calling send
req.send(); //optional argument is the data you want to send in your request body (unless you are POSTing data)
//handle rate limit ex: https://cs.nyu.edu/courses/spring20/CSCI-UA.0480-008/_site/slides/20/ajax.html#/42

//can use either: 
req.onload = function() { 
	console.log('content loaded!');
};

req.addEventListener('load') { 
	console.log('content loaded!');
};

//ex

function handleClick(evt) {
	var req = new XMLHttpRequest(),
		url = 'http://api.github.com/users/' + 
			document.getElementById('username').value + '/repos';

	req.open('GET', url, true);
	req.addEventListener('load', handleResponse);
	req.send();
}

function handleResponse() {
	if (this.status >= 200 && this.status < 400) {
		var div = document.getElementById('container'), 
			oldList = document.querySelector('#container ul'),
			ul = document.createElement('ul'),
			repos = JSON.parse(this.responseText);

		repos.forEach(function(obj) {
			ul.appendChild(document.createElement('li')).textContent = obj.name;
		});
		div.replaceChild(ul, oldList);
	}
}

//can set headers 
req.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded; charset=UTF-8');



////display page with one button, background request, get API at
document.getElementById(“submitButton”).addEventListener('click', function(evt) {
var url = 'http://localhost:3000/api/movies';
var req = new XMLHttpRequest();
req.open('GET', url, true);
req.addEventListener('load', function() {
if (req.status >= 200 && req.status < 400) {
var movies = JSON.parse(req.responseText);
movies.forEach(function(movie) {
var p = document.body.appendChild(document.createElement('p'));
p.textContent = movie.title + '-' + movie.year;
});
}
});
 req.send();
});










































///creating your own API
res.json()


const Message = new mongoose.Schema({
	message: String,
	dateSent: Date
});

var mongoose = require('mongoose');
var Message = mongoose.model('Message');
router.get('/api/messages', function(req, res) {
  Message.find({}, function(err, messages, count) {
    res.json(messages.map(function(ele) {
      return {
        'message': ele.message,
        'date': ele.dateSent
      }; 
    }));
  });
});

//need a base url: http://my.domain/api
//think of all the things you need to do, think of all url paths necessary

router.post('/api/messages/', function(req, res) {
  var message = new Message({
    text: req.body.message,
    dateSent: Date.now()
  });
  message.save(function(err, saved_message, count) {
    if (err) { return res.send(500, 'Error occurred: database error.'); }
    res.json({id:saved_message._id}); /////notice res.json here
  });
});

//using advanced filtering:
router.get('/api/messages', function(req, res) {
  console.log(req.query.lastRetrievalDate);

  var q = {};
  if (req.query.lastRetrievalDate) {
    q.dateSent = {$gt:new Date(req.query.lastRetrievalDate)};
    console.log(q);
  }

  Message.find(q).sort('dateSent').exec(function(err, messages, count) {
    console.log('messages:', messages);
    console.log('err:', err);
    res.json(messages.map(function(ele) {
      return {
        'message': ele.text,
        'date': ele.dateSent
      }; 
    }));
  });
});

///and then on the client side:
var lastRetrievalDate, 
    timer, 
    delay = 1000;

document.addEventListener("DOMContentLoaded", getMessages);
document.querySelector('input[type=button]').addEventListener("click", sendMessage);

function sendMessage() {
	var message = document.getElementById('message').value;
	console.log('sending message', message);
	var req= new XMLHttpRequest();
	req.open('POST', 'http://localhost:3000/api/messages/create', true);
	req.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded; charset=UTF-8');
	req.send('message=' + message);
	req.addEventListener('load', function(eve) {
    clearTimeout(timer);
		getMessages();
	});
}
function getMessages() {
	var req = new XMLHttpRequest(),

  url = 'http://localhost:3000/api/messages';

  console.log(lastRetrievalDate);
  if (lastRetrievalDate) {
    url += '?lastRetrievalDate=' + lastRetrievalDate;
  }
	req.open('GET', url, true);

	req.addEventListener('load', function() {
	  if (req.status >= 200 && req.status < 400){
	    data = JSON.parse(req.responseText);
	    messageList = document.getElementById('message-list');
	    data.forEach(function(msg) {
	      var div = messageList.appendChild(document.createElement('div'));
	      div.textContent = (new Date(msg.date)).toLocaleString() + ' - ' + msg.message;
	    });
	    console.log(data);
	    if(data.length >= 1) { 
	      lastRetrievalDate = data[data.length - 1].date;
	    }
	    timer = setTimeout(getMessages, delay);
	  } else {
	    console.log(req.status);
	  }
	});

	req.addEventListener('error', function() {
	  console.log('uh-oh... network error or cross domain request');
	});

	req.send();
}

































function main() {
    console.log('THE DOM IS RED E');
}
document.addEventListener('DOMContentLoaded', main);


function talksAbout(node, search) {
	if (node.nodeType === document.ELEMENT_NODE) {
		for (var i = 0; i < node.childNodes.length; i++) {
			if (talksAbout(node.childNodes[i], search)) {
				return true;
			}
		}
		return false
	} else if (node.nodeType === document.TEXT_NODE) {
		return node.nodeValue.indexOf(search) > -1 {
	}
}

//finding elements:
document.getElementById
node.getElementsByClassName //returns multiple nodes or document.getElements by for both
node.getElementsByTagName  //returns multiple nodes
document.querySelector
document.querySelectorAll
// we can change certain attributes simply by using assignment... for example, id, src, or href
document.getElementById('foo').id = 'bar';
// assuming we have an element_node, and we know its first child is a text element
node.firstChild.nodeValue = 'new text'
//ATTRIBUTES
//example of changing attribute
const images = document.getElementsByTagName('img');
for (let i=0; i < images.length; i++) {
	images[i].src = "http://foureyes.github.io/csci-ua.0480-fall2017-007/resources/img/disapproval.png";;
}
////
element.getAttribute(name) // to get back the value of an element's attributed
element.setAttribute(name, value) 
element.hasAttribute(name) 
//find and replace using regular expressions: https://cs.nyu.edu/courses/spring20/CSCI-UA.0480-008/_site/slides/17/attributes.html#/6
//data-* attribute
const paragraphs = document.getElementsByTagName('p');
for (let i = 0; i < paragraphs.length; i++) {
	if (paragraphs[i].hasAttribute('data-shout')) {
		paragraphs[i].textContent = paragraphs[i].textContent.replace(/\./g, '!!!!!');
	}
}
//modifying the DOM
.removeChild(childNodeToRemove) //returns the node removed
.appendChild(nodeToAppend) //puts node at end and returns the node
.insertBefore(nodeToInsert, beforeThisNode) //returns inserted node
.replaceChild(nodeToInsert, nodeToReplace)  // returns the replaced node
//example https://cs.nyu.edu/courses/spring20/CSCI-UA.0480-008/_site/slides/18/modifying-creating.html#/2
//use a while loop to remove elements
while (div.firstChild) {
  div.removeChild(div.firstChild);
} //because if you do it this way:
for(let i = 0; i < p.length; i++) {
	div.removeChild(p[i]);
} //there is an element left over since you are removing from a live data structure

//reading and modifying a node's content
console.log(node.firstChild.nodeValue);
node.firstChild.nodeValue = 'new text';
// textContent - the text content of the node and all of its descendants (!)
const text = element.textContent; 
element.textContent = "this is some sample text";
//properties similar to textContent: innerHTML, innerText

//nodevalue and textcontent reference: https://cs.nyu.edu/courses/spring20/CSCI-UA.0480-008/_site/code/class19.html
//https://cs.nyu.edu/courses/spring20/CSCI-UA.0480-008/_site/slides/18/modifying-creating.html#/6
document.body.textContent
document.body.innerHTML
document.body.nodeValue
const p = document.getElementsByTagName('p')[0]
p.firstChild.nodeValue
p.firstChild.nodeValue = 'Surprised?'
p.textContent = 'Maybe not.'

//creating nodes
document.createTextNode(text)
document.createElement(elementName)
//replacement example https://cs.nyu.edu/courses/spring20/CSCI-UA.0480-008/_site/slides/18/modifying-creating.html?print-pdf#/
const div = document.getElementById('content');
const p = div.getElementsByTagName('p');

for(let i = p.length - 1; i >= 0; i--) {
	div.replaceChild( 
		document.createTextNode("this was a paragraph"),
		p[i]);
}

//example with replacing every p tag with a header tag
const div = document.getElementById('content');
const p = div.getElementsByTagName('p');

for(let i = p.length - 1; i >= 0; i--) {
	const header = document.createElement("h1");
	const content = document.createTextNode(p[i].textContent);
	header.appendChild(content);
	div.replaceChild(header, p[i]);
}

//function to add an element and an arbitrary number of child elements
function elt(type) {
	const ele = document.createElement(type);
	// start at 1 or else we'll get the type argument!
	for (let i = 1; i < arguments.length; i++) {
		let child = arguments[i];
		if (typeof child === "string") {
			child = document.createTextNode(child);
		}
		ele.appendChild(child);
	}
	return ele;
}
const ul = elt('ul', elt('li', 'item one'), elt('li', 'item two'));
document.body.appendChild(ul);

//instead of document.getElementById, you can also use querySelector to select elements by their CSS selector
document.querySelector('selector') //returns a single matching element
document.querySelectorAll('selector') //returns a list of all the matching elements

//every DOM element has an eventListener property
document.addEventListener
document.body.addEventListener
document.getElementsByTagName('div')[0].addEventListener
//ex:
const b = document.querySelector('button');
b.addEventListener('click', sayHello); //we use 'click' or 'DOMContentLoaded'
//this within the callback is the object the event is called on

//ex: make all paragraphs clickable, show x and y position, other properties an object might have are target and key
//https://cs.nyu.edu/courses/spring20/CSCI-UA.0480-008/_site/slides/19/events.html#/10
function handleClick(event) {
	this.textContent = event.x + ',' + event.y;
	console.log(evt.x, evt.y, evt.which);
	this.removeEventListener('click', sayHello); //get rid of it after first time clicked
}
const paragraphs = document.querySelectorAll('p');
paragraphs.forEach((p) => {
	p[i].addEventListener('click', handleClick);
});

//bubbling and propogation
/*
<article>
  <h1>About Events</h1>
  <button>Click to Say Hello</button>
</article>
*/
// in js
	const a = document.querySelector('article');  
	const b = document.querySelector('button');
	a.addEventListener('click', function(evt) {
	  console.log('article!');  
	});
	b.addEventListener('click', function(evt) {
	  console.log('button!');
	});
// modify your previous button event listener
b.addEventListener('click', function(evt) {
  console.log('button!');
  // the event won't bubble up!
  evt.stopPropagation();
});

//default action of a submit button: get or post request, or go to link
evt.preventDefault() 


/////hw07
function createReset() {
	const reset = document.createElement("BUTTON");
	reset.innerHTML = "RESET";
	reset.setAttribute("id", "reset");
	document.body.appendChild(reset);
}















































 










































































