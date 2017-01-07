#include "ThingSpeak/ThingSpeak.h"

TCPClient client;

unsigned long myChannelNumber = 208736;  //ThingSpeak Channel ID
const char * myWriteAPIKey = "OD984ZG0ALD6LX5N";  //ThingSpeak Write API Key

int led = D7;  // The on-board LED

void setup() {

  pinMode(led, OUTPUT);
  
  Particle.function("SP", text);
  
  Particle.function("led",ledToggle);
  
  ThingSpeak.begin(client);
  
}

void loop() {

  int temp = random(20, 100);
  ThingSpeak.writeField(myChannelNumber, 1, temp, myWriteAPIKey);
  delay(20000);               // Wait for 20 seconds

}

int text(String array)
{
	Particle.publish("SP-return", array);
	return 1;	
}	

int ledToggle(String command)
{
	if (command == "on") {
		digitalWrite(led,HIGH);
		return 1;
	}
	else if (command == "off") {
		digitalWrite(led,LOW);
		return 0;
	}
	else {
		return -1;
	}
}