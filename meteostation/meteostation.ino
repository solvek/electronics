
#include <LiquidCrystal.h>
#include <LCDKeypad.h>
#include <EEPROM.h>

#define CO2PIN A3

LCDKeypad lcd;

const int default_da = 50;
const int default_db = 100;

int da, db;

const int ppmMin = 350;
const int ppmMax = 10000;

float m, n;

void setup() {
  Serial.begin(9600);  
  lcd.begin(16, 2);
  
  da = readWord(0);
   Serial.print("da: ");
   Serial.println(da);  
  if (da <= 0) da = default_da;
  db = readWord(2);
   Serial.print("db: ");
   Serial.println(db);  
  if (db <= da) db = max(default_db, da+20);
  
  prepareParams();
}

float volts;
int sensorValue, ppm, level;

void loop() {
   for (int i = 0; i < 4; i++)
   {
    sensorValue = analogRead(CO2PIN); 
    delay(20);
   }
   
   lcd.setCursor(0,0);
   lcd.print(repeat(' ', 16)); 
   lcd.setCursor(0,0);

   lcd.print("D"); 
   lcd.print(sensorValue);
   
//   volts = valueToVoltage(sensorValue, 1);
//   
//   lcd.print(" V"); 
//   lcd.print(volts);

   ppm = valueToPpm(sensorValue);   
   
   lcd.print(" C"); 
   lcd.print(ppm);   
  
   level = map(sensorValue, da, db, 16, 0);
//   Serial.print("Level1:");
//   Serial.println(level);
   level = constrain(level, 0, 16);
//   Serial.print("Level2:");
//   Serial.println(level);
      
  lcd.setCursor(0,1);
  lcd.print(repeat('#', level)+repeat(' ', 16-level));

  if (lcd.button()!=KEYPAD_NONE)
  {
    config();
  }
     
  delay(1000);
}

void config()
{
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Cofiguration");
   
    delay(50);
    while(lcd.button()!=KEYPAD_NONE)
    {
    }
    delay(50);
   
  
   int buttonPressed;
   
   for(;;)
   {
    lcd.setCursor(0,1);     
    lcd.print(repeat(' ', 16));
    lcd.setCursor(0,1);
    lcd.print(da);
    lcd.print(" - ");
    lcd.print(db);
    
    while((buttonPressed=lcd.button())==KEYPAD_NONE)
    {
    }
         
     if (buttonPressed == KEYPAD_RIGHT)
     {
       break;
     }
         
     if (buttonPressed==KEYPAD_SELECT)
     {
       da = da - 1;
     }
     
     if (buttonPressed==KEYPAD_LEFT)
     {
       da = da + 1;
     }     
     
     if (buttonPressed==KEYPAD_UP)
     {
       db = db + 1;
     }     
     
     if (buttonPressed==KEYPAD_DOWN)
     {
       db = db - 1;
     }          
     
     da = constrain(da, 0, 1023);
     db = constrain(db, da+1, 1023);
     
     delay(500);
   }
   writeWord(0, da);
   writeWord(2, db);
   
   prepareParams();
}

void prepareParams()
{
  m = pow(1.0*ppmMax/ppmMin, 1.0/(da - db));
  n = pow(m, -db)*ppmMin;
}  

String repeat(char symbol, int times){
  if (times == 0) return String("");
  String res = String(symbol);
  for(;res.length()<times;)
    res += symbol;
   return res;
}

int valueToPpm(int value)
{
  return n*pow(m, value);
}

float valueToVoltage(int value, int digits)
{
  float power = pow(10, digits);
  int v = 5.0*power*value/1024.0;
  return v/power;
}

int readWord(int address)
{
//  Serial.println("Reading...");  
//  int lo = (int)EEPROM.read(address);
//  int hi = (int)EEPROM.read(address+1) << 8;
//
//  Serial.print("Lo: ");
//  Serial.println(lo);
//  
//  Serial.print("Hi*256: ");
//  Serial.println(hi);    
//
//  Serial.print("Value: ");
//  Serial.println(lo | hi);      
  
  return (int)EEPROM.read(address) | (((int)EEPROM.read(address+1)) << 8);
}

void writeWord(int address, int w)
{
//  Serial.print("Writing: ");
//  Serial.println(w);
//  
//  byte lo = (byte)w;
//  byte hi = (byte)(w>>8);
//  
//  Serial.print("Lo: ");
//  Serial.println(lo);
//  
//  Serial.print("Hi: ");
//  Serial.println(hi);  
  
  EEPROM.write(address, (byte)w);
  EEPROM.write(address+1, (byte)(w>>8));
}
