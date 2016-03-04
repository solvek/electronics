#include <EtherCard.h>
#include <SFE_BMP180.h>
#include <Wire.h>
#include "DHT.h"

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

#define CO2PIN A0
#define DHTPIN 2

#define DHTTYPE DHT11

int runId, sensorValue=-1, temperature, humidity;
double pressure, temperature2;

DHT dht(DHTPIN, DHTTYPE);
SFE_BMP180 bmp;

void setup() {
  Serial.begin(57600);

  randomSeed(analogRead(2));  
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
  
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP180 sensor, check wiring!");
  }

  dht.begin();
}

void loop() {
  delay(5000);
  
  readCO2();
  readDht11();
  readBmp180();
 
  String s = String("meteostationZ");
  s.concat(runId);
  s.concat(";");

  s.concat(sensorValue);
  s.concat(";");

  s.concat(temperature);
  s.concat(";");
  s.concat(humidity);
  s.concat(";");

  s.concat(temperature2);
  s.concat(";");
  s.concat(pressure);

  s.concat("Z");
  s.toCharArray(response, s.length()+1);

  Serial.print("String size: ");
  Serial.println(s.length());
  
  Serial.print("Sending to udp:");
  Serial.println(s);
    
  ether.sendUdp(response, s.length(), srcPort, ether.hisip, dstPort);   
}

const int TRIES = 10;

void readCO2()
{
   sensorValue = 0;
   analogRead(CO2PIN);
   for (int i = 0; i < TRIES; i++)
   {
     sensorValue += analogRead(CO2PIN);
     delay(20);
   }
   sensorValue /= TRIES;
}

void readDht11(){
    
  humidity = dht.readHumidity();
  if (isnan(humidity)) {
    humidity = 0;
    Serial.println("Failed to read humidity from DHT sensor!");
  }
  
  temperature = dht.readTemperature();
  if (isnan(temperature)) {
    temperature = 0;
    Serial.println("Failed to read temperature from DHT sensor!");
  }
}

void readBmp180(){
  char status = bmp.startTemperature();
  if (status == 0){
    Serial.println("error starting temperature measurement");
    return;
  }
  
  delay(status);
  
  status = bmp.getTemperature(temperature2);
  if (status == 0){
    Serial.println("error retrieving temperature measurement\n");
    return;
  }
  
  status = bmp.startPressure(3);
  if (status == 0){
    Serial.println("error starting pressure measurement\n");
    return;
  }
  
  delay(status);
  
  status = bmp.getPressure(pressure,temperature2);
  
  if (status == 0){
    Serial.println("error retrieving pressure measurement\n");
    return;
  } 
}
