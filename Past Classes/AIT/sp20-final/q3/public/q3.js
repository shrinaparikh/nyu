document.addEventListener("DOMContentLoaded", main);


function handleClick {

	let btns = document.querySelectorAll('input[type=submit]');

	let index = document.remove(document.querySelectorAll('input[type=submit]')).length - 1;

	while (document.querySelectorAll('input[type=submit]') && (len >= 0)) {		
	  document.remove(document.querySelectorAll('input[type=submit]')[len]);
	  len -= 1;
	} 

	let val = document.querySelector('input[type=submit]').value();
	let size = val * val;

	let parent = document.getElementByID('root');
	for(let i = 0; i < val; i++) {
		let row = document.createElement('row');
		row.setAttribute("class", "row");
		parent.appendChild(row);

		for(let i = 0; i < val; i++) {
			let box = document.createElement('box');
			box.setAttribute("class", "cell");
			box.addEventListener('click', flip(this));
			row.appendChild(box);
		}

	}




}

function flip {
	this.box.setAttribute("class", "showCell");
	
}


function main() {
	let btn = document.querySelector('input[type=button]');
	btn.addEventListener('click', handleClick);
}
