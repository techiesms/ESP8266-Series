/*
 *  This sketch trys to Connect to the best AP based on a given list
 *
 *  visit 
 *  http://www.techiesms.com
 *  for IoT project tutorials.
 *  
 *        #techiesms
 *  explore | learn | share
 */

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti wifiMulti;

void setup() {
    Serial.begin(115200); // --> default baudrate for ESP 12e board.
    delay(10);
	
    wifiMulti.addAP("ssid_from_AP_1", "your_password_for_AP_1"); 
    wifiMulti.addAP("ssid_from_AP_2", "your_password_for_AP_2");
    //wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3");



    
}

void loop() {
    if(wifiMulti.run() != WL_CONNECTED) {
        Serial.println("WiFi not connected!");
        delay(1000);
    }
    if(wifiMulti.run() == WL_CONNECTED) {
        Serial.println("");
        Serial.println("WiFi connected to");
        Serial.println(WiFi.SSID());// --> Name of the Access Point to which ESP is connected 
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP()); // --> Local IP address of ESP board
        delay(1000);
    }
}
