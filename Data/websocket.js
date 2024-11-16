
var connection = new WebSocket('ws://' + location.hostname + ':81/', ['arduino']);
var first = true;

connection.onopen = function () {
  first = true;
  // connection.send('connected'); // Get value
};

connection.onerror = function (error) {
  console.log('WebSocket Error ', error);
};

// Function that receives the message from the ESP32 with the readings
connection.onmessage = function (evt) {
  console.log('Server: ', evt.data);
  var myObj = JSON.parse(evt.data);
  var keys = Object.keys(myObj);
  for (var i = 0; i < keys.length; i++){
      var key = keys[i];
      document.getElementById(key).innerHTML = myObj[key];
  }
};

connection.onclose = function () {
  console.log('WebSocket connection closed');
};

// Send value to Json format
function sendValue () {
  first = false;
  var val = document.getElementById('value').value** 2 / 1023;
  var txt = document.getElementById('text').value;
  var valstr = '{ value: ' + val.toString() +'; text: \"' + txt.toString() + '\"; }';  
  console.log('sendValue: ' + valstr);
  connection.send(valstr);
}
