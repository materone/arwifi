#include <AltSoftSerial.h>
#include <arwifi.h>
arwifi wifiClient;
String data1;
char c1;
#define ledPin 13
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  wifiClient.begin(9600);
  Serial.println("Test Begin");
  //wifiClient.quitAP();
  Serial.println("Test 1");
  wifiClient.joinAP("CoolMi","26856204");
//  wifiClient.connect("10.128.5.44","1883",1);
//  wifiClient.disconnect(1);
  wifiClient.connect("materonep001.sinaapp.com","80",1);
  data1 = "GET /h.php HTTP/1.1\r\nhost:materonep001.sinaapp.com\r\n\r\n";
  uint8_t buff[data1.length()];
  data1.getBytes(buff,data1.length());
  wifiClient.write(buff,data1.length(),1);
  Serial.println(wifiClient.waitData("OK","","",""));
  wifiClient.disconnect(1);
}

void loop(){
  wifiClient.getWifiInfo();
}

