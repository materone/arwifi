/*
 arwif.cpp - A simple esp8266 wifi lib.
  Tony
  Chufan Studio
  20141028
*/

#include "arwifi.h"
#include <string.h>
#include <AltSoftSerial.h>

#define  ledPin  13

//define var
AltSoftSerial serWifi;
String data;
char c;
unsigned long tStart, timeInterval = 10000UL, timeFree = 0UL, timeLast = 0UL;

arwifi::arwifi() {
  serWifi.begin(9600);
}
arwifi::arwifi(char* sid, char* passwd) {
  serWifi.begin(9600);
  quitAP();
  joinAP(sid, passwd);
}
boolean arwifi::connect(char * url) {
  boolean rc = false;
  return rc;
}
boolean arwifi::connect(char * host, char * port, int mux) {
  boolean rc = false;
  return rc;
}
void arwifi::disconnect(int mux) {
	serWifi.println("AT+CIPCLOSE=1");
}
boolean arwifi::joinAP(char* sid, char* passwd) {
  Serial.println("arwifi::joinAP");
  boolean rc = false;
  String ret = "";
  for (int i = 0; i < 3 ; i++) {
    serWifi.println("AT+CIFSR");
    ret = waitData("OK", "", "", "");
    if (ret.indexOf("0.0.0.0") != -1) {
      serWifi.print("AT+CWJAP=\"");
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
boolean arwifi::quitAP() {
  Serial.println("arwifi::quitAP");
  boolean rc = false;
  serWifi.print("AT+CWQAP");
  String s = waitData("OK", "ERROR", "", "");
  if (s.indexOf("OK") != -1) {
    rc = true;
  }
  return rc;

}
boolean arwifi::connected() {
  boolean rc = false;
  serWifi.println("AT+CIPSTATUS");
  String ret = waitData("OK", "ERROR", "", "");
  if(ret.indexOf("STATUS:3")!=-1) rc = true;
  return rc;
}
boolean arwifi::available() {
  //boolean rc = false;
  return serWifi.available();
}
uint8_t arwifi::read() {
  uint8_t rc = false;
  return rc;
}
boolean arwifi::write(uint8_t* buf, uint16_t length) {
  boolean rc = false;
  return rc;
}
String arwifi::waitData(char * Tag1, char * Tag2 = "", char * Tag3 = "", char * Tag4 = "") {
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

void arwifi::getWifiInfo() {
  if (serWifi.available()) {
    digitalWrite(ledPin, HIGH);
    data = "";
    Serial.print("WiFi:") ;
    while (serWifi.available()) {
      c = char(serWifi.read());
      data += c;
      //Serial.write(c);
      delay(1);
    }
    Serial.print(data);
    digitalWrite(ledPin, LOW);
  }

  if (Serial.available()) {
    digitalWrite(ledPin, HIGH);
    data = "";
    Serial.print("PC:") ;
    while (Serial.available()) {
      c = char(Serial.read());
      data += c;
      //serWifi.write(c);
      delay(2);
    }
    //Serial3.write(data);
    Serial.print(data);
    serWifi.print(data);
    digitalWrite(ledPin, LOW);
    //serWifi.println(data);
    delay(100);
    digitalWrite(ledPin, LOW);
  }
}