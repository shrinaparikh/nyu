//built up to an echo server[???]

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



////nc localhost 3000