
float x = 0; //обьявление переменной и присвоение ей значения ноль
#include <TM74HC595Display.h> //библиотека индикатора
#include <EncButton.h>
//#include "button.h"

byte SCLK = 2; //присвоение выводов идикатора
byte RCLK = 3;
byte DIO = 4;
TM74HC595Display disp(SCLK, RCLK, DIO);
unsigned char SYM[19]; //создание массива значений
unsigned long dispIsrTimer, countTimer;

//Определение пинов под кнопки
const int PIN_BUTTON_1 = 5;
const int PIN_BUTTON_2 = 6;

void setup() {
  symbols();// обьявление пачки символов для работы дисплея
  Serial.begin(9600);
}

//Цикл
void loop(){

  tone(10, x);

  //Получения состояния кнопки 1
  int buttonState1 = digitalRead(PIN_BUTTON_1);
  //Получения состояния кнопки 2
  int buttonState2 = digitalRead(PIN_BUTTON_2);
  
  if (buttonState1){
    x += 50;
    delay(500);
    if (x > 1000){
      x = 0;
      disp.clear();
    }
  }

  if (buttonState2){
    x -= 50;
    delay(500);
    if (x > 1000){
      x = 0;
    }
    if (x < 0){
      x = 0;
      disp.clear();
    }
  }
  
  //Вывод значения x (частоты)
  Serial.println(x);
  
  //disp.float_dot(x, 0); //вывод значения икса на дисплей с точностью 1 знака после запятой
  disp.digit4(x);
  disp_isr();                         // динамическая индикация
}
void disp_isr() {
  if (micros() - dispIsrTimer > 300) {       // таймер динамической индикации
    disp.timerIsr();                         // "пнуть" дисплей
    dispIsrTimer = micros();                 // сбросить таймер
  }
}
// символы для дисплея
void symbols() {
  SYM[0] = 0xC0; //0
  SYM[1] = 0xF9; //1
  SYM[2] = 0xA4; //2
  SYM[3] = 0xB0; //3
  SYM[4] = 0x99; //4
  SYM[5] = 0x92; //5
  SYM[6] = 0x82; //6
  SYM[7] = 0xF8; //7
  SYM[8] = 0x80; //8
  SYM[9] = 0x90; //9
  SYM[10] = 0b01000000; //0.
  SYM[11] = 0b01111001; //1.
  SYM[12] = 0b00100100; //2.
  SYM[13] = 0b00110000; //3.
  SYM[14] = 0b00011001; //4.
  SYM[15] = 0b00010010; //5.
  SYM[16] = 0b00000010; //6.
  SYM[17] = 0b01111000; //7.
  SYM[18] = 0b00000000; //8.
  SYM[19] = 0b00010000; //9.
 

}
