
#include <Arduino.h>
#include <time.h>


long previousMillis = 0;
const char VERSION[] ="0.0.1";

// Variables 

// Internal led
#define EspLedBlue 2


// setup -------------------------------------------------------------------------
void setup() {

  Serial.begin(115200);
  Serial.printf("Start setup Ver:%s\n\r",VERSION);


  // Set pin mode  I/O Directions
  pinMode(EspLedBlue, OUTPUT);     // Led is BLUE at statup
  digitalWrite(EspLedBlue, HIGH);  // After 5 seconds blinking indicate WiFI ids OK

}

// Main loop -----------------------------------------------------------------
void loop() {

  // Is alive executed every 1 sec.
  if ( millis() - previousMillis > 1000L) {
    previousMillis = millis();
    
    Serial.println("#Test ADE Front-end");
    Serial.println("ACR_Temperature1=23.48");
    // ....
 
  } // End second

} // End loop