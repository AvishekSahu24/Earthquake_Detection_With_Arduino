#include <ArduinoJson.h>
#include <SoftwareSerial.h>



/* Sending Sensor Data to Firebase Database by CircuitDigest(www.circuitdigest.com) */

#include <ESP8266WiFi.h>                                               // esp8266 library
#include <FirebaseArduino.h>                                                // firebase library
                                                  // dht11 temperature and humidity sensor library


#define FIREBASE_HOST "xbeewsn.firebaseio.com"                          // the project name address from firebase id
#define FIREBASE_AUTH "I4mWYGRpCqJdhUgH3HBDD0fTe4EKrFTqteU7RiTa"            // the secret key generated from firebase

#define WIFI_SSID "OnePlus 5"                                             // input your home or public wifi name 
#define WIFI_PASSWORD "lhingnunhoi57"                                    //password of wifi ssid
#include <SoftwareSerial.h>
SoftwareSerial mySerial(14,12, false, 128); //Define Hardware Connection


 
//String incomingbyte;
//int incomingbyte=0;                                 

void setup() {
  Serial.begin(9600);       //hardware serial
  mySerial.begin(9600);     //software serial
  delay(5000);                
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                              // connect to firebase

}
void loop() { 
//  incomingbyte= String(incomingbyte);
  
/*if(Serial.available()) {
  //read the incoming byte
 int incomingbyte = Serial.read();
  //show serial
 // Serial.print("Recieved Sensor Datas:");
  Serial.println(incomingbyte);
  //Firebase.setString("Readings/Values:", incomingbyte);
  


 Firebase.pushInt("/Readings", incomingbyte);                                  //setup path and send readings
        delay(4000);          */         
String IncomingString="";
boolean StringReady = false;

  while (mySerial.available()) {
  IncomingString=mySerial.readString();
  StringReady= true; 
      }
      if(StringReady){
        Serial.println("Recieved Datas:"  +  IncomingString);
        Firebase.pushString("Recieved Data:", IncomingString);
      }
 }
