// Выводы, подключенные к датчику
#define sensorPower 7 
#define powerSensor 8
#define sensorPin A0
#define pinSensor A5

//рэле
int RELAY_ON = 10;

void setup() 
{
  Serial.begin(9600);

  pinMode(sensorPower, OUTPUT);
  digitalWrite(sensorPower, HIGH);

  pinMode(RELAY_ON, OUTPUT);
  digitalWrite(RELAY_ON, LOW);

  pinMode(powerSensor, OUTPUT);
  digitalWrite(powerSensor, HIGH);
}


void loop() 
{
  int level = analogRead(sensorPin);
  int vs = analogRead(pinSensor);


  Serial.print("Water level:");
  Serial.print(level);
  Serial.print(" Humidity:");
  Serial.println(vs);



  if ((level == 0) || (vs > 570) || ((vs > 350) && (vs < 570))) 
  {
    digitalWrite(RELAY_ON, LOW);
  }
    else if ((vs < 350) && (level > 0)) 
  {
    digitalWrite(RELAY_ON, HIGH);
  }
  delay(5000);
  }
