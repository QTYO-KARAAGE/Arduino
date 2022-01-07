//LCDディスプレイを使用するためのライブラリの読み込み
#include <LiquidCrystal.h>
//目標距離の設定
double KYORI = 121.0;

//超音波センサの設定
int TRIG = 0;
int ECHO = 8;

//LEDの初期化
int RED = 1;
int YELLOW = 2;
int GREEN = 3;

//値の初期化
double duration = 0;
double distance = 0;
double diff_dis = 0;

//LCDディスプレイの初期化
LiquidCrystal lcd( 4, 6, 10, 11, 12, 13 );

//超音波センサで用いる音速の設定
//"21"の部分が当日の温度になるように設定すること
double speed_of_sound = 331.5 + 0.6 * 21;

void setup() {
  //超音波センサのピンの操作
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
  //LEDのピンの操作
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  //LCDディスプレイの操作
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
  
  double ABS = 0.0;
  
  //超音波センサの操作
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  duration = pulseIn(ECHO, HIGH);
 
  if(duration > 0){
    //距離の計算
    duration = duration / 2;
    distance = duration * speed_of_sound * 100 / 1000000;
    
    //目標距離と測定距離の絶対値を算出
    if(KYORI - distance >= 0.0){
      ABS = KYORI - distance;
  }
    else {
      ABS = distance - KYORI;
  }
  
  //LEDの処理
    //絶対値が3cm未満になった時に点滅する
  if (ABS <= 3.0){
      digitalWrite(GREEN, HIGH);
      delay(500);
    }
    else {
      digitalWrite(GREEN, LOW);
    }
    //絶対値が20cm未満かつ3cm以上になった時に点滅する
  if (ABS <= 20.0 && ABS > 3.0){
      digitalWrite(YELLOW, HIGH);
      delay(500);
    }
    else{
        digitalWrite(YELLOW, LOW);
    }
    //絶対値が20cm以上になった時に点滅する
    if (ABS > 20.0){
        digitalWrite(RED, HIGH);
      delay(500);
    }
    else{
      digitalWrite(RED, LOW);
    }
    //LEDの後処理
    digitalWrite(GREEN, LOW);
    digitalWrite(YELLOW, LOW);
    digitalWrite(RED, LOW);
    
    //LCDディスプレイに出力
    lcd.setCursor(0, 0);
    lcd.print(distance);
    lcd.print("cm");

  }
}
