#include <SPI.h> 
#include<WiFi.h>

const char* ssid = "Wokwi-GUEST";
const char* pass = "";
//open weather map api key 
String apiKey= "2433516c3d8cf727338deab79e2ea38d"; 
//the city you want the weather for 
String location= "torino,IT"; 
int status = WL_IDLE_STATUS; 
char server[] = "api.openweathermap.org";     
WiFiClient client; 

void setup(){
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED){
    delay(100);
    Serial.println(".");
  }
  Serial.println("WiFi Connected!");
  Serial.println(WiFi.localIP());
}

void loop(){
getWeather(); 
 delay(10000); 
}

void getWeather() { 
 Serial.println("\nStarting connection to server..."); 
 // if you get a connection, report back via serial: 
 if (client.connect(server, 80)) { 
   Serial.println("connected to server"); 
   // Make a HTTP request: 
   client.print("GET /data/2.5/forecast?"); 
   client.print("q="+location); 
   client.print("&appid="+apiKey); 
   client.print("&cnt=3"); 
   client.println("&units=metric"); 
   client.println("Host: api.openweathermap.org"); 
   client.println("Connection: close"); 
   client.println(); 
 } else { 
   Serial.println("unable to connect"); 
 } 
 delay(1000); 
 String line = ""; 
 while (client.connected()) { 
   line = client.readStringUntil('\n'); 
   Serial.println(line); 
 } 
} 