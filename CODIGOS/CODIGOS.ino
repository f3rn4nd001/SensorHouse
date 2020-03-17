 #include <Wire.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

int duracion=1500; //Duración del sonido
int fMin=2000; //Frecuencia más baja que queremos emitir
int fMax=4000; //Frecuencia más alta que queremos emitir
int i=0;

int pinzumbador = 1;    // pin del zumbador
int frecuencia = 150;      // frecuencia correspondiente a la nota La


int duraciongas=1500; //Duración del sonido
int fMingas=4000; //Frecuencia más baja que queremos emitir
int fMaxgas=6000; //Frecuencia más alta que queremos emitir
int igas=0;
 
int SensorTempCocina=A0; 
int Pinbuzzer = 8; 
int SensorGasCocina = A1;
int SensorFlamaCocina = A2;
int SensorFlamaDodrmitorio = A3;
int SensorGasLimite = 250;
int sensortemperaturaLimite=33;
const int Trigger = 6;   
const int Echo = 7;   

void setup() {
  Serial.begin(9600);
  pinMode(SensorGasCocina, INPUT); //SE DEFINE COMO ENTRADA
  pinMode(Pinbuzzer, OUTPUT); // SE DEFINE COMO SALIDA
  pinMode(Trigger, OUTPUT); //SE DEFINE COMO SALIDA
  pinMode(Echo, INPUT);  //SE DEFINE COMO ENTRADA
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0
}

void loop() {
 //INICIO SENSOR DE TEMPERATURA
  //COCINA
    int SensorTempCocina=analogRead(SensorTempCocina); //Convierte los datos de  0 a 1023 (Teclas analogico a digital)
    Serial.print("#T1");
    Serial.print(",");  
    float Tensao=SensorTempCocina*5; //Se declara ka variable por decimal
    Tensao/=1024;
    float TemperaturaCocinaC=(Tensao-0.5)*10;
    float TemperaturaCocinaF=(TemperaturaCocinaC*9/5)+32;

    Serial.print(TemperaturaCocinaC);
    Serial.print(",");   
    Serial.println(TemperaturaCocinaF);
    
    if (TemperaturaCocinaC > sensortemperaturaLimite)
    {digitalWrite(Pinbuzzer, HIGH);
    delay(1000);
    }
     else
     {digitalWrite(Pinbuzzer, LOW);
     delay(50);
     }

 //SALA

//FIN SENSOR DE TEMPERATURA
 
  
//SENSOR DE GAS  
  //COCINA
    int ValorSensorGasCocina = analogRead(SensorGasCocina);
    Serial.print("#G1");
    Serial.print(",");  
    Serial.println(ValorSensorGasCocina);
    if (ValorSensorGasCocina > SensorGasLimite){
   for (i=fMingas;i<=fMaxgas; i++)
     tone(Pinbuzzer, i, duraciongas);
  //sonido más grave
  for (i=fMaxgas;i>=fMingas; i--)
    tone(Pinbuzzer, i, duraciongas); 
    }else{ 
    digitalWrite(Pinbuzzer, LOW);
    delay(50);
    }
    
 //SALA
//FIN SENSOR DE GAS  
// SENSOR FLAMA 
  //COCINA
    int ValorSensorFlamaCocina = analogRead(SensorFlamaCocina);
    Serial.print("#F1");
    Serial.print(",");  
    Serial.println(ValorSensorFlamaCocina);
    if (ValorSensorFlamaCocina < 30){
   for (i=fMin;i<=fMax; i++)
     tone(Pinbuzzer, i, duracion);
  //sonido más grave
  for (i=fMax;i>=fMin; i--)
    tone(Pinbuzzer, i, duracion);
    }else{ 
    digitalWrite(Pinbuzzer, LOW);
    delay(50);
    }
   // Sala
   int ValorSensorFlamaDodrmitorio = analogRead(SensorFlamaDodrmitorio);
    Serial.print("#D1");
    Serial.print(",");  
    Serial.println(ValorSensorFlamaDodrmitorio);
    if (ValorSensorFlamaDodrmitorio < 30)
    {
      for (i=fMin;i<=fMax; i++)
      tone(Pinbuzzer, i, duracion);
  //sonido más grave
      for (i=fMax;i>=fMin; i--)
      tone(Pinbuzzer, i, duracion);
    }else{ 
    digitalWrite(Pinbuzzer, LOW);
    delay(50);
    }
//INICIO SENSOR puerta
  long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros 
 
  digitalWrite(Trigger, LOW);
  delayMicroseconds(2);  
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  d = (t/2)/29.1;

      Serial.print("#P1");
    Serial.print(","); 
    Serial.print(d);      //Enviamos serialmente el valor de la distancia
    Serial.print(","); 
    Serial.println("cm");

  if (d <=12)
  {

  tone(Pinbuzzer,frecuencia);    // inicia el zumbido
    delay(1000);                    
    noTone(Pinbuzzer);               // lo detiene a los dos segundos
    delay(500);
      }
 
//FIN  SENSOR puerta
delay(1000);
}
