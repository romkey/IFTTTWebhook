/* 
   IFTTTWebhook.cpp
   Created by John Romkey - https://romkey.com/
   March 24, 2018
 */
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include "IFTTTWebhook.h"

IFTTTWebhook::IFTTTWebhook(const char* api_key, const char* event_name) : IFTTTWebhook::IFTTTWebhook(api_key, event_name, DEFAULT_IFTTT_FINGERPRINT) {
}

IFTTTWebhook::IFTTTWebhook(const char* api_key, const char* event_name, const char* ifttt_fingerprint) {
  _api_key = api_key;
  _event_name = event_name;
  _ifttt_fingerprint = ifttt_fingerprint;
}

int IFTTTWebhook::trigger() {
  return IFTTTWebhook::trigger(NULL, NULL, NULL);
}

int IFTTTWebhook::trigger(const char* value1) {
  return IFTTTWebhook::trigger(value1, NULL, NULL);
}

int IFTTTWebhook::trigger(const char* value1, const char* value2) {
  return IFTTTWebhook::trigger(value1, value2, NULL);
}

int IFTTTWebhook::trigger(const char* value1, const char* value2, const char* value3) {
  HTTPClient http;
  const char* ifttt_base = "https://maker.ifttt.com/trigger";

  int url_length = strlen(ifttt_base) + strlen("/") + strlen(_event_name) + strlen("/with/key/") + strlen(_api_key) + strlen("?") + (strlen("&valuex=")*3);
  url_length += (value1 ? strlen(value1) : 0) + (value2 ? strlen(value2) : 0) + (value3 ? strlen(value3) : 0);
  url_length += 5;
  char ifttt_url[url_length];

#ifdef IFTTT_WEBHOOK_DEBUG  
  Serial.print("URL length: ");
  Serial.println(url_length);
#endif
  
  snprintf(ifttt_url, url_length, "%s/%s/with/key/%s", ifttt_base, _event_name, _api_key);
  if(value1 || value2 || value3) {
    strcat(ifttt_url, "?");
  }

  if(value1) {
    strcat(ifttt_url, "value1=\"");
    strcat(ifttt_url, value1);
    strcat(ifttt_url, "\"");
    if(value2 || value3) {
      strcat(ifttt_url, "&");
    }
  }
  
  if(value2) {
    strcat(ifttt_url, "value2=\"");
    strcat(ifttt_url, value2);
    strcat(ifttt_url, "\"");
    if(value3) {
      strcat(ifttt_url, "&");
    }
  }
  
  if(value3) {
    strcat(ifttt_url, "value3=\"");
    strcat(ifttt_url, value3);
    strcat(ifttt_url, "\"");
  }

#ifdef IFTTT_WEBHOOK_DEBUG  
  Serial.println(ifttt_url);
#endif
  
  // fingerprint: openssl s_client -connect maker.ifttt.com:443  < /dev/null 2>/dev/null | openssl x509 -fingerprint -noout | cut -d'=' -f2
  http.begin(ifttt_url, _ifttt_fingerprint);
  int httpCode = http.GET();

#ifdef IFTTT_WEBHOOK_DEBUG  
  if (httpCode > 0) {
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);

    if(httpCode == HTTP_CODE_OK) {
      Serial.println(http.getString());
    }
  } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
#endif

    http.end();

    return httpCode != HTTP_CODE_OK;
  }
