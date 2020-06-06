#include <Arduino.h>

#include <Servo.h>;
int distancia(); // Declaracion de funcion de medicion de distancia

const byte trigPin = 11;
const byte echoPin = 10;
const byte controlLed = 12;
const byte servoPin = 9;
const byte abierto = 120;
const int cerrado = 0;
bool estado = false;

Servo servo_puerta; // Crea objeto Servo

void setup() {

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(controlLed,OUTPUT);
  pinMode(servoPin, OUTPUT);

  servo_puerta.attach(servoPin); // Conectamos el servo
  servo_puerta.write(cerrado);	// Nos aseguramos que se inizializa en posicion cerrado...
  servo_puerta.detach();		// ...y desconectamos el servo.

  Serial.begin(9600); // Starts the serial communication

}

void loop() {

if(distancia()<10){
   delay(2000);
    while(distancia()<10)
    {
      if(estado==false){
      	digitalWrite(controlLed,HIGH);
      	servo_puerta.attach(servoPin);
      	servo_puerta.write(abierto);
	  	Serial.println("Abriendo puerta...");
      	delay(1000);
      	servo_puerta.detach();
        estado=!estado;
      }
      delay(1000);
      Serial.println("Puerta abierta");
      Serial.print("Distance: ");
  		Serial.println(distancia());
    }
  }else{
    if(estado==true){
     digitalWrite(controlLed,LOW);
     servo_puerta.attach(servoPin);
     servo_puerta.write(cerrado);
     Serial.println("Cerrando puerta...");
     delay(1000);
     servo_puerta.detach();
     estado=!estado;
    }
  	Serial.println("Puerta Cerrada");
  }

  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distancia());
delay(1000);
}

int distancia(){

  // defines variables
  long duration;
  int distance;
    // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;

  if (distance>300) distance = 5;
  // Calculating the distance
  return distance;
}
