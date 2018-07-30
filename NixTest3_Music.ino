/* ニキシー管でゲッダン踊ってみた
  2011/11/xx  ノリで作る
  2011/12/11  エレコン前にネカフェで修正

*/

// ニキシー管  コンスト
const int ledPin =  13;      // the number of the LED pin
const int NixA = 7;
const int NixB = 5;
const int NixC = 4;
const int NixD = 6;
//Nix用変数
int viewNo = 0;
int NixAstate = LOW;
int NixBstate = LOW;
int NixCstate = LOW;
int NixDstate = LOW;

// 変数定義
int ledState = LOW;             // Lチカ用変数
long interval = 1000;           // Lチカ用インターバル
long LEDpreviousMillis =0;      // Lチカ用 インターバル生成
long previousMillis = 0;        //ニキシー管用 インターバル生成
long startMillis = 0;           //ニキシー管用 スタート時間
long bpm = 452;                 //ニキシー管用 4分音符1つのms
int sensorPin = A0;            //光センサー ピンアサイン
int sensorValue  = 0;          //光センサー 取得値変数
int lastSensorValue  = 0;          //光センサー 取得値変数
int sensorPosition  = 0;          //光センサー 取得値変数
int sensorTimeup  = 0;            //光センサー タイムアップ
long SensorPreviousMillis = 0;    //光センサー インターバル生成

void setup() {
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);      
  pinMode(NixA, OUTPUT);
  pinMode(NixB, OUTPUT);
  pinMode(NixC, OUTPUT);
  pinMode(NixD, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  unsigned long currentMillis = millis();
 
 //Lチカ用ループ
  if(currentMillis - LEDpreviousMillis > interval) {
    LEDpreviousMillis = currentMillis;   

    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;
    digitalWrite(ledPin, ledState);
  }
  
//光センサー
  if(currentMillis - SensorPreviousMillis > 200 ){  // x msごとにしておく
    SensorPreviousMillis = currentMillis ;
  
    switch(sensorPosition){
      case 0:
        sensorValue = analogRead(sensorPin);
        if(sensorValue - lastSensorValue > 70){ 
          sensorPosition = 1;
          lastSensorValue = sensorValue;
          sensorTimeup = 5;  //次のタイムアップ x100ms
        }else{
          lastSensorValue = sensorValue;
        }
        break;
      case 1:
        sensorValue = analogRead(sensorPin);
        if(sensorValue - lastSensorValue < -100){ 
          sensorPosition = 2;
          lastSensorValue = sensorValue;
          sensorTimeup = 5;  //次のタイムアップ x100ms
        }else{
          sensorTimeup --;
          if(sensorTimeup <0) sensorPosition = 0;
        }
        break;
      case 2:
        sensorValue = analogRead(sensorPin);
        if(sensorValue - lastSensorValue > 100){ 
          sensorPosition = 3;
          lastSensorValue = sensorValue;
          sensorTimeup = 5;  //次のタイムアップ x100ms
        }else{
          sensorTimeup --;
          if(sensorTimeup <0) sensorPosition = 0;
        }
        break;
      case 3:
        sensorValue = analogRead(sensorPin);
        if(sensorValue - lastSensorValue < -100){ 
          sensorPosition = 4;
          lastSensorValue = sensorValue;
          sensorTimeup = 5;  //次のタイムアップ x100ms
        }else{
          sensorTimeup --;
          if(sensorTimeup <0) sensorPosition = 0;
        }
        break;
      case 4:
        sensorValue = analogRead(sensorPin);
        if(sensorValue - lastSensorValue > 70){ 
          sensorPosition = 5;
          lastSensorValue = sensorValue;
          sensorTimeup = 5;  //次のタイムアップ x100ms
        }else{
          sensorTimeup --;
          if(sensorTimeup <0) sensorPosition = 0;
        }
        break;
      case 5:
        sensorValue = analogRead(sensorPin);
        if(sensorValue - lastSensorValue < -100){ 
          sensorPosition = 6;
          lastSensorValue = sensorValue;
          sensorTimeup = 5;  //次のタイムアップ x100ms
        }else{
          sensorTimeup --;
          if(sensorTimeup <0) sensorPosition = 0;
        }
        break;
      case 6:
        sensorValue = analogRead(sensorPin);
        if(sensorValue - lastSensorValue > 100){ 
          sensorPosition = 7;
          lastSensorValue = sensorValue;
          sensorTimeup = 5;  //次のタイムアップ x100ms
        }else{
          sensorTimeup --;
          if(sensorTimeup <0) sensorPosition = 0;
        }
        break;
      case 7:
          delay(2000);
          sensorPosition = 0;
          lastSensorValue = sensorValue;
          startMillis = currentMillis + 2000;
          break;
        default:
        sensorPosition = 0;
        break;
    }
    
    Serial.println(sensorValue);
    Serial.println("SensorPosition = ");
    Serial.println(sensorPosition);
  }

//ニキシー管用ループ
  gedd();    //ゲッダンする


}

//ゲッダンを踊る
void gedd(){
  unsigned long currentMillis = millis();
  
  if(currentMillis - startMillis < bpm * 1){
    nix(0);
  }else if(currentMillis - startMillis < bpm * 2){
    nix(1);
  }else if(currentMillis - startMillis < bpm * 21 ){
    if(currentMillis - previousMillis > 10 ){
      previousMillis = currentMillis;
      nix(viewNo);
      viewNo++;
    }
  }else if(currentMillis - startMillis < bpm * 21.5 ){
    nix(9);
  }else if(currentMillis - startMillis < bpm * 22 ){
    nix(6);
  }else if(currentMillis - startMillis < bpm * 22.5 ){
    nix(9);
  }else if(currentMillis - startMillis < bpm * 23 ){
    nix(6);
  }else if(currentMillis - startMillis < bpm * 25 ){
    if(currentMillis - previousMillis > 10 ){
      previousMillis = currentMillis;
      nix(viewNo);
      viewNo++;
    }
  }else if(currentMillis - startMillis < bpm * 25.5 ){
    nix(9);
  }else if(currentMillis - startMillis < bpm * 26 ){
    nix(6);
  }else if(currentMillis - startMillis < bpm * 26.5 ){
    nix(9);
  }else if(currentMillis - startMillis < bpm * 27 ){
    nix(6);
  }else if(currentMillis - startMillis < bpm * 32 ){
    if(currentMillis - previousMillis > bpm /4 ){
      previousMillis = currentMillis;
      if(viewNo !=2){
        viewNo = 2;
        nix(viewNo);
      }else{
        viewNo = 7;
        nix(viewNo);
      }
    }
  }else if(currentMillis - startMillis < bpm * 33 ){
    nix(1);
  }else if(currentMillis - startMillis < bpm * 34 ){
    nix(2);
  }else if(currentMillis - startMillis < bpm * 35 ){
    nix(3);
  }else if(currentMillis - startMillis < bpm * 36 ){
    nix(4);
  }else if(currentMillis - startMillis < bpm * 55 ){
    if(currentMillis - previousMillis > 10 ){
      previousMillis = currentMillis;
      nix(viewNo);
      viewNo++;
    }
  }else if(currentMillis - startMillis < bpm * 55.5 ){
    nix(9);
  }else if(currentMillis - startMillis < bpm * 56 ){
    nix(6);
  }else if(currentMillis - startMillis < bpm * 56.5 ){
    nix(9);
  }else if(currentMillis - startMillis < bpm * 57 ){
    nix(6);
  }else if(currentMillis - startMillis < bpm * 59 ){
    if(currentMillis - previousMillis > 10 ){
      previousMillis = currentMillis;
      nix(viewNo);
      viewNo++;
    }
  }else if(currentMillis - startMillis < bpm * 59.5 ){
    nix(9);
  }else if(currentMillis - startMillis < bpm * 60 ){
    nix(6);
  }else if(currentMillis - startMillis < bpm * 60.5 ){
    nix(9);
  }else if(currentMillis - startMillis < bpm * 61 ){
    nix(6);
  }else if(currentMillis - startMillis < bpm * 66 ){
    if(currentMillis - previousMillis > bpm /4 ){
      previousMillis = currentMillis;
      if(viewNo !=2){
        viewNo = 2;
        nix(viewNo);
      }else{
        viewNo = 7;
        nix(viewNo);
      }
    }
  }else if(currentMillis - startMillis < bpm * 67 ){
    nix(1);
  }else if(currentMillis - startMillis < bpm * 68 ){
    nix(2);
  }else if(currentMillis - startMillis < bpm * 69 ){
    nix(3);
  }else if(currentMillis - startMillis < bpm * 70 ){
    nix(4);
  }else if(currentMillis - startMillis < bpm * 79 ){
    if(currentMillis - previousMillis > 10 ){
      previousMillis = currentMillis;
      nix(viewNo);
      viewNo++;
    }
  }else if(currentMillis - startMillis < bpm * 87 ){
    nix(9);
  }else if(currentMillis - startMillis < bpm * 88 ){
    nix(3);
  }else if(currentMillis - startMillis < bpm * 89 ){
    nix(2);
  }else if(currentMillis - startMillis < bpm * 93 ){
    nix(1);
  }else{
    startMillis = currentMillis;
  }
}

//digitに入力された値をシールドに出力する
void nix(int digit){
      switch (digit){
      case 0:
        NixAstate = LOW;
        NixBstate = LOW;
        NixCstate = HIGH;
        NixDstate = LOW;
        break;
      case 1:
        NixAstate = LOW;
        NixBstate = HIGH;
        NixCstate = LOW;
        NixDstate = LOW;
        break;
      case 2:
        NixAstate = HIGH;
        NixBstate = HIGH;
        NixCstate = LOW;
        NixDstate = LOW;
        break;
      case 3:
        NixAstate = HIGH;
        NixBstate = HIGH;
        NixCstate = HIGH;
        NixDstate = LOW;
        break;
      case 4:
        NixAstate = LOW;
        NixBstate = HIGH;
        NixCstate = HIGH;
        NixDstate = LOW;
        break;
      case 5:
        NixAstate = HIGH;
        NixBstate = LOW;
        NixCstate = HIGH;
        NixDstate = LOW;
        break;
      case 6:
        NixAstate = HIGH;
        NixBstate = LOW;
        NixCstate = LOW;
        NixDstate = LOW;
        break;
      case 7:
        NixAstate = HIGH;
        NixBstate = LOW;
        NixCstate = LOW;
        NixDstate = HIGH;
        break;
      case 8:
        NixAstate = LOW;
        NixBstate = LOW;
        NixCstate = LOW;
        NixDstate = LOW;
        break;
      case 9:
        NixAstate = LOW;
        NixBstate = LOW;
        NixCstate = LOW;
        NixDstate = HIGH;
        break;
      default :
        viewNo = 0;
        break;
    }
//output
    digitalWrite(NixA, NixAstate);
    digitalWrite(NixB, NixBstate);
    digitalWrite(NixC, NixCstate);
    digitalWrite(NixD, NixDstate);
}

