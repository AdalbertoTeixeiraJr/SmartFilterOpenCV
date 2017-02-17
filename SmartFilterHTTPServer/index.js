var express = require('express');
var multer = require('multer');
var upload = multer({ dest: './uploads/' });
var path = require('path');
var uuid = require('uuid');
var net = require('net');
var app = express();

app.use(express.static('public'));

app.get('/', function (req, res) {
	res.send("Hello Carlos!");
});

app.post('/send_photo', upload.single('photo'), function (req, res) {
	var absolute_path = path.resolve('./uploads/' + req.file.filename);
	var new_name = uuid()+'.png';
	var new_path = path.resolve('./uploads_output/' + new_name);
	console.log(new_name);
	var type = req.body.type;
	var socket = new net.Socket();
	socket.connect(9000,'localhost', function(){
		socket.write(absolute_path+','+new_path+','+type);
	});
	var response;
	socket.on('data',function(data){
		response = data;
	});
	socket.on('close',function(){
		res.json({response: parseInt(response[0]), output: new_name});
	});
});


app.get('/photo/:name', function(req, res) {
	res.sendFile(path.resolve('./uploads_output/' + req.params.name));
});

app.listen(8080);



