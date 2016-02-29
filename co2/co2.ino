#include <EtherCard.h>
#include "dht11.h"

//#define STATIC 1  // set to 1 to disable DHCP (adjust myip/gwip values below)
//
//#if STATIC
//// ethernet interface ip address
//static byte myip[] = { 192,168,1,150 };
//// gateway ip address
//static byte gwip[] = { 192,168,1,1 };
//#endif

// ethernet mac address - must be unique on your network
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };

byte Ethernet::buffer[500]; // tcp/ip send and receive buffer

const int dstPort PROGMEM = 1234;
const int srcPort PROGMEM = 4321;

char response[100];

#define CO2PIN A3

int runId, sensorValue=-1,temperature, humidity;

float alpha = 0.96;

dht11 DHT11;

#define DHT11PIN 2

void setup() {
  Serial.begin(57600);

  randomSeed(analogRead(0));  
  runId = random(0,10000);
  
  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) 
    Serial.println( "Failed to access Ethernet controller");
//#if STATIC
//  ether.staticSetup(myip, gwip);
//#else
//  if (!ether.dhcpSetup())
//    Serial.println("DHCP failed");
//#endif

  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);  
  ether.printIp("DNS: ", ether.dnsip);
}

word len, pos;
void loop() {
  delay(10*60*1000);
  
  readCO2();
  readDh11();

  Serial.print("RunId: ");    
  Serial.print(runId);
  Serial.print(", co2 sensor:");
  Serial.println(sensorValue);
  
  Serial.print("Humidity (%): ");
  Serial.print(humidity, 2);
  Serial.print(", Temperature (°C): ");
  Serial.println(temperature, 2);
  
  String s = String("meteostation;");
  s.concat(runId);
  s.concat(";");
  s.concat(sensorValue);
  s.concat(";");
  s.concat(temperature);
  s.concat(";");
  s.concat(humidity);
  s.toCharArray(response, s.length()+1);
  
  Serial.print("Sending to udp:");
  Serial.println(s);
    
  ether.sendUdp(response, s.length(), srcPort, ether.hisip, dstPort);   
}

void readCO2()
{
   for (int i = 0; i < 4; i++)
   {
     sensorValue = (sensorValue == -1) 
       ? analogRead(CO2PIN)
       : sensorValue*alpha + analogRead(CO2PIN)*(1-alpha);
     delay(20);
   }
}

void readDh11(){
  int chk = DHT11.read(DHT11PIN);

  Serial.print("Read dht11 sensor: ");
  switch (chk)
  {
    case DHTLIB_OK: 
		Serial.println("OK"); 
		break;
    case DHTLIB_ERROR_CHECKSUM: 
		Serial.println("Checksum error"); 
		break;
    case DHTLIB_ERROR_TIMEOUT: 
		Serial.println("Time out error"); 
		break;
    default: 
		Serial.println("Unknown error"); 
		break;
  }
  
  humidity = DHT11.humidity;
  temperature = DHT11.temperature;
}
