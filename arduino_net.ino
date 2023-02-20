#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
// #include <list>

const char* ssid = "iPhone (Ибрагим)";
const char* psswrd =  "888888888";
byte tries = 10;
WiFiClient client;

String currentLine = "";

int id = 2;
int temp = 27;
int vlaz = 53;
int angle = 18;

//Парсинг 
struct StringParser {
    void reset() {
        from = to = -1;    
    }
    bool update(String& s, char div = ';') { //указываем разделитель
        if (to == s.length()) return 0;
        from = to + 1;
        to = s.indexOf(div, from);
        if (to < 0) to = s.length();
        str = s.substring(from, to);
        return 1;
    }
    String str;
    int from = -1;
    int to = -1;
};

struct Datchik {
  int temp;
  int vlaz;
  int angle;
  int id;
};

int get_angle(int temp) {
  if (temp >= 25 && temp < 30) {
    return 30;

  } else if (temp >= 30 && temp < 35) {
    return 45;
  
  } else if (temp >= 35 && temp < 40) {
    return 90;

  } else if (temp >= 90) {
    return 110;

  } else {
    return 0;

  }
}


void send() {
  int err = 0;
  Datchik dat2;
  HTTPClient http;  
  if(http.begin(client, "http://172.20.10.2:5000/api")){
    http.addHeader("Content-Type", "application/json");

    // int httpCode = http.GET();
    int httpCode = http.POST("{\"temp\":\"12\",\"vlaz\":\"50\",\"angle\":\"15\", \"id\":\"1\" }");
    if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        // Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        // Serial.println();
        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          // Serial.println(payload);
          
          
          String mas[4];
          String s = payload;   // строка для теста
          StringParser pars;  
          int i = 0;                // локально создать парсер
          while (pars.update(s)) {            // цикл обработки 
            String s = pars.str;
            // Serial.println(pars.str);         // забираем кусок строки
            // list1.push_back(s);

            mas[i++] = s;

          }

          dat2.temp = atoi(mas[0].c_str());
          dat2.vlaz = atoi(mas[1].c_str());
          dat2.angle = atoi(mas[2].c_str());
          dat2.id = atoi(mas[3].c_str());

          // Serial.print("Temperature: ");
          // Serial.println(dat2.temp);
          // Serial.print("Id: ");
          // Serial.println(dat2.id);
        delay(5000);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        Serial.println();
      }

      http.end();
  } else {
    Serial.println("error");
  }  

  int sr_temp = (dat2.temp + temp) / 2;
  Serial.println(sr_temp);
  Serial.println(get_angle(sr_temp));
  
}

void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, psswrd);
  while (--tries && WiFi.status() != WL_CONNECTED) {
    delay(5000);
    Serial.println(".");
  }
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Non Connecting to WiFi...");
  } else {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP adress: ");
    Serial.println(WiFi.localIP());
  }



  
}

void loop() {
  send();
  digitalWrite(2, HIGH);
  delay(1000);
}