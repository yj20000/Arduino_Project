#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#include <Servo.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
Servo myservo;
int angle=30;
float distance;
float duration;

void setup(){
  Serial.begin(9600);
  lcd.begin();
  lcd.clear();
  mlx.begin();
  myservo.attach(13);
  pinMode(8,OUTPUT);
  pinMode(9,INPUT);
  pinMode(10,OUTPUT);
}

void loop(){
  lcd.setCursor(0,0);
  digitalWrite(8,HIGH);
  delay(10);
  digitalWrite(8,LOW);
  long duration=pulseIn(9,HIGH);
  long distance=duration/58.2;

  if((distance>10)&&(mlx.readObjectTempC()>30))
  {
    //온도를 감지 하고 거리가 너무 멀 경우
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("COME CLOSER");
    delay(2000);
  }
  //거리가 10보다 작거나 같고 온도가 30보다 높고 100보다 작으면 정상 즉 실행되는 코드
  else if((distance<=10)&&(mlx.readObjectTempC()>30)&&(mlx.readObjectTempC()<100)){
    lcd.clear();
    angle=360;
    myservo.write(angle);
    angle=0;
    myservo.write(angle);
    lcd.setCursor(2,0); //2행 0열
    lcd.print("Temperature"); //Temperature 표시
    lcd.setCursor(6,1); //6행 1열
    lcd.print(mlx.readObjectTempC()); //측정 온도 표시
    lcd.setCursor(8,1); //8행 1열
    lcd.print("C"); //온도 단위 표시
    delay(2000);
  }
  //거리도 멀고 온도를 감지 못함
  else if((distance>10)&&(mlx.readObjectTempC()<30)&&(mlx.readObjectTempC()>100){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("ERROR");
    delay(2000);
  }
}
