# IoT_FRDM
Web UI based data logger for FRDM-KL25z Development board

![alt tag](http://s28.postimg.org/tnuwta56l/Screenshot_from_2014_06_29_163046.png)
The web interface is created using Node.js. You will need "serialport", "socket.io", "smoothie" & "ws" modules to make this work. You also need to upload the mbed code to a FRDM-KL25z dev. board. Click the link in References [1] for installation instructions on Linux based operation system.


<b>Installation Instructions: (on ubuntu)</b>

<b>1. Install node.js: </b> <br>
&nbsp;&nbsp;&nbsp;&nbsp;sudo apt-get install python-software-properties <br>
&nbsp;&nbsp;&nbsp;&nbsp;sudo add-apt-repository ppa:chris-lea/node.js  <br>
&nbsp;&nbsp;&nbsp;&nbsp;sudo apt-get update  <br>
&nbsp;&nbsp;&nbsp;&nbsp;sudo apt-get install nodejs <br>

<b>2. Install npm (node package manager):</b> <br>
&nbsp;&nbsp;&nbsp;&nbsp;sudo apt-get install npm

<b>3. Install the aforementioned modules (first "cd" to: "./Web UI Source/node_modules")</b> <br>
&nbsp;&nbsp;&nbsp;&nbsp;npm install serialport  <br>
&nbsp;&nbsp;&nbsp;&nbsp;npm install socket.io  <br>
&nbsp;&nbsp;&nbsp;&nbsp;npm install smoothie  <br>
&nbsp;&nbsp;&nbsp;&nbsp;npm install ws <br>

These modules will be installed in "node_modules" folder in your current directory. Now, i will recommend installing "localtunnel" which will allow you to source your localhost to a webpage (intranet to internet).

<b>4. Install localtunnel</b> <br>
&nbsp;&nbsp;&nbsp;&nbsp;sudo apt-get install ruby ruby1.8-dev rubygems1.8 libopenssl-ruby  <br>
&nbsp;&nbsp;&nbsp;&nbsp;sudo gem install localtunnel  <br>

<b>Running the server:</b>

The server will run on port 8080 (you can change this in the server.js file if required)

<b>Run server</b> &nbsp;:&nbsp;&nbsp;  node index.html  (first cd to your project directory) <br>
<b>locatunnel</b> &nbsp;&nbsp;:&nbsp;&nbsp;  lt --port 8080

The localtunnel will generate a subdomain for you and you can use that to access your website anywhere.


<br>
<b>H/W Schematic: <br></b>

![alt tag](http://s4.postimg.org/hqcygptq5/Schematic_FSL133.png)

<b>References: <br><br></b>
1.</b> Youtube demo video:<a href ="https://www.youtube.com/watch?v=MLR95POeOU4"> youtube link </a>
