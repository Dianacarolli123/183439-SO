/*
    This sketch establishes a TCP connection to a "quote of the day" service.
    It sends a "hello" message, and then prints received data.
*/

#include <ESP8266WiFi.h>

const char* ssid     = "INFINITUM72EB_2.4";
const char* password = "Atd7tTd1VR";

int ledPin = 2;
int ledPin2 = 4;
int ledPin3 = 16;

WiFiServer  server(400);
void setup(){
  Serial.begin(115200);
  if(ledPin){
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW); 
  }
  if(ledPin2){
    pinMode(ledPin2, OUTPUT);
    digitalWrite(ledPin2, LOW); 
  }
  if(ledPin3){
    pinMode(ledPin3, OUTPUT);
    digitalWrite(ledPin3, LOW); 
  }
  

  Serial.print("Connecting to");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nWiFi connected");

  server.begin();
  Serial.println("Server started");

  Serial.print("Use this  URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.print("/\n");
}

void loop(){
  WiFiClient client = server.available();
  if(!client){
    return;
  }

  while(!client.available()){
    delay(1);
  }

  String request = client.readStringUntil('\r');
  if(request.indexOf("/favicon") == -1) {
    Serial.println("New client");
    Serial.println(request);
  }
  client.flush();

  int value = LOW;
  if(ledPin){
    if(request.indexOf("/LED=ON") != -1 ){
    digitalWrite(ledPin, HIGH); 
    value = HIGH;
    }
    if(request.indexOf("/LED=OFF") != -1 ){
      digitalWrite(ledPin, LOW); 
      value = LOW;
    }
  }
  if(ledPin2){
    if(request.indexOf("/LED=ON") != -1 ){
    digitalWrite(ledPin2, HIGH); 
    value = HIGH;
    }
    if(request.indexOf("/LED=OFF") != -1 ){
      digitalWrite(ledPin2, LOW); 
      value = LOW;
    }
  }
  if(ledPin3){
    if(request.indexOf("/LED=ON") != -1 ){
    digitalWrite(ledPin3, HIGH); 
    value = HIGH;
    }
    if(request.indexOf("/LED=OFF") != -1 ){
      digitalWrite(ledPin3, LOW); 
      value = LOW;
    }
  }
  

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.print("Led pin in now: ");

  if(value == HIGH){
    client.print("Off");
  }else{
    client.print("On");
  }

  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>Turn Off </button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>Turn ON </button></a><br />");
  client.println("</html>");

  delay(1);
  if(request.indexOf("/favicon") == -1) Serial.println("Client disconnected\n");

  
}
