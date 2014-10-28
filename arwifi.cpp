/*
 arwif.cpp - A simple esp8266 wifi lib.
  Tony
  Chufan Studio
  20141028
*/

#include "arwif.h"
#include <string.h>
#include <AltSoftSerial.h>

//define var
AltSoftSerial serWifi;
String data;
char c;
unsigned long tStart, timeInterval = 10000, timeFree = 0, timeLast = 0;

arwif::arwif() {

}
arwif::arwifi(char* sid, char* passwd) {
  quitAP();
  joinAP();
}
boolean arwif::connect(char * url) {
  boolean rc = false;
  return rc;
}
boolean arwif::connect(char * host, char * port,int mux) {
  boolean rc = false;
  return rc;
}
void arwif::disconnect(int mux) {


}
boolean arwif::joinAP(char* sid, char* passwd) {
  String ret = "";
  for (int i = 0; i < 3 ; i++) {
    serWifi.println("AT+CIFSR");
    ret = waitData("OK", "", "", "");
    if (ret.indexOf("0.0.0.0") != -1) {
      serWifi.print("AT+CWJAP=\"")
      serWifi.print(sid);
      serWifi.print("\",\"");
      serWifi.print(passwd);
      serWifi.println("\"");
      ret = waitData("OK", "ERROR", "", "");
      if (ret.indexOf("OK") != -1) {
        rc = true;
        break;
      }
    } else {
      rc = true;
      break;
    }
    delay(1000);
  }

  return rc;
}
boolean arwif::quitAP() {
  boolean rc = false;
  serWifi.print("AT+CWQAP");
  String s = waitData("OK", "ERROR", "", "");
  if (s.indexOf("OK") != -1) {
    rc = true;
  }
  return rc;

}
boolean arwif::connected() {
  boolean rc = false;
  return rc;
}
boolean arwif::available() {
  //boolean rc = false;
  return serWifi.available();
}
uint8_t arwif::read() {
  uint8_t rc = false;
  return rc;
}
boolean arwif::write(uint8_t* buf, uint16_t length) {
  boolean rc = false;
  return rc;
}
String arwif::waitData(char * tag1, char * tag2 = null, char * tag3 = null, char * tag4 = null) {
  String ret = "";
  timeLast = millis();
  while (1)
  {
    if (serWifi.available()) {
      data = "";
      while (serWifi.available()) {
        c = char(serWifi.read());
        data += c;
        delay(1);
      }
      Serial.print(data);
      ret += data;
    }
    timeFree = millis();
    if ((timeFree > timeLast) && (timeFree - timeLast) > timeInterval) break;

    //找到任何一个标识符即退出。
    if ((Tag1 != "") && (data.indexOf(Tag1) == 0)) break;
    if ((Tag2 != "") && (data.indexOf(Tag2) != -1)) break;
    if ((Tag3 != "") && (data.indexOf(Tag3) != -1)) break;
    if ((Tag4 != "") && (data.indexOf(Tag4) != -1)) break;
  }
  return ret;
}