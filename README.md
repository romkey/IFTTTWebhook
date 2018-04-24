# IFTTTWebHook ESP8266/ESP32 library

This is a small library that calls [IFTTT](https://ifttt.com) web
hooks from your ESP8266 or ESP32 Arduino project.

[IFTTT webhooks](https://ifttt.com/maker_webhooks) allow you to trigger IFTTT actions from your project. You might trigger an action because a button has been pushed, a temperature threshold has been passed, or just because you feel like it. You can pass up to three values with the trigger.

An action can be any IFTTT action:
- send an email or text message
- turn on a light
- add values to a Google Sheet
- call a webhook on another service

## Usage

1. If you haven't already, add the library to your Arduino project. Either:
- use "Manage Libraries" under the Sketch menu, locate `IFTTTWebhook` and install it
or
- download https://github.com/romkey/IFTTTWebhook/archive/master.zip and install it using "Add Zip" under the Sketch menu

2. Include the library in your project:
```
#include <IFTTTWebhook.h>
```

3. You'll need an IFTTT account, an IFTTT API key for that an account and a webhook event name.

Once you're logged into IFTTT you can get your API key by going to https://ifttt.com/maker_webhooks and clicking the `Documentation` button.

Instantiate an `IFTTTWebhook` object using your API key and the event name:

```
IFTTTWeb webhook(YOUR_IFTTT_API_KEY, YOUR_IFTTT_EVENT_NAME);
```

When you want to trigger the webhook, call the `trigger` method with zero to three `char*` to be passed as values:
```
webhook.trigger();
webhook.trigger("value1");
webhook.trigger("value1", "value2");
webhook.trigger("value1", "value2", "value3"); 
```

You can trigger using the same webhook object as many times as you want.

## Passing values other than strings

If you need to pass an `int`, `char`, `float` or some other type to
IFTTT, convert it to a `char*` array first. For instance, if you want
to pass a `float`, you can use `sprintf`:

```
float my_value = 2.558;

#define MAX_VALUE_STRING_LENGTH 32
char value_string[MAX_VALUE_STRING_LENGTH];

snprintf(value_string, MAX_VALUE_STRING_LENGTH, "%.2f", my_value);
```

This would result in the string "2.56" being passed to IFTTT. Replace
the `2` in `%.2f` with however many decimal places you need to pass to
IFTTT.

I considered offering variations of `trigger` which take different
types as any of the three values, but there are two problems with
this:

1. for floats, I don't know how many decimal places you want to send
to IFTTT
2. the number of varations get out of hand quickly, 3^_nth_ where _n_
   is the number of different types a value can be. You can reasonably
   argue that `trigger` should support `char*`, `int`, `unsigned` and
   `float`, which would require 81 different declarations of
   `trigger`, and that's not even supporting `long` and `unsigned
   long`.  It's much more straightforward and less error-prone if you
   encode your data as a C string, and then you have full control over
   the way it's formatted.

# No Strings

Arduino Core provides a
[String](https://www.arduino.cc/reference/en/language/variables/data-types/stringobject/)
class. 

`String` is a mixed bag. It's hugely convenient. C strings are awful
to deal with - they're simply arrays of characters in a language which
doesn't really have an array type. You have to be very careful
manipulating them - it's trivial to overflow them and overwrite other
data in your program. C string problems are one of the top reasons for
bugs in C programs. On the other hand, they're very efficient.

`String` avoids the problems of C strings, but at a cost. It gets its
character storage from the "heap" - a chunk of data memory that C can
allocate and free. Unfortunately, Arduinos and similar processors
don't have a lot of space for the heap and it's easy to fragment it to
the point of unusability. Using `String` a lot in an application will
lead to this, at which point your program won't be able to operate
correctly.

If your device reboots frequently - for instance, an ESP8266 which
spends most of its time in deep sleep - then you'll likely be fine. If
you've built an application which wants to run for a long time without
restarting, you should use `String` sparingly if at all.

`IFTTTWebhook` avoids using `String`, so it should not contribute to
heap fragmentation. You should also avoid using `String` to manage the
values you pass to `trigger` if you're concerned about heap
fragmentation (this is why `trigger` doesn't take `String` arguments).


