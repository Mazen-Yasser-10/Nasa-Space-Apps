#include <LiquidCrystal_I2C.h>

#define IR A0
int count = 0;
bool count_change = false;
#define reset_button 2

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  pinMode(reset_button,INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  int IR_value = analogRead(IR);
  if(IR_value < 400){
    count++;
    delay(1000);
    count_change = true;
  }
  if(count_change){
    lcd.clear();
    lcd.setCursor(8,0);
    lcd.print(count);
  }
  count_change = false;
  if(!digitalRead(reset_button)) 
    reset();
  delay(50);
}
void reset(){
  count = 0;
  lcd.clear();
  lcd.setCursor(8,0);
  lcd.print(count);
}