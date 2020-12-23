//classes

class EchoServer {
	constructor(name) {
		this.name = name;
		//this.server = net.createServer(this.handleConnect.bind(this));
		this.server = net.createServer((sock) => (this.handleConnect));
		//handleConnect is being called as a regular function here, so this is global
		//can fix this
		//use 'bind' --> one way to fix
		//can also use an array function
	}

	handleConnect(sock) {
		console.log('You have connected to,' this.name);
		//here, this.name is undefined
		//because the this here is the global this
		sock.on('data', (d) => handleData(d));
	}

	handleData(d) {
		console.log(d + ' ');
		sock.write(d);
	}

	start() {
		console.log(this.name, 'is listening on port 3000');
		this.server.listen(3000, '127.0.0.1');
	}
}

const es = new EchoServer('Joe\'s echo server');


/*
const net = require('net');
//create server will create new tcpip server
//func passed in will be called WHEN client connect
const server = net.createServer(function(sock)) {
	//socket object passed into callback function represents a connected client
	console.log(' client connected ');

	//it will call callback function when event 'data' occurs
	//'data' event means client sent us data
	sock.on('data', function(d)) {
		console.log(d);
		sock.write(`i recieved:  ${d}`); //backtick???
	});
}); //asynchronous i/o part




console.log('listening on port 3000');
server.listen(3000, '127.0.0.1');


*/