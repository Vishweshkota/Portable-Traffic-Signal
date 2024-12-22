#include <ESP8266WiFi.h>
#include <WiFiClient.h>

WiFiClient client;
WiFiServer server(80);

#define green D0
#define yellow D1
#define red D2

String request= "1on";

void setup() {
    pinMode(green, OUTPUT);
    pinMode(yellow, OUTPUT);
    pinMode(red, OUTPUT);
    digitalWrite(green, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(red, HIGH);
    Serial.begin(9600);

    WiFi.mode(WIFI_AP);
    WiFi.softAP("Nodemcu", "123456789");

    Serial.println();
    Serial.println("Nodemcu started");
    Serial.println(WiFi.softAPIP());
    server.begin();

}
void loop (){
      if(request=="4on"){
      digitalWrite(green, LOW);
      digitalWrite(yellow, HIGH);
      digitalWrite(red, LOW);
      delay(5000);
      digitalWrite(green, HIGH);
      digitalWrite(yellow, LOW);
      digitalWrite(red, LOW);
      delay(20000);
      digitalWrite(green, LOW);
      digitalWrite(yellow, HIGH);
      digitalWrite(red, LOW);
      delay(5000);
      digitalWrite(green, LOW);
      digitalWrite(yellow, LOW);
      digitalWrite(red, HIGH);
      request="1on";
      Serial.println(request);
   }
    client = server.available();
    if(client){
    Serial.println("new client");
    led();
  }
}
void led() {
    if (client.connected()) {
    Serial.println("connected to client");
    if(request=="1on"){

      client.println("1on");
      delay(30000);
      request=client.readStringUntil('\n');
      Serial.println(request);
      request.trim();
      client.flush();
      return;
    } 
  if(request=="2on"){
      client.println("2on");
      delay(30000); 
      request=client.readStringUntil('\n');
    Serial.println(request);
    request.trim();
    client.flush();
    return;
   }
if(request=="3on"){
    client.println("3on");
    delay(30000);
    request=client.readStringUntil('\n');
    Serial.println(request);
    request.trim();
    client.flush();
    return;
    }
  }
}