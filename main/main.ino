#include<WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <HTTPClient.h>
#include "ArduinoJson.h"

#define CLIENT_ID "****CLIENT_ID****"// thing unique ID, this id should be unique among all things associated with your AWS account.
#define MQTT_TOPIC "****MQTT_TOPIC****" //topic for the MQTT data
#define AWS_HOST "****AWS_HOST****" // your host for uploading data to AWS,

#define LED_BUILTIN 2
#define LIGHT 12

const char* ssid = "SSID";
const char* password = "PASSWORD";
char auth[] = "BLYNK_AUTH_KEY";

AWS_IOT aws;
int MQ2_sensorval, PIR_sensorval, temperature;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LIGHT, OUTPUT);

  Serial.begin(9600);

  //**** Connect to Wifi
  Serial.print("\n  Initializing WIFI: Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  Serial.print("  ");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\n  Initializing connection to Blynk....");
  Blynk.begin(auth, ssid, password);

  Serial.println("\n  Initializing connection to AWS....");
  if (aws.connect(AWS_HOST, CLIENT_ID) == 0) { // connects to host and returns 0 upon success
    Serial.println("  Connected to AWS\n  Done.");
  }
  else {
    Serial.println("  Connection failed!\n make sure your subscription to MQTT in the test page");
  }
  Serial.println("  Done.\n\nDone.\n");
}


void loop()
{
  Blynk.run();
  digitalWrite(LED_BUILTIN, HIGH);
  
  StaticJsonBuffer<300> JSONbuffer;
  JsonObject& status = JSONbuffer.createObject();

  MQ2_sensorval = MQ2();
  status["mq2"] = MQ2_sensorval;
  Blynk.virtualWrite(V3,MQ2_sensorval);
  if (MQ2_sensorval > 1500) {
    Blynk.notify("Gas Level too high. Please consider evacuating.");
  }

  PIR_sensorval = PIR();
  status["pir"] = PIR_sensorval;
  
  temperature = Weather();
  status["temperature"] = temperature;
    
  char JSONmessageBuffer[300];
  status.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));

  Serial.println("Publishing:- ");
  //Serial.println(payload);
  if (aws.publish(MQTT_TOPIC, JSONmessageBuffer) == 0) { // publishes payload and returns 0 upon success
    Serial.println("Success\n");
  }
  else {
    Serial.println("Failed!\n");
  }
  delay(2000);


}
