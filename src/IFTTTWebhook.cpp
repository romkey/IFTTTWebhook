/* 
   IFTTTWebhook.cpp
   Created by John Romkey - https://romkey.com/
   March 24, 2018
 */

#ifndef ESP32
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#endif

#ifdef ESP32
#include <WiFi.h>
#include <HTTPClient.h>
#endif

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

#ifdef ESP32
const char* _ifttt_root_certificate = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIE0DCCA7igAwIBAgIBBzANBgkqhkiG9w0BAQsFADCBgzELMAkGA1UEBhMCVVMx" \
"EDAOBgNVBAgTB0FyaXpvbmExEzARBgNVBAcTClNjb3R0c2RhbGUxGjAYBgNVBAoT" \
"EUdvRGFkZHkuY29tLCBJbmMuMTEwLwYDVQQDEyhHbyBEYWRkeSBSb290IENlcnRp" \
"ZmljYXRlIEF1dGhvcml0eSAtIEcyMB4XDTExMDUwMzA3MDAwMFoXDTMxMDUwMzA3" \
"MDAwMFowgbQxCzAJBgNVBAYTAlVTMRAwDgYDVQQIEwdBcml6b25hMRMwEQYDVQQH" \
"EwpTY290dHNkYWxlMRowGAYDVQQKExFHb0RhZGR5LmNvbSwgSW5jLjEtMCsGA1UE" \
"CxMkaHR0cDovL2NlcnRzLmdvZGFkZHkuY29tL3JlcG9zaXRvcnkvMTMwMQYDVQQD" \
"EypHbyBEYWRkeSBTZWN1cmUgQ2VydGlmaWNhdGUgQXV0aG9yaXR5IC0gRzIwggEi" \
"MA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQC54MsQ1K92vdSTYuswZLiBCGzD" \
"BNliF44v/z5lz4/OYuY8UhzaFkVLVat4a2ODYpDOD2lsmcgaFItMzEUz6ojcnqOv" \
"K/6AYZ15V8TPLvQ/MDxdR/yaFrzDN5ZBUY4RS1T4KL7QjL7wMDge87Am+GZHY23e" \
"cSZHjzhHU9FGHbTj3ADqRay9vHHZqm8A29vNMDp5T19MR/gd71vCxJ1gO7GyQ5HY" \
"pDNO6rPWJ0+tJYqlxvTV0KaudAVkV4i1RFXULSo6Pvi4vekyCgKUZMQWOlDxSq7n" \
"eTOvDCAHf+jfBDnCaQJsY1L6d8EbyHSHyLmTGFBUNUtpTrw700kuH9zB0lL7AgMB" \
"AAGjggEaMIIBFjAPBgNVHRMBAf8EBTADAQH/MA4GA1UdDwEB/wQEAwIBBjAdBgNV" \
"HQ4EFgQUQMK9J47MNIMwojPX+2yz8LQsgM4wHwYDVR0jBBgwFoAUOpqFBxBnKLbv" \
"9r0FQW4gwZTaD94wNAYIKwYBBQUHAQEEKDAmMCQGCCsGAQUFBzABhhhodHRwOi8v" \
"b2NzcC5nb2RhZGR5LmNvbS8wNQYDVR0fBC4wLDAqoCigJoYkaHR0cDovL2NybC5n" \
"b2RhZGR5LmNvbS9nZHJvb3QtZzIuY3JsMEYGA1UdIAQ/MD0wOwYEVR0gADAzMDEG" \
"CCsGAQUFBwIBFiVodHRwczovL2NlcnRzLmdvZGFkZHkuY29tL3JlcG9zaXRvcnkv" \
"MA0GCSqGSIb3DQEBCwUAA4IBAQAIfmyTEMg4uJapkEv/oV9PBO9sPpyIBslQj6Zz" \
"91cxG7685C/b+LrTW+C05+Z5Yg4MotdqY3MxtfWoSKQ7CC2iXZDXtHwlTxFWMMS2" \
"RJ17LJ3lXubvDGGqv+QqG+6EnriDfcFDzkSnE3ANkR/0yBOtg2DZ2HKocyQetawi" \
"DsoXiWJYRBuriSUBAA/NxBti21G00w9RKpv0vHP8ds42pM3Z2Czqrpv1KrKQ0U11" \
"GIo/ikGQI31bS/6kA1ibRrLDYGCD+H1QQc7CoZDDu+8CL9IVVO5EFdkKrqeKM+2x" \
"LXY2JtwE65/3YR8V3Idv7kaWKK2hJn0KCacuBKONvPi8BDAB" \
"-----END CERTIFICATE-----\n";
#endif

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
  
#ifdef ESP32
  // certificate: openssl s_client -showcerts -connect maker.ifttt.com:443 < /dev/null
  http.begin(ifttt_url, _ifttt_root_certificate);
#else
  // fingerprint: openssl s_client -connect maker.ifttt.com:443  < /dev/null 2>/dev/null | openssl x509 -fingerprint -noout | cut -d'=' -f2
  http.begin(ifttt_url, _ifttt_fingerprint);
#endif
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
