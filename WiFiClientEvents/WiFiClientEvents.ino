/*
 *  This sketch shows the WiFi event usage
 *
 */

#include <ESP8266WiFi.h>

const char* ssid     = "SSID";
const char* password = "PASSWORD";


void WiFiEvent(WiFiEvent_t event) {
    Serial.printf("[WiFi-event] event: %d\n", event);

    switch(event) { 
    case WIFI_EVENT_STAMODE_CONNECTED:
      Serial.printf("[WiFi] %d, Connected\n", event);
    break;
    
    case WIFI_EVENT_STAMODE_DISCONNECTED:
      Serial.printf("[WiFi] %d, Disconnected - Status %d, %s\n", event, WiFi.status(), connectionStatus( WiFi.status() ).c_str() );      
    break;
    
     case WIFI_EVENT_STAMODE_AUTHMODE_CHANGE:
      Serial.printf("[WiFi] %d, AuthMode Change\n", event);
    break;
    
    case WIFI_EVENT_STAMODE_GOT_IP:
      Serial.printf("[WiFi] %d, Got IP\n", event);
    break;
    
    case WIFI_EVENT_STAMODE_DHCP_TIMEOUT:
      Serial.printf("[WiFi] %d, DHCP Timeout\n", event);
    break;
    
    case WIFI_EVENT_SOFTAPMODE_STACONNECTED:
      Serial.printf("[AP] %d, Client Connected\n", event);
    break;
    
    case WIFI_EVENT_SOFTAPMODE_STADISCONNECTED:
      Serial.printf("[AP] %d, Client Disconnected\n", event);
    break;
    
    case WIFI_EVENT_SOFTAPMODE_PROBEREQRECVED:
//      Serial.printf("[AP] %d, Probe Request Recieved\n", event);
    break;
  }
}

String connectionStatus( int which )
{
  switch ( which )
    {
        case WL_CONNECTED:
            return "Connected";
            break;

        case WL_NO_SSID_AVAIL:
            return "Network not availible";
            break;

        case WL_CONNECT_FAILED:
            return "Wrong password";
            break;

        case WL_IDLE_STATUS:
            return "Idle status";
            break;

        case WL_DISCONNECTED:
            return "Disconnected";
            break;

        default:
            return "Unknown";
            break;
    }
  
}

void setup() {
    Serial.begin(115200);

    // delete old config
    WiFi.disconnect(true);

    delay(1000);

    WiFi.onEvent(WiFiEvent);
    WiFi.mode(WIFI_STA);                                                        // Station mode

    WiFi.begin(ssid, password);

    Serial.println();
    Serial.println();
    Serial.println("Wait for WiFi... ");
}


void loop() {
    delay(1000);
}

