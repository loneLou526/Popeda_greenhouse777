#include "DHT.h"
#define DHTPIN 2 
DHT dht(DHTPIN, DHT11);

//пока наш двигатель находится на доработке,
//мы используем светодиоды, 
//в будущем мы укажем вместо них градусны меры углров для окна


int redLED = 3;
int yellowLED = 4;
int greenLED = 5;

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);
}


void loop() {
  delay(2000); 
  float h = dht.readHumidity(); 
  float t = dht.readTemperature(); 
  if (isnan(h) || isnan(t)) 
  { 
    Serial.println("Ошибка считывания");
    return;
  }
  else if (t>0 && t<=23) 
  {
    digitalWrite(redLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
  }
  else if (t>23 && t<=26) 
  {
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(greenLED, LOW);
  }
  else if (t>26) 
  {
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, HIGH);
  }
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Tempretuare: ");
  Serial.print(t);
  Serial.println(" *C ");
}