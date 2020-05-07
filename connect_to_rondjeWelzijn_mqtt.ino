//
#include <ESP8266WiFi.h> // this import will allow for wifi connection
#include <ESP8266HTTPClient.h> // this import will allow to execute get/post requests
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <WiFiClientSecure.h>


const char* ssid = "your wifi code";             
const char* password = "your password";                

int motion = D0;                // choose the pin for the LED
int aliveSignal = D5;                // choose the pin for the LED
int pirSensor = D7;               // choose the input pin (for PIR sensor)
const String iot = "250016Lier";
int timer = 0;  // to count seconds
int waitTime = 1000;

void setup () {    
  Serial.begin(9600);        // initialize serial
  initPins();
  wifiConnect();
}

void loop() {   
   int state = digitalRead(pirSensor);   // read if sensor value is "0 or 1"
   
   if (timer == 60) { // sent signal every 60 seconds       
    digitalWrite(aliveSignal, HIGH);  // turn LED ON      
    doApiCall("250016Lier", "Alive");   
    //delay(waitTime);       
    timer = 0;       
   }
    else if(state == HIGH)//sent wakeywakey signal 
    {
       digitalWrite(motion, HIGH);  // turn LED ON   
       doApiCall("250016Lier", "WakeyWakey");
       state = 0;           
    }
//   else { 
//      digitalWrite(motion, LOW);  // turn LED OFF 
//    }
    timer++;
    delay(1000);
    Serial.println(timer);
    state = 0;
    digitalWrite(motion, LOW);  // turn LED OFF   
    digitalWrite(aliveSignal,LOW); // turn LED OFF 
    
  }

void initPins(){
     pinMode(motion, OUTPUT);      // declare LED as output
     pinMode(aliveSignal, OUTPUT);      // declare LED as output
     pinMode(pirSensor, INPUT);     // declare sensor as input   
     pinMode(pirSensor, LOW);       
  }

 void wifiConnect(){
  
  WiFi.begin(ssid, password); // lets connect to the wifi network

  // while connecting display status message 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting..");
  }
  Serial.println("Connected to WiFi Network"); 
 }
 

 void doApiCall(String IoT, String endpoint){

   //Check for WiFi connection status
   if (WiFi.status() == WL_CONNECTED) { 

    /*This class provides the methods to create and send the HTTP request.*/
    HTTPClient http;

    /*BearSSL::WiFiClientSecure is the 
      object which actually handles TLS encrypted WiFi connections to a remote server or client. 
      It extends WiFiClient and so can be used with minimal changes to code that does unsecured communications.*/
    BearSSL::WiFiClientSecure client;

    /*Don’t verify any X509 certificates. There is no guarantee that the server 
    connected to is the one you think it is in this case, but this call will mimic the 
    behavior of the deprecated axTLS code.*/
    client.setInsecure();               // Don't check fingerprint
    String url = "https://rondjewelzijnapi.azurewebsites.net/api/" + endpoint + "/" + IoT + "";
    http.begin(client, url);

    int httpCode = http.GET();

    if (httpCode == HTTP_CODE_OK) {
       Serial.println("Calling: " + endpoint);
     }
      else {
    Serial.printf("HTTP Error: %s\n", http.errorToString(httpCode).c_str());
    return;
  }
   http.end();
  }   
   //delay(10000);
  }
