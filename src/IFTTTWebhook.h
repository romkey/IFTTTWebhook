/* 
   IFTTTWebhook.h
   Created by John Romkey - https://romkey.com/
   March 24, 2018
 */
#ifndef IFTTT_H
#define IFTTT_H

#define DEFAULT_IFTTT_FINGERPRINT "C0:5D:08:5E:E1:3E:E0:66:F3:79:27:1A:CA:1F:FC:09:24:11:61:62"

class IFTTTWebhook {
 public:
  IFTTTWebhook(char* api_key, char* event_name);
  IFTTTWebhook(char* api_key, char* event_name, char* ifttt_fingerprint);
  
  int trigger(char* value1, char* value2, char* value3);
  int trigger(char* value1, char* value2);
  int trigger(char* value1);
  int trigger();
  
 private:
  const char* _api_key;
  const char* _event_name;
  const char* _ifttt_fingerprint;
};

#endif

