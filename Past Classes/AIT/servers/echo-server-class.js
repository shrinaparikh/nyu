const net = require('net');

class EchoServer {
  constructor(name) {
    this.name = name; 
    this.server = net.createServer((sock) => this.handleConnect(sock));
  }

  handleConnect(sock) {
    console.log('you have connected to', this.name);
    sock.on('data', (d) => this.handleData(sock, d))
  }

  handleData(sock, d) {
    console.log(d + '');
    sock.write(d)
  }

  start() {
    console.log(this.name, 'is listening on port 3000');
    this.server.listen(3000, '127.0.0.1') 
  }
}
const es = new EchoServer('Joe\'s echo server!!!!');
es.start();

/*
const net = require('net');
class EchoServer {
  constructor(name, msg) {
    this.msg = msg;
    this.name = name;
    this.server = net.createServer((sock) => this.handleConnect(sock));
  }

  handleConnect(sock) {
    sock.write(this.msg);
    sock.on('data', (data) => this.handleData(sock, data)) 
  }

  handleData(sock, data) {
    sock.write(data); 
  }

  start() {
    this.server.listen(3000); 
  }

}

const es = new EchoServer('es', 'hello');
es.start();
*/

/*
// create server will create new tcpip server
// function passed in will be called WHEN client
// connects
const server = net.createServer(function(sock) {
  // socket obj passed in to callback function
  // represents a connected client
  console.log('client connected');
  // it will call callback when event 'data' occurs
  // 'data' event means client sent us data
  sock.on('data', function(d) {
    console.log(d + ''); 
    sock.write(`I received: ${d}`);
  });
});
console.log('listening on port 3000');
server.listen(3000, '127.0.0.1');
*/