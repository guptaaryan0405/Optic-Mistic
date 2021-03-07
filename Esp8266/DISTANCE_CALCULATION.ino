#define TRIGGER 5
#define ECHO    4
 
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>


// Set these to run example.
#define FIREBASE_HOST "distanceee-4d11c-default-rtdb.firebaseio.com"              // the project name address from firebase id
#define FIREBASE_AUTH "8eG5iPBBcs1rP1Lx4uaKxZIVMbouuIbIXvieowKD"       // the secret key generated from firebase
#define WIFI_SSID "TEST"                                         
#define WIFI_PASSWORD "aryangupta"   

void setup() {
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting"); 
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUILTIN_LED, OUTPUT);
}
 
void loop() {

  
  long duration, distance;
  digitalWrite(TRIGGER, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = (duration/2) / 29.1;
  
  Serial.print(distance);
  Serial.println("Centimeter:");
  String fireDistance=String(distance);
  delay(500);
  Firebase.pushString("Distance",fireDistance);  
    if (Firebase.failed()) 
    {
 
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error()); 
      return;
  }
   
  
}
