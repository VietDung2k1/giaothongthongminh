#include <ShiftRegister74HC595.h>
#include <Wire.h>
char c;
//ShiftRegister74HC595(const uint8_t serialDataPin, const uint8_t clockPin, const uint8_t latchPin);
//ShiftRegister74HC595(SDI, SCLK, LOAD);
ShiftRegister74HC595<2> sr(3, 2, 4);
ShiftRegister74HC595<2> sr2(6, 5, 7);
#define x1  8
#define d1  9
#define v1  10
#define x2  11
#define d2  12
#define v2  13
unsigned long time;
unsigned long time2;
unsigned long time3;
unsigned long time4;
int data = 0;
char dongbo;
int trangthaichophep = 0;
int xanh1 = 34, do1 = 39, vang1 = 4, xanh2 = 34, do2 = 39, vang2 = 4;
int xanh21 = 49, do21 = 24, vang21 = 4, xanh22 = 19, do22 = 54, vang22 = 4;
int xanh31 = 19, do31 = 54, vang31 = 4, xanh32 = 49, do32 = 24, vang32 = 4;
int value, digit1, digit2, digit3, digit4;
uint8_t numberB[] = {
    B11000000, //0
    B11111001, //1
    B10100100, //2
    B10110000, //3
    B10011001, //4
    B10010010, //5
    B10000100, //6
    B11111000, //7
    B10000000, //8
    B10010000  //9
};
void receiveEvent(int howMany) {
  while (0 < Wire.available()) {
    c = Wire.read();      /* receive byte as a character */
    Serial.print(c);           /* print the character */
  }
  Serial.println();             /* to newline */
}

// function that executes whenever data is requested from master
void requestEvent() {
  switch (c) {
    case '1':
    data = 1;
    Wire.write('1');
    break;
    case '2':
    data = 2;
    Wire.write('2');
    break;
    case '3':
    data = 3;
    Wire.write('3');
    break;
    case '4':
    if (trangthaichophep == 1){
      Wire.write('y');
      } else {
        Wire.write('n');} 
    break;
    case '5':
    dongbo = data + 48;
      Wire.write(dongbo);
    }
}
void setup()
{
    Wire.begin(8);/* join i2c bus with address 8 */
    Wire.onReceive(receiveEvent); /* register receive event */
    Wire.onRequest(requestEvent); /* register request event */
    Serial.begin(9600);           /* start serial for debug */
    pinMode(x1, OUTPUT);
    pinMode(d1, OUTPUT);
    pinMode(v1, OUTPUT);
    pinMode(x2, OUTPUT);
    pinMode(d2, OUTPUT);
    pinMode(v2, OUTPUT);
    time = millis();
    time2 = millis();
    time3 = millis();
    time4 = millis();
}
void loop()
{
  switch(data) {
  case 1:
    chuongtrinhdieukhien1();
    resetchuongtrinh2();
    resetchuongtrinh3();
    break;
  case 2:
    chuongtrinhdieukhien2();
    resetchuongtrinh1();
    resetchuongtrinh3();
    break;
  case 3:
    chuongtrinhdieukhien3();
    resetchuongtrinh1();
    resetchuongtrinh2(); 
    break; 
  default:
    Wire.write('1');
    chuongtrinhdieukhien1();
    resetchuongtrinh2();
    resetchuongtrinh3();
    break;
}
}
void timeline1(){
  trangthaichophep = 1;
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);}
  void timeline2(){
  trangthaichophep = 0;
  digitalWrite(x1, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(v1, HIGH);
  digitalWrite(x2, LOW);
  digitalWrite(d2, HIGH);
  digitalWrite(v2, LOW);}
  void timeline3(){
  trangthaichophep = 0;
  digitalWrite(x1, LOW);
  digitalWrite(d1, HIGH);
  digitalWrite(v1, LOW);
  digitalWrite(x2, HIGH);
  digitalWrite(d2, LOW);
  digitalWrite(v2, LOW);}
  void timeline4(){
  trangthaichophep = 0;
  digitalWrite(x1, LOW);
  digitalWrite(d1, HIGH);
  digitalWrite(v1, LOW);
  digitalWrite(x2, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(v2, HIGH);}

void hienthi(int a, int b){
  digit2 = a % 10;
  digit1 = (a / 10) % 10;
  digit4 = b % 10;
  digit3 = (b / 10) % 10;
  uint8_t numberToPrint[] = {numberB[digit1], numberB[digit2]};
  sr.setAll(numberToPrint);
  uint8_t numberToPrint2[] = {numberB[digit3], numberB[digit4]};
  sr2.setAll(numberToPrint2);
  }

  void chuongtrinhdieukhien1(){
  if ((unsigned long)(millis() - time) <= 8000){
    if ((unsigned long)(millis() - time) >= 0 && (unsigned long)(millis() - time) <=3500){
      hienthi(xanh1, do2);
      if ((unsigned long)(millis() - time2) > 100){
        xanh1 = xanh1-1;
        do2 = do2 -1;
        time2 = millis();}
      timeline1();
      } else if ((unsigned long)(millis() - time) > 3500 && (unsigned long)(millis() - time) <=4000){
        hienthi(vang1, do2);
      if ((unsigned long)(millis() - time2) > 100){
        vang1 = vang1-1;
        do2 = do2 -1;
        time2 = millis();}
        timeline2();
        } else if ((unsigned long)(millis() - time) > 4000 && (unsigned long)(millis() - time) <=7500){
          hienthi(do1, xanh2);
          if ((unsigned long)(millis() - time2) > 100){
        do1 = do1-1;
        xanh2 = xanh2 -1;
        time2 = millis();}
          timeline3();} else if ((unsigned long)(millis() - time) > 7500 && (unsigned long)(millis() - time) <=8000){
            hienthi(do1, vang2);
      if ((unsigned long)(millis() - time2) > 100){
        do1 = do1-1;
        vang2 = vang2 -1;
        time2 = millis();}
            timeline4();}
    }
    if ((unsigned long)(millis() - time) > 8000){
      resetchuongtrinh1();
      time = millis();
      }
  }

  void chuongtrinhdieukhien2(){
  if ((unsigned long)(millis() - time3) <= 8000){
    if ((unsigned long)(millis() - time3) >= 0 && (unsigned long)(millis() - time3) <=5000){
      hienthi(xanh21, do22);
      if ((unsigned long)(millis() - time2) > 100){
        xanh21 = xanh21-1;
        do22 = do22 -1;
        time2 = millis();}
      timeline1();
      } else if ((unsigned long)(millis() - time3) > 5000 && (unsigned long)(millis() - time3) <=5500){
        hienthi(vang21, do22);
      if ((unsigned long)(millis() - time2) > 100){
        vang21 = vang21-1;
        do22 = do22 -1;
        time2 = millis();}
        timeline2();
        } else if ((unsigned long)(millis() - time3) > 5500 && (unsigned long)(millis() - time3) <=7500){
          hienthi(do21, xanh22);
          if ((unsigned long)(millis() - time2) > 100){
        do21 = do21-1;
        xanh22 = xanh22 -1;
        time2 = millis();}
          timeline3();} else if ((unsigned long)(millis() - time3) > 7500 && (unsigned long)(millis() - time3) <=8000){
            hienthi(do21, vang22);
      if ((unsigned long)(millis() - time2) > 100){
        do21 = do21-1;
        vang22 = vang22 -1;
        time2 = millis();}
        timeline4();}
    }
    if ((unsigned long)(millis() - time3) > 8000){
      resetchuongtrinh2();
      time3 = millis();
      }
  }
   void chuongtrinhdieukhien3(){
  if ((unsigned long)(millis() - time4) <= 8000){
    if ((unsigned long)(millis() - time4) >= 0 && (unsigned long)(millis() - time4) <=2000){
      hienthi(xanh31, do32);
      if ((unsigned long)(millis() - time2) > 100){
        xanh31 = xanh31-1;
        do32 = do32 -1;
        time2 = millis();}
      timeline1();
      } else if ((unsigned long)(millis() - time4) > 2000 && (unsigned long)(millis() - time4) <=2500){
        hienthi(vang31, do32);
      if ((unsigned long)(millis() - time2) > 100){
        vang31 = vang31-1;
        do32 = do32 -1;
        time2 = millis();}
        timeline2();
        } else if ((unsigned long)(millis() - time4) > 2500 && (unsigned long)(millis() - time4) <=7500){
          hienthi(do31, xanh32);
          if ((unsigned long)(millis() - time2) > 100){
        do31 = do31-1;
        xanh32 = xanh32 -1;
        time2 = millis();}
          timeline3();} else if ((unsigned long)(millis() - time4) > 7500 && (unsigned long)(millis() - time4) <=8000){
            hienthi(do31, vang32);
      if ((unsigned long)(millis() - time2) > 100){
        do31 = do31-1;
        vang32 = vang32 -1;
        time2 = millis();}
        timeline4();}
    }
    if ((unsigned long)(millis() - time4) > 8000){
      resetchuongtrinh3();
      time4 = millis();
      }
  }

  void resetchuongtrinh1(){
      xanh1 = 34;
      vang1 = 4;
      do1 = 39;
      xanh2 = 34;
      vang2 = 4;
      do2 = 39;
    }
    void resetchuongtrinh2(){
      xanh21 = 49;
      do21 = 24;
      vang21 = 4;
      xanh22 = 19;
      do22 = 54;
      vang22 = 4;
    }
    void resetchuongtrinh3(){
      xanh31 = 19;
      do31 = 54;
      vang31 = 4;
      xanh32 = 49;
      do32 = 24;
      vang32 = 4;
      }
