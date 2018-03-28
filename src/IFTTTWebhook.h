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
  IFTTTWebhook(const char* api_key, const char* event_name);
  IFTTTWebhook(const char* api_key, const char* event_name, const char* ifttt_fingerprint);
  
  int trigger(const char* value1, const char* value2, const char* value3);
  int trigger(const char* value1, const char* value2);
  int trigger(const char* value1);
  int trigger();
  
 private:
  const char* _api_key;
  const char* _event_name;
  const char* _ifttt_fingerprint;
};

#endif

