//
#include <ESP8266WiFi.h> // this import will allow for wifi connection
#include <ESP8266HTTPClient.h> // this import will allow to execute get/post requests
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <WiFiClientSecure.h>


const char* ssid = "put here your ssid";             
const char* password = "put here your password";                

int motion = D0;                // choose the pin for the LED
int noMotion = D5;                // choose the pin for the LED
int pirSensor = D7;               // choose the input pin (for PIR sensor)
int ledState = LOW;
const String iot = "250016Lier";
int timer = 0;                  // to count seconds

void setup () {    
  Serial.begin(9600);        // initialize serial
  initPins();
  wifiConnect();
}

void loop() {
   
   int state = digitalRead(pirSensor);   // read if sensor value is "0 or 1"
   
   if (timer == 60 || state == 1 ) { // sent wakeywakey signal if sensor reads motion otherwise every 60 seconds 
    digitalWrite(motion, HIGH);  // turn LED ON   
    digitalWrite(noMotion, LOW); // turn LED OFF
    Serial.println("wakeywakey!");
   // delay(waitTime);
    doApiCall("250016Lier", "WakeyWakey");
    state = 0;
    timer = 0;   
    }
   else { // sent alive signal
      digitalWrite(noMotion, HIGH); // turn LED ON
      digitalWrite(motion, LOW);  // turn LED OFF     
      Serial.println("Alive!");
      doApiCall("250016Lier", "Alive");                
    }
    timer+=2;
    Serial.println(timer);
    
  }

void initPins(){
     pinMode(motion, OUTPUT);      // declare LED as output
     pinMode(noMotion, OUTPUT);      // declare LED as output
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
//   delay(10000);
  }
