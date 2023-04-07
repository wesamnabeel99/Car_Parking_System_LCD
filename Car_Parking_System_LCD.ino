#include <Servo.h> //includes the servo library
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

const int LCD_COLUMNS = 20;
const int LCD_ROWS = 4;

LiquidCrystal_I2C lcd(0x27,LCD_COLUMNS, LCD_ROWS);

Servo myservo;


#define servomotor 3

#define ir_enter 2
#define ir_back  4

#define ir_car1 5
#define ir_car2 6
#define ir_car3 7
#define ir_car4 8
#define ir_car5 9
#define ir_car6 10
#define ir_car7 11
#define ir_car8 12

int flag1=0, flag2=0;
int available_slots = 8;

void setup(){
  
  Serial.begin(9600);
  pinMode(ir_car1, INPUT);
  pinMode(ir_car2, INPUT);
  pinMode(ir_car3, INPUT);
  pinMode(ir_car4, INPUT);
  pinMode(ir_car5, INPUT);
  pinMode(ir_car6, INPUT);
  
  pinMode(ir_enter, INPUT);
  pinMode(ir_back, INPUT);

  myservo.attach(servomotor);
  myservo.write(90);  

  lcd.init();  
  lcd.backlight();

  lcd.setCursor (0,1);
  lcd.print("    Car  parking  ");
  lcd.setCursor (0,2);
  lcd.print("       System     ");
  delay (2000);
  
  lcd.clear(); 

}

void loop(){
  
  print_on_lcd(ir_car1,0,1,1);
  print_on_lcd(ir_car2,10,1,2);
  print_on_lcd(ir_car3,0,2,3);
  print_on_lcd(ir_car4,10,2,4);
  print_on_lcd(ir_car5,0,3,5);
  print_on_lcd(ir_car6,10,3,6);
  print_on_lcd(ir_car7,0,4,7);
  print_on_lcd(ir_car8,10,4,8);
  
  if(digitalRead (ir_enter) == 0 && flag1==0){
    if(available_slots>0){
      flag1=1;
      if(flag2==0){
        myservo.write(180); 
        available_slots = available_slots - 1;
        }
  } else{
    lcd.setCursor (0,0);
    lcd.print(" Sorry Parking Full ");  
    delay(1500);
    }   
  }
  
  if(digitalRead (ir_back) == 0 && flag2==0){
    flag2=1;
    if(flag1==0){myservo.write(180); available_slots = available_slots +1;}
  }
  
  if(flag1==1 && flag2==1){
    delay (1000);
    myservo.write(90);
    flag1=0, flag2=0;
  }
  
  delay(1);
}



void print_on_lcd(int car,int location_x, int location_y,int slot_number) {
  lcd.setCursor (location_x,location_y);
  lcd.print("s");
  lcd.print(slot_number);
  
  if(digitalRead(car) == 0){
      lcd.print(": Full");
    } else {
      lcd.print(": Empty");
    }  
}
