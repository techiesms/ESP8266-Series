/*
 *  HTTP over TLS (HTTPS) example sketch
 *
 *  This example demonstrates how to use
 *  WiFiClientSecure class to access HTTPS API.
 *  We fetch and display the status of
 *  esp8266/Arduino project continuous integration
 *  build.
 *
 *  Created by Ivan Grokhotkov, 2015.
 *  This example is in public domain.
 *  
 *   For tutorial video of this code, watch out this video
 *   https://youtu.be/dsmMzS3Qvg0
 *  
 *  visit 
 *  http://www.techiesms.com
 *  for IoT project tutorials.
 *  
 *        #techiesms
 *  explore | learn | share
 */

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char* ssid = "SSID"; // Name of the Host
const char* password = "PASSWORD"; // Password of the corresponding Host

const char* host = "api.github.com"; // Server from which data is to be fetched
const int httpsPort = 443; // Default port for HTTPS 

// Use web browser to view and copy
// SHA1 fingerprint of the certificate
const char* fingerprint = "35 85 74 ef 67 35 a7 ce 40 69 50 f3 c0 f6 80 cf 80 3b 2e 19"; // Fingerprint/Thumbprint for website api.github.com
                         
void setup() {
  Serial.begin(115200); //default baud rate for esp12e
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password); // establish connection with mentioned Host
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); // Print out the Local IP assigned by the router to ESP8266

 
  WiFiClientSecure client;  // Use WiFiClientSecure class to create client instance
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpsPort)) { // establishing connection with the server(api.github.com) at port 443
    Serial.println("connection failed");
    return; // this line will return the function to the starting of void setup()
  }

  if (client.verify(fingerprint, host)) { // verfying fingerprint with the server
    Serial.println("certificate matches");
  } else {
    Serial.println("certificate doesn't match");
  }

  String url = "/repos/esp8266/Arduino/commits/master/status"; //address from which we need to get the data inside the server.
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");
  /*
   * GET /repos/esp8266/Arduino/commits/master/status HTTP/1.1
   * Host : api.github.com
   * User-Agent : BuildFailureDetectorESP8266
   * Connection : close
   */

  Serial.println("request sent");
  while (client.connected()) { // until the client is connected, read out the response
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("esp8266/Arduino CI successfull!");
  } else {
    Serial.println("esp8266/Arduino CI has failed");
  }
  Serial.println("reply was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("closing connection");
}

void loop() {
}
