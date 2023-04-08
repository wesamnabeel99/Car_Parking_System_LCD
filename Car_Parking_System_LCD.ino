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


int enter_flag=0, back_flag=0;

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

  int empty_slots =  digitalRead(ir_car1) +  digitalRead(ir_car2) + digitalRead(ir_car3) + digitalRead(ir_car4) + digitalRead(ir_car5) + digitalRead(ir_car6);
  
  lcd.setCursor (0,0);
  lcd.print("   Have Slot: "); 
  lcd.print(empty_slots);
  lcd.print("    ");  
  
  print_on_lcd(ir_car1,0,1,1);
  print_on_lcd(ir_car2,10,1,2);
  print_on_lcd(ir_car3,0,2,3);
  print_on_lcd(ir_car4,10,2,4);
  print_on_lcd(ir_car5,0,3,5);
  print_on_lcd(ir_car6,10,3,6);

  
  if(is_activated(ir_enter) && enter_flag==0){
    if(empty_slots > 0){
      enter_flag=1;
      if(back_flag==0){
        myservo.write(180); 
        }
  } else{
    lcd.setCursor (0,0);
    lcd.print(" Sorry Parking Full ");  
    delay(1500);
    }   
  }
  
  if(is_activated(ir_back)&& back_flag==0){
    back_flag=1;
    if(enter_flag == 0){myservo.write(180); }
  }
  
  if(enter_flag==1 && back_flag==1){
    delay (1000);
    myservo.write(90);
    enter_flag=0, back_flag=0;
  }
  
  delay(1);
}



void print_on_lcd(int car,int location_x, int location_y,int slot_number) {
  lcd.setCursor (location_x,location_y);
  lcd.print("s");
  lcd.print(slot_number);
  
  if(is_activated(car)){
      lcd.print(": Full ");
    } else {
      lcd.print(": Empty");
    }  
}

bool is_activated(int pin) {
  return digitalRead(pin) == 0;
}
