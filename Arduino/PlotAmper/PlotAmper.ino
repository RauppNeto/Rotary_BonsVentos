#define Sin_SenCorrente    A2    // porta do senor de corrente

float  volt, c_value, f_Sin_Corrente;
const uint16_t n = 30; //amostras do Filtro FIR da corrente
float V_atual[n];


void setup() {
  // put your setup code here, to run once:

  //pinMode(Sin_SenCorrente, IMPUT);
  Serial.begin(9600);
  
  // Zera os vetes
  for (uint16_t i = 0; i < n ; i++)
   V_atual[n] = 0;

}

void loop() {
  // put your main code here, to run repeatedly:
  volt = 0;

  //Pega Valor Filtrado por media movel
  for (uint16_t i = 0; i < (n-1) ; i++) //Desloca uma varivel do vetor 
  V_atual[n] = V_atual[n + 1];

  V_atual[n] = analogRead(Sin_SenCorrente); //Salva a nova variavel
  
  for (uint16_t i = 0; i < n ; i++) //Soma o vetor
  f_Sin_Corrente += V_atual[n];
  
  f_Sin_Corrente = f_Sin_Corrente / n;

  volt = (5.0/1023.0)*f_Sin_Corrente; //Converte para corrente do sensor
  volt = volt -2.5 + 0.007;


  Serial.print("Corrente:");
  Serial.println(volt);

}
