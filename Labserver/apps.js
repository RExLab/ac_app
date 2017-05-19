// Setup basic express server
var panel = require('./build/Release/panel.node');
var express = require('express');
var app = express();

var server = require('http').createServer(app);
var io = require('socket.io')(server);
var port =  80;

app.use(express.static(__dirname + '/public'));

server.listen(port, function () {
  console.log('Server listening at port %d', port);
  
});


var configured = false, authenticated = false;

io.on('connection', function (socket) {
  var password  = ""; 
  var sync = 0, interval=0;

  
	  /*function SendMessage(socket){
		  if (sync < 10){
			var data = panel.getvalues();
			socket.emit('data received', data);
			sync = sync+1;
		  }else{
			  sync=0;
			  clearInterval(interval);
		  }
	  }*/
  
  socket.on('teste', function(data){
	socket.emit('teste',data);
  });
  
socket.on('new connection', function(data){
	  // fazer acesso ao rlms para autenticar
     //password = data.pass;
	  console.log('new connection' + data);

	  authenticated = true;
	  configured = panel.setup();
	  if(configured){
		  
	  }else{
		  panel.exit();
		  panel.setup();
  		  
	  }
	  
	  //SendMessage(socket);

  });
  
  
  socket.on('new message', function (data) {
	console.log( data);
	if(authenticated){
		  clearInterval(interval);
		  console.log(data);
		  var sum = 0; 
		  for(var x=0; x<4;x++){
			   sum = sum + (data.sw[x] << x);
		  }
			  
		  panel.update(sum);
		  //SendMessage(socket);
		  sync = 0;
		  //interval = setInterval(function(){SendMessage(socket) },1000);
	}
	  
  });


  socket.on('disconnect', function () {
	console.log('disconnected');

    if (configured) {
		panel.update("0");
		configured = authenticated = false;
		panel.exit();

    }else{
		panel.setup();
  		panel.update("0");
		panel.exit();
	}
  });
  
  
});

app.get('/:command', function (req, res) {
	console.log(req.params.command);
	if(configured){
		if(!isNaN(req.params.command)){
			panel.update(req.params.command);
		}
		
	}else{
		panel.setup();
  		if(!isNaN(req.params.command)){
			panel.update(req.params.command);
		}
		panel.exit();			
	}
	res.send("Estado atual: "+ req.params.command);
	
});
