/*
 arwifi.h - A simple esp8266 wifi lib.
  Tony
  Chufan Studio
  20141028
*/

#ifndef arwifi_h
#define arwifi_h

#include <Arduino.h>
#include <string.h>

// Define
#define VERSION 001

class arwif {
private:
   char* sid;
   char* passwd;
public:
   arwif();
   arwifi(char* sid,char* passwd);
   boolean connect(char * url);
   boolean connect(char * host, char * port, char * path=null);
   void disconnect();   
   boolean joinAP(char* sid,char* passwd);
   boolean quitAP();
   boolean connected();
   boolean available();
   uint8_t read();
   boolean write(uint8_t* buf, uint16_t length);
   String waitData(char * tag1,char * tag2=null,char * tag3=null,char * tag4=null);
};


#endif
