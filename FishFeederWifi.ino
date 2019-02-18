#include <Servo.h>
#include <time.h>
#include <ESP8266WiFi.h>
#include <AmazonIOTClient.h>
#include <ESP8266AWSImplementations.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>  

Esp8266HttpClient httpClient;
Esp8266DateTimeProvider dateTimeProvider;

AmazonIOTClient iotClient;
ActionError actionError;

Servo servo;

void initWLAN()
{
  WiFiManager wifiManager;
  wifiManager.autoConnect("CK-FISH-FEEDER");
  Serial.print("Wifi Connected:");
  Serial.print(WiFi.localIP());
  
}

void initAWS()
{
  iotClient.setAWSRegion("us-east-1");
  iotClient.setAWSEndpoint("amazonaws.com");
  iotClient.setAWSDomain("xxxx-ats.iot.us-east-1.amazonaws.com");
  iotClient.setAWSPath("/things/FishFeeder/shadow");
  iotClient.setAWSKeyID("xxxxxx");
  iotClient.setAWSSecretKey("xxxxxxxxxxxxxxxx");
  iotClient.setHttpClient(&httpClient);
  iotClient.setDateTimeProvider(&dateTimeProvider);
  Serial.println("iot initialized");
}

void setup() {
  Serial.begin(115200);
  delay(10);
  initWLAN();
  initAWS();
  
  const size_t capacity = 5*JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(4) + 130;
  DynamicJsonBuffer jsonBuffer(capacity);

  const char* shadow = iotClient.get_shadow(actionError);
  
  JsonObject& root = jsonBuffer.parseObject(shadow);
  if (!root.success()) {
    Serial.println("parseObject() failed");
    
  }else{
    Serial.println("parseObject() success");
    
  }

  const char* feed = root["state"]["delta"]["feed"];
  Serial.print("Should feed? ");
  Serial.println(feed);

  if(feed && strcmp(feed,"true") ==0){
    servo.attach(2); //D4
    Serial.println("Time to feed");
    servo.write(180);
    delay(1500);
    servo.write(0);
    delay(1500);
    servo.detach();
    char* sendReport = "{\"state\":{\"reported\": {\"feed\": \"true\"}}}";
    char* result = iotClient.update_shadow(sendReport, actionError);
    Serial.println(result);
    Serial.println("Shadow state updated");
    
    
  }else{
    Serial.println("Don't feed");
  }
  
  
  ESP.deepSleep(3480e6, WAKE_RF_DEFAULT); //30 seconds

}

void loop() {
  //never comes here 
}
