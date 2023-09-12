/*
Rotary Satelite bons Ventos 

Fontes consultadas 
https://simple-circuit.com/interface-arduino-allegro-acs758-current-sensor-ac-dc/

*/


#define REF_VOLTAGE     1100.0  // internal bandgap reference voltage, in millivolts
#define ACS758_SENS     10      // ACS758 sensitivity = 10mV/A (for ACS758-200B version)
#define Sin_Acelerador    A0    // porta do acelerador
#define Sin_SenCorrente    A2    // porta do senor de corrente

const uint16_t n = 256;   // number of samples
float _array[n];          // sample array with 'n' elements
float dc_offset;          // auto-calibration dc offset


//Inicio
void setup() {

  Serial.begin(9600);


  // ADC configuration
  ADMUX |= (1 << REFS0) ;   // set ADC +ive vlotage reference to AVCC
  // ADC auto triggering is enabled, ADC clock division factor set to 128 (ADC clock = 125kHz)
  ADCSRA |= (1 << ADATE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

 // do auto-calibration to the circuit (no current should flow through the ACS758 sensor)
  ADMUX |= (1 << MUX1) ;   // select analog channel 2 (A2) as input to ADC
  dc_offset = 0;
  get_smaples();
  for (uint16_t j = 0; j < n; j++)
  dc_offset += _array[j];
  dc_offset /= n;

}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(Sin_Acelerador);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  Serial.println(voltage);
}
