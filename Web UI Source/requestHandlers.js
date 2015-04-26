var fs      =  require('fs');
var server  =  require('./server');

function sendInterface(response) {
  console.log("Request handler 'webui' was called.");
  response.writeHead(200, {"Content-Type": "text/html"});
  var html = fs.readFileSync(__dirname + "/webpage/main.html")
  response.end(html);
}

function smoothie(response) {
  console.log("Request handler 'smoothie' was called.");
  response.writeHead(200, {"Content-Type": "text/html"});
  var html = fs.readFileSync(__dirname + "/scripts/smoothie.js")
  response.end(html);
}

function socketio(response) {
  console.log("Request handler 'socketio' was called.");
  response.writeHead(200, {"Content-Type": "text/html"});
  var html = fs.readFileSync(__dirname + "/scripts/socket-io.js")
  response.end(html);
}

function gaugemin(response) {
  console.log("Request handler 'socketio' was called.");
  response.writeHead(200, {"Content-Type": "text/html"});
  var html = fs.readFileSync(__dirname + "/scripts/gauge.min.js")
  response.end(html);
}

exports.sendInterface  =   sendInterface;
exports.smoothie       =   smoothie;
exports.socketio       =   socketio;
exports.gaugemin       =   gaugemin;
