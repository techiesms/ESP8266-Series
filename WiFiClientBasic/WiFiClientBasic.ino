/*
 *  This sketch sends a message to a TCP server
 *  visit 
 *  http://www.techiesms.com
 *  for IoT project tutorials.
 *  
 *        #techiesms
 *  explore | learn | share
 */

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti WiFiMulti;
String line="";

void setup() {
    Serial.begin(115200);
    delay(10);

    // We start by connecting to a WiFi network
    WiFiMulti.addAP("SmS", "sms123458955");

    Serial.println();
    Serial.println();
    Serial.print("Wait for WiFi... ");

    while(WiFiMulti.run() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    delay(500);
}


void loop() {
    const uint16_t port = 80;
    const char * host = "api.thingspeak.com";

    
    
    Serial.print("connecting to ");
    Serial.println(host);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;

    if (!client.connect(host, port)) {
        Serial.println("connection failed");
        Serial.println("wait 5 sec...");
        delay(5000);
        return;
    }

    // This will send the request to the server
    Serial.println("Connected!!!!!");
    //Serial.print("Send this data to server");

  String url = "/apps/thinghttp/send_request?api_key=QOSIIMQ9NBH5YQQN";
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Cache-Control: no-cache\r\n\r\n");

               Serial.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");

               /* 
                *  GET /apps/thinghttp/send_request?api_key=QOSIIMQ9NBH5YQQN HTTP/1.1 
                *  Host: api.thingspeak.com
                *  Connection; close
                */
delay(1000);

   while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  //Serial.println(line);
    Serial.println("closing connection");
    client.stop();
    
    Serial.println("wait 5 sec...");
    delay(5000);
}

