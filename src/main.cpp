/*
 Basic MQTT example

 This sketch demonstrates the basic capabilities of the library.
 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic"
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary

 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.
 
*/

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <ArduinoUniqueID.h>

#include "LaserDetect.hpp"
#include "LEDAnimations.hpp"


//for messaging
EthernetClient ethClient;
PubSubClient client(ethClient);
String unique_id;

//for laser detecting
LaserDetect laser_detect(client);

// for leds
LEDAnimations led_animations;

// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(192,168,1,5);
IPAddress server(192, 168, 1, 112);



void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String topicstr(topic);
  if (topicstr.equals("windowon")) {
      led_animations.ledanimate(1);
      Serial.println("windowon msg");
  }

  if (topicstr.equals("windowoff")) {
      led_animations.ledanimate(0);
      
      Serial.println("windowoff msg");
  }
  
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}



void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClient")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      String hello = String("hello world:" + unique_id);

      client.publish("outTopic", hello.c_str());
      // ... and resubscribe
      client.subscribe("inTopic");
      client.subscribe("windowon");
      client.subscribe("windowoff");

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(9600);
  char outputBuffer[10];
  uint8_t i = 0;
  for (; i < UniqueIDsize; i++)
  {
      outputBuffer[i] = (char)UniqueID[i];
  }
  i;;
  outputBuffer[i] = 0;
  unique_id = String(outputBuffer);
  Serial.print("BOARD_ID:"); Serial.println(unique_id);


  client.setServer(server, 1883);
  client.setCallback(callback);

  Ethernet.begin(mac, ip);
  // Allow the hardware to sort itself out
  delay(1500);

  //leds
  led_animations.setup();
  //laser
  laser_detect.laser_init();


}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  laser_detect.laser_detect();
  led_animations.ledanimate();

}