#define IN 2 
#define OUT 3
#define coi 11
#define den 10
double quangduong = 0.5;//khoảng cách hai cảm biến ; //Đơn vị mét
double thoigian = 0;
double vantoc = 0;
long time;
int i = 0;
int canhbao = 70.0;
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
void batdau() {
  time = millis();
}
void ketthuc() {
    thoigian = (millis() - time); //tính thời gian xe chạy đơn vị giây
}
void setup() {
  Serial.begin(9600);
  pinMode(IN, INPUT_PULLUP); // sử dụng điện trở kéo lên cho chân số 2, ngắt 0
  attachInterrupt(0, batdau, FALLING); // gọi hàm tatled liên tục khi còn nhấn nút
  pinMode(OUT, INPUT_PULLUP); // sử dụng điện trở kéo lên cho chân số 2, ngắt 0
  attachInterrupt(1, ketthuc, FALLING); // gọi hàm tatled liên tục khi còn nhấn nút
  lcd.init();                      // initialize the lcd
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" MAY DO TOC DO  ");
  lcd.setCursor(0, 1);
  lcd.print("VAN TOC:  " + String(vantoc));
  pinMode(coi, OUTPUT);
  pinMode(den, OUTPUT);
}

void loop() {
  if(thoigian >0){
  vantoc = (quangduong / (thoigian/1000.0))*3.6;//đổi m/s sang km/h
  }
  Serial.println("VAN TOC HIEN TAI LA: " + String(vantoc));
  lcd.setCursor(0, 0);
  lcd.print(" MAY DO TOC DO  ");
  lcd.setCursor(0, 1);
  lcd.print("V:          Km/h");
  lcd.setCursor(4, 1);
  lcd.print(vantoc);
  if(vantoc >= canhbao){
    digitalWrite(coi, HIGH);
    digitalWrite(den, HIGH);
  }
  else {
    digitalWrite(coi, LOW);
    digitalWrite(den, LOW);
  }
  delay(100);
}
