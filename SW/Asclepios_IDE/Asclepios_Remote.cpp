#include "Asclepios_Remote.h"


void remote_monitoring_setup() {
  delay(1000);
  //  WiFi.mode(WIFI_STA); //Optional
  // Serial.println("SSID:");
  // Serial.println(ssid);
  // Serial.println("Password:");
  // Serial.println(password);
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting to the Wifi network");

  long unsigned int time = millis();
  while(WiFi.status() != WL_CONNECTED && ((millis() - time) < 500) ){
    Serial.println(".");
    delay(10);
    WiFi.begin(ssid, password);
  }

  if (WiFi.status() == WL_CONNECTED) { 
    Serial.println("\nConnected to the WiFi network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
  }
  else {
   Serial.println("\n Could not connect to the WiFi network on startup"); 
  }
}

void remote_monitoring_update() {
  if (WiFi.status() == WL_CONNECTED) { 
    Serial.println("\nConnected to the WiFi network");
  }
  else {
    Serial.println("\nConnecting to the WiFi network");
    unsigned long time = millis();
    while(WiFi.status() != WL_CONNECTED && ((millis() - time) < 500) ) {
      Serial.print(".");
      delay(10);
    }
  }
}

