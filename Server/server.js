//Refernced from: https://gist.githubusercontent.com/sid24rane/6e6698e93360f2694e310dd347a2e2eb/raw/44aaf3c7689325e4d8262272a3aee1d5b419ed48/udp.js
var udp = require('dgram');
var server = udp.createSocket('udp4');

server.on('error',function(error){
  console.log('Error: ' + error);
  server.close();
});

server.on('message',function(msg,info){
  console.log('\nData received from client: ' + msg.toString());
  console.log('Received %d bytes from %s:%d',msg.length, info.address, info.port);

  setTimeout(function(){},2000);
  console.log("[!] Responding to client...");
  server.send("This message is a responce from the nodeJS server!", info.port, 'localhost', (error) => {
    if(error) 
      console.log('[!] Error while sending responce');
    else
      console.log('[*] Responce sent');
  });
});

server.on('listening',() => {
  var address = server.address();
  var port = address.port;
  var family = address.family;
  var ipaddr = address.address;
  console.log('Server port:       ' + port);
  console.log('Server ip:         ' + ipaddr);
  console.log('Server is IP4/IP6: ' + family);
});

server.on('close',function(){
  console.log('[!] Socket closed');
});

server.bind(2222);