#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 13 
DHT dht(DHTPIN, DHT11);
void setup() {
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  pinMode(2, OUTPUT);
  dht.begin();
}
void loop() {
  delay(2000); 
  float h = dht.readHumidity(); //Измеряем влажность
  float t = dht.readTemperature(); //Измеряем температуру
  if (isnan(h) || isnan(t)) {  // Проверка. Если не удается считать показания, выводится «Ошибка считывания», и программа завершает работу
    Serial.println("Error");
    digitalWrite(12, HIGH); // В случае ошибки загорается диод на 12-м пине.
    digitalWrite(2, 0);
    return;
  }
  digitalWrite(12, 0);
  digitalWrite(2, HIGH);
  Serial.print("Vlazn: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temp: ");
  Serial.print(t);
  Serial.println(" *C "); //Вывод показателей на экран
}
