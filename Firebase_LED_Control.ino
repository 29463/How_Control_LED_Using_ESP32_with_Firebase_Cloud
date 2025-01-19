#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
 
#define FIREBASE_HOST "https://led-control-project-d5125-default-rtdb.asia-southeast1.firebasedatabase.app" // Firebase host
#define FIREBASE_AUTH "e6ImbSqKfkgygkM9xnPqfQOMq6ZVkhoxEJ6Freos" //Firebase Auth code
#define WIFI_SSID " " //Enter your wifi Name
#define WIFI_PASSWORD " " // Enter your password
int fireStatus = 0;
 
void setup() {
  Serial.begin(9600);
  pinMode(D1, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected.");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.set("LED_STATUS", 0);
}
 
void loop() {
  fireStatus = Firebase.getInt("LED_STATUS");
  if (fireStatus == 1) {
    Serial.println("Led Turned ON");
    digitalWrite(D1, HIGH);
  }
  else if (fireStatus == 0) {
    Serial.println("Led Turned OFF");
    digitalWrite(D1, LOW);
  }
  else {
    Serial.println("Command Error! Please send 0/1");
  }
} 