//===============================================
//PIN1  GND 接0V
//PIN2  VCC 接4.8V-5V
//PIN3  V0  对地接电阻470-2K
//PIN4  RS RS=0，指令寄存器；RS=1，数据寄存器
//PIN5  R/W R/W=0，写；R/W=1，读
//PIN6  E  允许信号
//PIN7  D0 数据0
//PIN8  D1 数据1
//PIN9  D2 数据2
//PIN10 D3 数据3
//PIN11 D4 数据4
//PIN12 D5 数据5
//PIN13 D6 数据6
//PIN14 D7 数据7
//PIN15 LED+ 背光正极，接4.8V - 5V
//PIN16 LED- 背光负极，接0V
//LiquidCrystal(rs,rw,enable,d0,d1,d2,d3);
//LiquidCrystal(rs,rw,enable,d4,d5,d6,d7);
//===============================================

#include <LiquidCrystal.h>
LiquidCrystal lcd(3, 4, 5, 6, 7, 8, 9);
int Button = 6;
String t1 = "";
String t2 = "";
String t3 = "";
int n = 0;
int SerialKey = 0;
long SerialBtl[] = {115200, 57600, 38400, 19200, 9600, 4800};

void setup() {
  lcd.begin(16, 2);//columns rows
  lcd.print("LCD start...!");
  Serial.begin(115200);
  pinMode(Button, INPUT);
}

void loop() {
  //--------------------------------------------------------
  if (digitalRead(Button) == HIGH) {
    ButtonClick();
    delay(600);
  }
  //--------------------------------------------------------
  while (Serial.available() > 0) {
    char inChar = Serial.read();
    if (inChar == '\r') {
      t2 = t1;
      t1 = "";
      lcd_show_t();
    } else {
      t1 += inChar;
    }
  }
  //--------------------------------------------------------
}

void lcd_show_t() {
  //--------------------------------------------------------
  t2.trim();
  //--------------------------------------------------------
  lcd.clear();
  //--------------------------------------------------------
  lcd.setCursor(0, 0);
  lcd.print(t2);
  n = t2.length();
  //--------------------------------------------------------
  if (n > 16) {
    t3 = t2.substring(16, n);
    lcd.setCursor(0, 1);
    lcd.print(t3);
  }
  //--------------------------------------------------------
}

void ButtonClick() {
  //--------------------------------------------------------
  SerialKey++;
  if (SerialKey > 5)SerialKey = 0;
  //--------------------------------------------------------
  Serial.begin(SerialBtl[SerialKey]);
  //--------------------------------------------------------
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Serial BaudRate:");
  lcd.setCursor(0, 1);
  lcd.print(SerialBtl[SerialKey]);
  //--------------------------------------------------------
}
