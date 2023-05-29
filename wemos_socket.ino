#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <Servo.h>

const char* ssid = "HotspotWemos";
const char* password = "12345678";
// Create an instance of the server
ESP8266WebServer server(80);
// LED pins
int led1 = D4;
Servo myservo;

String htmlTemplate(){
String html = R"(
<!DOCTYPE html>
<html lang='en'>
<head>
<meta charset='UTF-8'>
<meta http-equiv='X-UA-Compatible' content='IE=edge'>
<meta name='viewport' content='width=device-width, initial-scale=1.0'>
<title>Wemos Based Automation</title>
<style>
  body{
  margin: 0;
  padding: 0;
  background-color: #003049;
  height: 100vh;

}
.container{
  height: 32em;
  width: 16em;
  margin: auto;
  text-align: center;
  padding: 1em;
}
.lcd, .command, .output{
  background-color: #219ebc;
  border-radius: .5em;
  margin: auto;

}
.lcd{
  width: 85%;
  height: 20%; 
  padding: .5em;   
}
.contain{
  display: flex;
  justify-content: center;
}
.entry_point{
  width: 45%;
  height: 50%;
  display: block;
}
.entry_point h3, .entry_point p, #nameSched{
  margin: 0;
}


.command{
  background-color: #003049;
  height: 35%;
  width: 85%;
  margin-top: 1em;
  padding: .5em;
}

.selectInput{
  width: 100%;
  height: 100%;
}
#dateMeSelect select{
  margin: auto;
  background-color: #219ebc;
  width: 90%;
  height: 45%;
  outline: none;
  border-radius: .5em;
  border: 1px solid #003049;
  color: #003049;
  font-weight: bolder;
  font-size: .8em;
}


#dateMe,#dateMeSelect{
  display: flex;
  margin-top: -1.5em;
}

.dateTime label{
  color: #219ebc;
}
#event{
  background:#003049;
  height: 20%;
  outline: none;
  border: 1px solid #219ebc;
  border-radius: .5em;
  color: #219ebc;
  position: relative;
  top: -1.5em;
}

#event:hover{
  background:#219ebc;
  color: #003049;
}
.dateTime{
  width: 100%;
  color: #219ebc;
  font-weight: bolder;
  font-size: 1.1em;
  height: 5em;
  margin-top: .5em;
  color:#003049;
}
.dateTime input{
  background-color: #219ebc;
  height: 40%;
  border-radius: .5em;
  border: 1px solid #003049;
  text-align: center;
  width: 90%;
}

::placeholder{
  color: #219ebc;
  text-align: center;
}



/* Buttons */
.buttons{
  border-radius: .5em;
  width: 100%;
  margin: auto;
  display: flex;
  height: 50%;
  margin-bottom: 1em;
}

.entry{
  width: 100%;
  border-radius: .5em;
  height: 100%;
  margin: auto;

}

.entry button{
  background: none;
  outline: none;
  border: 1px solid #219ebc;
  height:70%;
  width: 70%;
  border-radius: 100%;
  margin: auto;
  color: #219ebc;
  font-weight:bolder;
  margin-top: .5em;
  font-size: 2em;
  
}


.entry p{
  color: #219ebc;
  font-size: 1.5em;
  margin: 0;
}

#time_1{
  font-size: 1em;
}

</style>
</head>
<body>
<div class='container'>

  <div class='lcd'>
  <h3 id='nameSched'>SCHEDULE</h3>
  <div class='contain'>
  <div class='entry_point'>
    <h3>SWITCH</h3>
    <p id='componentText'>NA</p>
  </div>
  <div class='entry_point'>
    <h3>ON/OFF</h3>
    <p id='onOffText'>NA</p>
  </div>
</div>
  <div class='contain'>
    <div class='entry_point'>
      <h3>TIME</h3>
      <p id='timeText'>NA</p>
    </div>
    <div class='entry_point'>
      <h3>STATUS</h3>
      <p id='statusText'>NA</p>
    </div>
  </div>
  </div>

  <div class='command'>
    <div id='dateMeSelect'>
          <div class='dateTime'>
            <label for='before'>Component</label>
            <select name='component' id='component'>
              <option value='1' selected>Switch 1</option>
            </select>
          </div>

          <div class='dateTime'>
            <label for='until'>Activity</label>
            <select name='activity' id='activity'>
              <option value=''>Chose</option>
              <option value='0'>Turn OFF</option>
              <option value='1'>Turn ON</option>
              
            </select>
          </div>
      </div>

      <div id='dateMe'>
          <div class='dateTime'>
            <label for='before'>From</label>
            <input type='time' name='before' id='before'>
          </div>

          <div class='dateTime'>
            <label for='until'>Until</label>
            <input type='time' name='until' id='until'>
          </div>
      </div>

      <input type='button' onclick='sendRequest()' value='Add Event' id='event'>
    </div>
  
  <div class='buttons'>
    <div class='entry'>
      <p>Switch 1</p>
      <p id='time_1'>--:--:--</p>
      <button id='button_1' onclick='changeButton_1()'>ON</button>
    </div>
    
  </div>
</div>

</div>
<script>
  let startTimer_1;
  let intervalId_1;

  function ft_1(time) {
    return time < 10 ? '0' + time : time;
  }

  function updateTime_1() {
    const elapsedTime = Date.now() - startTimer_1;
    const hours = Math.floor(elapsedTime / 3600000);
    const minutes = Math.floor((elapsedTime % 3600000) / 60000);
    const seconds = Math.floor((elapsedTime % 60000) / 1000);
    const timeDisplay = document.getElementById('time_1');
    timeDisplay.textContent = ft_1(hours) + ':' + ft_1(minutes) + ':' + ft_1(seconds);
  }

  function startTime_1() {
    startTimer_1 = Date.now();
    intervalId_1 = setInterval(updateTime_1, 1000);
  }

  function stopTime_1() {
    clearInterval(intervalId_1);
  }

  function changeButton_1(num) {
    var xhttp = new XMLHttpRequest();
    const button = document.getElementById('button_1');
    if (button.innerHTML == 'ON' || num ==1){
      xhttp.open('GET', '/led?id=1&state=1', true);
      xhttp.send();
      button.innerHTML = 'OFF';
      button.style.background = '#8ecae6';
      button.style.color = '#219ebc';
      startTime_1();
    } else if  (button.innerHTML == 'OFF' || num == 0){
      xhttp.open('GET', '/led?id=1&state=0', true);
      xhttp.send();
      button.innerHTML = 'ON';
      button.style.background = 'none';
      button.style.color = '#219ebc';
      stopTime_1();
    }
  }

function checkWhatToDo(comp, state){
  switch(Number.parseInt(comp)){
    case 1:
      changeButton_1(state);
      break;
  }
}

const format = (str) => {
    const [hours, minutes] = str.split(':').map(Number);
    return (hours * 3600) + (minutes * 60);
  }

let currentDate, interval, end, res, eventAdded = false;
let firstStart = true, firstEnd =true;


function updateCurrentDate() {
var xhttp = new XMLHttpRequest();
const now = new Date();
  const myComponent = document.getElementById('component').value;
let myActivity = document.getElementById('activity').value;

currentDate = format(`${now.getHours()}:${now.getMinutes()}`);
if (eventAdded && currentDate >= interval && currentDate <= end) {
if(firstStart){
console.log('Start Event')
document.getElementById('statusText').innerHTML = 'Ongoing';
checkWhatToDo(myComponent,myActivity)
}

firstStart = false;
} else if (eventAdded && !firstStart) {
if(firstEnd){
console.log('End Event')
myActivity = myActivity==0? 1: 0
checkWhatToDo(myComponent,myActivity)
document.getElementById('statusText').innerHTML = 'Done';
}

firstEnd = false;

}
}

function sendRequest() {
const componentSelect= document.getElementById('component').value;
const activitySelect = document.getElementById('activity').value;
const before = document.getElementById('before').value;
const until = document.getElementById('until').value;

document.getElementById('componentText').innerHTML = componentSelect
document.getElementById('onOffText').innerHTML = activitySelect==0? 'OFF':'ON'
document.getElementById('timeText').innerHTML = `${before}:${until}`
interval = format(before);
end = format(until);
eventAdded = true;

}

setInterval(updateCurrentDate, 1000);
  
</script>
</body>
</html>

)";

return html;
}

void handleLed() {
  String id = server.arg("id");
  String state = server.arg("state");
  String ledme = "led"+id;
  String status = (state.toInt()==1)? "HIGH" : "LOW";
  String message = "Switch "+id+" is "+status;
    if(status=="HIGH"){
      digitalWrite(led1, HIGH);    
      myservo.write(180);  
    }else{
      digitalWrite(led1, LOW);
      myservo.write(0);    
    }
    Serial.println(message);
    server.send(200, "text/plain", message);
}

void handleRoot() {
  String html = htmlTemplate();
  server.send(200, "text/html", html);
}

void setup() {
  // Set LED pins as outputs
  pinMode(led1, OUTPUT);
  myservo.attach(D3);

  // IPAddress ip(192, 168, 1, 69);    // Replace with your desired IP address
  IPAddress ip(192, 168, 43, 69);    // Replace with your desired IP address
  IPAddress gateway(192, 168, 43, 1); // Replace with your gateway IP address
  IPAddress subnet(255, 255, 255, 0); // Replace with your subnet mask

  WiFi.config(ip, gateway, subnet);
  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  // Print IP address
  Serial.begin(115200);
  Serial.println("");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // On HTTP request, handle LED control
  server.on("/led", HTTP_GET, handleLed);
  server.on("/", HTTP_GET, handleRoot);

  // Start server
  server.begin();
}

void loop() {
  // Handle client requests
  server.handleClient();

}
