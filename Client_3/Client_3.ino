#include <ESP8266WiFi.h>
#include <WiFiClient.h>

WiFiServer server(80);
WiFiClient client;
const char* host="192.168.4.1";

#define green D0

#define yellow D1
#define red D2
void setup() {
pinMode(green, OUTPUT);
pinMode(red, OUTPUT);
pinMode(yellow, OUTPUT);
digitalWrite(green, LOW);
digitalWrite(yellow, LOW);
digitalWrite(red, HIGH);
Serial.begin(9600);

WiFi.mode(WIFI_STA);
delay(1000);
WiFi.begin("Nodemcu", "123456789");
while(WiFi.status()!=WL_CONNECTED)
{
Serial.println("wait");
delay(1000);
}
Serial.println();
Serial.println("Connected");
Serial.println(WiFi.localIP());
Serial.println(WiFi.gatewayIP());
}
void loop() {
delay(60000);
if(client.connect(host,80)){
Serial.println("connection established");
led();
}
}

void led(){
String answer = client.readStringUntil('\n');
Serial.println(answer);
answer.trim();
if (answer=="3on")
{
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
client.println("4on");
}
client.flush();
client.stop();
delay(30000);
return;
} 