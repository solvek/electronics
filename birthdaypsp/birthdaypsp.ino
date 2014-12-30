#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);           // select the pins used on the LCD panel

bool psp = false;

char PSP_LINE1[] = "Happy Birthday";
char PSP_LINE2[] = "PSP PSP PSP";
char XUILO_LINE1[] = "  Putin Xuilo";
char XUILO_LINE2[] = "LA LA LA LA";

void setup(){
   lcd.begin(16, 2);
   init(XUILO_LINE1);
}
 
void loop(){
  if (analogRead(0) <= 50) {
    psp = !psp;
    if (psp) {
      init(PSP_LINE1);
    }
    else {
      init(XUILO_LINE1);
    }
  }
  for(int i=10;i>=0;i-=2){
    lcd.setCursor(0,1);
    lcd.print("                ");    
    lcd.setCursor(i,1);
    if (psp){
     lcd.print(PSP_LINE2);
    }
    else {
      lcd.print(XUILO_LINE2);
    }
    delay(500);
  }
}

void init(char text[]){
  lcd.clear();
  lcd.home();
  lcd.print(text);
}
