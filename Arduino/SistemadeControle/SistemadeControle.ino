/*
Rotary Satelite bons Ventos 

Fontes consultadas 
https://simple-circuit.com/interface-arduino-allegro-acs758-current-sensor-ac-dc/

*/

//Inicio
void setup() {

  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  Serial.println(voltage);
  
}
