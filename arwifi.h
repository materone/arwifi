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

class arwifi {
private:
   char* sid;
   char* passwd;
public:
   arwifi();
   arwifi(char* sid,char* passwd);
   boolean connect(char * url);
   boolean connect(char * host, char * port, int mux);
   void disconnect(int mux);   
   boolean joinAP(char* sid,char* passwd);
   boolean quitAP();
   boolean connected();
   boolean available();
   uint8_t read();
   boolean write(uint8_t* buf, uint16_t length);
   String waitData(char * Tag1,char * Tag2,char * Tag3,char * Tag4);
   void getWifiInfo();
};


#endif
