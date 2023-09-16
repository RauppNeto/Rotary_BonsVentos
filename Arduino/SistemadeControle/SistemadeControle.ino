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

// analog data acquisition function
void get_smaples() {
  // clear sample array
  for (uint16_t i = 0; i < n; i++)
    _array[i]  = 0.0;
  ADCSRA |= (1 << ADEN) | (1 << ADSC) ;  // enable ADC module and start converion (free running mode)
  // ignore the first reading
  while ( (ADCSRA & (1 << ADIF)) == 0 );  // wait for ADIF to be set (conversion complete)
  ADCSRA = ADCSRA;  // reset ADIF flag bit
  // fill samples array with 12-bit data (add another 2 bits using oversampling technique)
  for (uint16_t i = 0; i < n; i++) {
    for (uint16_t j = 0; j < 16; j++) {
      while ( (ADCSRA & (1 << ADIF)) == 0 );  // wait for ADIF to be set (conversion complete)
      ADCSRA |= (1 << ADIF);   // reset ADIF bit by writing 1 to it
      _array[i] += ADCW;
    }
  }
  ADCSRA &= ~((1 << ADEN) | (1 << ADSC)) ;  // stop conversion and disable ADC module, reset ADIF bit also
  for (uint16_t i = 0; i < n; i++)
    _array[i] /= 4.0;
}




// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(Sin_Acelerador);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  //Serial.println(voltage);


  //corrente


 // get digital representation of the internal bangap reference voltage
  float bgref_voltage = 0;   // Arduino internal reference voltage variable
  ADMUX |= (1 << MUX3) | (1 << MUX2) | (1 << MUX1);   // select internal bandgap refernce as input to ADC
  get_smaples();    // get samples
  for (uint16_t i = 0; i < n; i++)
    bgref_voltage += _array[i] ;
  bgref_voltage /= n;     // average value
 
  // read ACS758 output voltage
  float acs758_voltage = 0;   // ACS758 sensor output voltage variable
  ADMUX &= ~( (1 << MUX3) | (1 << MUX2) ) ;   // select analog channel 2 (A2) as input to ADC
  get_smaples();
  
   float _offset = 0;

   //média da corrente 
    for (uint16_t i = 0; i < n; i++){ // caculate signal average value (dc offset)
      _offset += _array[i];
//Serial.print("Corrente[");
//Serial.print(i);
//Serial.print("]:");
//Serial.print(_array[i]);
//Serial.println(",");
}
  _offset = _offset / n;
   
  //Serial.print("CorrenteMedia:");
  //Serial.print(_offset);
  //Serial.println(",");

  // corrente RMS 
  _offset = dc_offset;  // the dc offset is the pre-calibrated one
 
   // calculate signal RMS value (digital representation)
   for (uint16_t i = 0; i < n; i++)
     + += sq( _array[i] - _offset );
   acs758_voltage = acs758_voltage / n;
   acs758_voltage = sqrt(acs758_voltage);
 Serial.print("CorrenteRMS:");
Serial.println(acs758_voltage);
//Serial.println("-----Fim-----");


  
}
