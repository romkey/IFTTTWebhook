#include <ESP8266WiFi.h>
#include "IFTTTWebhook.h"

#define WIFI_SSID "your SSID here"
#define	WIFI_PASSWORD "your password here"

#define IFTTT_API_KEY "your key here"
#define IFTTT_EVENT_NAME "your event name here"

void setup() {
  Serial.begin(115200);
  Serial.println("RUNNING");
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  IFTTTWebhook wh(IFTTT_API_KEY, IFTTT_EVENT_NAME);
  wh.trigger();
  wh.trigger("1");
  wh.trigger("1", "2");
  wh.trigger("1", "2", "3");
}

void loop() {
}
