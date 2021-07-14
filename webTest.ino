#include <ESP8266WebServer.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// Data wire is plugged into port D2 on the ESP8266
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

float tempSensor1, tempSensor2, tempSensor3;

uint8_t sensor1[8] = { 0x28, 0xAC, 0x74, 0xD0, 0x64, 0x20, 0x01, 0xE8  };
uint8_t sensor2[8] = { 0x28, 0xE5, 0x93, 0x6C, 0x64, 0x20, 0x01, 0x03  };
uint8_t sensor3[8] = { 0x28, 0x2D, 0xA6, 0x49, 0x64, 0x20, 0x01, 0x9A  };

/*Put your SSID & Password*/
const char* ssid = "Casa Lima 2.4Ghz";  // Enter SSID here
const char* password = "Casalima1999";  //Enter Password here

//ESP8266WebServer server(80);
String stringMain, stringArca1, stringArca2, stringArca3;             
 
void setup() {
  Serial.begin(115200);
  delay(100);
  
  sensors.begin();              

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("...");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
}
void loop() {
  if(WiFi.status() == WL_CONNECTED){
      //String httpRequestData = "api_key=tPmAT5Ab3j7F9&sensor=BME280&value1=24.25&value2=49.54&value3=1005.14";           
      // Send HTTP POST request
      //int httpResponseCode = http.POST(httpRequestData);
    sensors.requestTemperatures();
    tempSensor1 = sensors.getTempC(sensor1); // Gets the values of the temperature
    tempSensor2 = sensors.getTempC(sensor2); // Gets the values of the temperature
    tempSensor3 = sensors.getTempC(sensor3); // Gets the values of the temperature
    
    HTTPClient http; //Object of class HTTPClient
    http.begin("http://msm.hopto.org/area/frigorifica/temperatura");
    //int httpCode = http.POST();
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", "validtokennn");
    
    stringMain = String("{\"user_id\":\"77\",\"temperatura\":\"");
    stringArca1 = String("\",\"area_frigorifica_id\":\"2333\"}");
    stringArca2 = String("\",\"area_frigorifica_id\":\"345345\"}");
    stringArca3 = String("\",\"area_frigorifica_id\":\"121\"}");

    int httpResponseCode = http.POST(stringMain+tempSensor1+stringArca1);
    Serial.println("Temperatura 1: "+String(tempSensor1));
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    
    http.end();
    delay(1000);
    http.begin("http://msm.hopto.org/area/frigorifica/temperatura");
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", "validtokennn");

    httpResponseCode = http.POST(stringMain+tempSensor2+stringArca2);
    Serial.println("Temperatura 2: "+String(tempSensor2));
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    http.end();
    delay(1000);
    http.begin("http://msm.hopto.org/area/frigorifica/temperatura");
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", "validtokennn");

    httpResponseCode = http.POST(stringMain+tempSensor3+stringArca3);
    Serial.println("Temperatura 3: "+String(tempSensor3));
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    
        
    // Free resources
    http.end();
    delay(30000);

  }
  

  
}
