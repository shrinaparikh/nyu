

//using client side js, script tag in html
// <script src="main.js"> </script> --> this is the html to link, HW08 index.html
// We'll generally include JavaScript at the bottom of the body tag
//script tags in html can have attributes async and defer
// <script defer async src="main.js"> </script>
// an async attribute which signals to the browser that the script does not have to be blocking; it can be downloaded asynchronously
// a defer attribute - tells the browser that the script can be downloaded and run after the page has been parsed



//// CSS
// https://cs.nyu.edu/courses/spring20/CSCI-UA.0480-008/_site/slides/19/layout-style.html#/5
/*
CSS selectors: h3, h6, etc. ... a rule is the entire block 
display: 
	block: start on a new line and stretch as far as they can horizontally, ex: div, p , h1,
			elements appear stacked on each other
	inline: stay on the same line, no height or width, ex: span, a, em
			element appear adjacent to one another
	none: will not appear and looks like it is not there, ex: script, style, title
	inline-block: has a width and height but flows around surrounding content inline, no new line
					element appear adjacent to one another
	table
	table-cell
	table-row
visibility: none; --> hides an element but leaves a space
position: 
	static: no positioning, default
	relative: to where it would normally be places, top left bottom right
	absolute:
	sticky:
	fixed:
*/
//example of access CSS through javascript
#content {
	border:1px solid #000;
	position: relative;
	top: 50px;
}
//use an element's style property
var c = document.getElementById('content')
c.style.display = 'relative';
c.style.top = '150px';
myelement.style.backgroundColor = '#797';
myelement.style.color = '#a20';

//add or remove a class to an element in JS
myelement.classList.add('baz');
myelement.classList.remove('foo');
ele.classList.toggle('someClassName') //adds if not there, removes if it is


//https://cs.nyu.edu/courses/spring20/CSCI-UA.0480-008/_site/slides/19/css.html?print-pdf#/
//examples for css header formatting, nav formatted on right corner of header, right aligned sidebar
//sizing: em, rem, px
//class -> 1 to many but id should be unique 
// use # for ids and . for classes with css selectors
//you can use tagName.classValue & tagName#idvalue 
// can have mult selectors, ex: div, p, body {}
// can use relationships in selectors (ex: A E , A > E, E:first-child, B + E)
// a:hover








