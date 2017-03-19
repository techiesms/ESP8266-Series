/*
 Create a WiFi access point and provide a web server on it. 

For tutorial video of this code, watch out this video
https://youtu.be/fcmb_3aBfH4

  visit 
  http://www.techiesms.com
  for IoT project tutorials.
  
        #techiesms
  explore | learn | share

*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

/* Set these to your desired credentials. */
const char *ssid = "ESPap"; // You can change it according to your ease
const char *password = "thereisnospoon"; // You can change it according to your ease

ESP8266WebServer server(80); // establishing server at port 80 (HTTP protocol's default port)


// Writing a simple HTML page.
char HTML[] = "<html><body><h1>For ESP8266 tutorials visit</h1><h2>www.techiesms.com</h2><a href=\"http://192.168.4.1/1\">Go to Page 1  </a> <button><a href=\"toggle\">Toggle LED</a></button> </body></html>"; // --> Simple HTML page


// This function will be called whenever anyone requests 192.168.4.1 within the local area connection of this ESP module.
void handleRoot() 
{
	server.send(200, "text/html",HTML);
}

// This function will be called whenever anyone requests 192.168.4.1/1 within the local area connection of this ESP module.
void Page1()
{
  server.send(200, "text/html", "<h1>techiesms</h1><h2>explore | learn | share </h2>");
}


// This function will be called whenever anyone requests 192.168.4.1/toggle within the local area connection of this ESP module.
void toggle()
{
  digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
  server.send(200, "text/html",HTML);
}

void setup() {
	delay(1000);
  pinMode(LED_BUILTIN,OUTPUT);
	Serial.begin(115200);
	Serial.println();

	Serial.print("Configuring access point...");
	/* You can remove the password parameter if you want the AP to be open. */
	WiFi.softAP(ssid, password); // --> This line will create a WiFi hotspot.

	IPAddress myIP = WiFi.softAPIP();
	Serial.print("AP IP address: ");
	Serial.println(myIP);
	server.on("/", handleRoot);
  server.on("/1",Page1);
  server.on("/toggle",toggle);
	server.begin();
	Serial.println("HTTP server started");
}

void loop() {
	server.handleClient();
}
