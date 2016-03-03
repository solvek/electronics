# Useful information

 * OpenHab default location: `/opt/openhab`
 * [OpenHab](http://www.openhab.org/getting-started/) starting: `./start_debug.sh`
 * [OpenHab url](http://localhost:8080) or [demo sitemap](http://localhost:8080/openhab.app?sitemap=demo)

# Used modules

![Wiring](/Meteostation_schem.png)

[Wiring in fritzing format](/Meteostation.fzz)

## Arduino UNO

##  Ethernet on chip ENC28J60

## CO2 Sensor TGS4161

![Module scheme](/TGS4161.jpg)

 * [Product information](/tgs4161.pdf)
 * [TGS4161 DataSheet](/TGS4161Dtl.pdf)

 This module can mesure [PPM](https://en.wikipedia.org/wiki/Parts-per_notation#ppm) ("parts per million" - co2 concentration value) from 350 to 10000 ppm. [Read](https://en.wikipedia.org/wiki/Carbon_dioxide#Toxicity) about CO2 toxity for humans.

 The dependency between actual ppm value and the voltage output provided by the sensor is exponential: `c=exp((v+a)/b)`, where

  * `c` - the concentration of co2 (in ppm)
  * `v` - sensor's output voltage *in millivolts* (pin `Aout`)
  * `a`, `b` - constants which have to be calibrated depending on specific sensor

  For arduino if `s` is signal then voltage `v` will be `v=(s*5000)/1024`. So having two different `v1` and `v2` and corresponding concentrations `c1` and `c2` we can find:

   * Let z1 = Ln(c1), z2 = Ln(c2), d=z1-z2
   * a = (v1*z2-v2*z1)/d
   * b = (v1-v2)/d

   [Calculation in instacalc](http://instacalc.com/40408)

## Temperature and humidity sensor [DHT11](http://playground.arduino.cc/Main/DHT11Lib)

![Module scheme](/dht11.jpg)

## Presure sensor BMP180
Can measure pressure, temperature and altitude.

[MMP180 Library](https://github.com/sparkfun/BMP180_Breakout_Arduino_Library)

![BMP180 wiring](/BMP180_pin_arduino.png)

## Voltage stabilizator LM7805CV. [Connection scheme](http://www.ruselectronic.com/news/stabilizatory-naprjazhjenija/)

![input/output](/lm7805.jpg)

# Used libraries

 * [EtherCard](http://jeelabs.org/pub/docs/ethercard/) ([sources](https://github.com/jcw/ethercard))
 * Library for timing [Metro](https://github.com/thomasfredericks/Metro-Arduino-Wiring)
