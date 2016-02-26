#include <EtherCard.h>
#include <Metro.h>
#include "dht11.h"
#include <SFE_BMP180.h>
#include <Wire.h>

#define STATIC 1  // set to 1 to disable DHCP (adjust myip/gwip values below)

#if STATIC
// ethernet interface ip address
static byte myip[] = { 192,168,1,150 };
// gateway ip address
static byte gwip[] = { 192,168,1,1 };
#endif

// ethernet mac address - must be unique on your network
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };

byte Ethernet::buffer[500]; // tcp/ip send and receive buffer

BufferFiller bfill;

#define CO2PIN A3

int runId, sensorValue=-1;
float temperature, humidity;

double pressure, temperature2;

float alpha = 0.96;

Metro co2Metro = Metro(10000); 

dht11 DHT11;

#define DHT11PIN 2

SFE_BMP180 bmp;

void setup() {
  Serial.begin(57600);

  randomSeed(analogRead(0));  
  runId = random(0,100000);
  
  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) 
    Serial.println( "Failed to access Ethernet controller");
#if STATIC
  ether.staticSetup(myip, gwip);
#else
  if (!ether.dhcpSetup())
    Serial.println("DHCP failed");
#endif

  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);  
  ether.printIp("DNS: ", ether.dnsip);
  
  if (!bmp.begin()) {
	Serial.println("Could not find a valid BMP180 sensor, check wiring!");
  }
}

word len, pos;
void loop() {
  len = ether.packetReceive();
  pos = ether.packetLoop(len);
  
  if (pos)  // check if valid tcp data is received
    ether.httpServerReply(webResponse()); // send web page data
  
  if (co2Metro.check() == 1) {
    readCO2();
    readDh11();
    readBmp180();

    Serial.print("RunId: ");    
    Serial.print(runId);
    Serial.print(", co2 sensor:");
    Serial.println(sensorValue);
  }
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
  
  humidity = (float)DHT11.humidity;
  temperature = (float)DHT11.temperature;
  
  Serial.print("Humidity (%): ");
  Serial.print(humidity, 2);

  Serial.print(", Temperature (°C): ");
  Serial.println(temperature, 2);
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
  
  Serial.print("Temperature = ");
  Serial.print(temperature2);
  Serial.print(" *C, ");
  
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
  
  Serial.print("Pressure = ");
  Serial.print(pressure);
  Serial.println(" mb");  
}

static word webResponse() {
   Serial.println("Sending web response");
  
   bfill = ether.tcpOffset();
   bfill.emit_p(PSTR(
    "HTTP/1.0 200 OK\r\n"
    // "Content-Type: text/html\r\n"
    "Content-Type: application/json;charset=utf-8\r\n"
    "Pragma: no-cache\r\n"
    "\r\n"
//    "<meta http-equiv='refresh' content='1'/>"
//    "<title>CO2 server</title>" 
//    "<h1>$D;$D</h1>"),
     "{\"runId\":$D,\"co2\":$D,\"temperature\":$D,\"humidity\":$D,\"temperature2\":$D,\"pressure\":$D}"),
      runId, sensorValue,temperature,humidity,temperature2,pressure);
  return bfill.position();
}
