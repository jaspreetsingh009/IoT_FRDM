var server = require("./server");
var router = require("./route");
var requestHandlers = require("./requestHandlers");

var debug = false;

var handle = {}
handle["/"] = requestHandlers.sendInterface;
handle["/webui"] = requestHandlers.sendInterface;
handle["/smoothie.js"] = requestHandlers.smoothie;
handle["/gauge.min.js"] = requestHandlers.gaugemin;

server.start(router.route,handle,debug);
