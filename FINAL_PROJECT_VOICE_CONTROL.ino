 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
#include<AFMotor.h>

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR12_1KHZ);
AF_DCMotor motor4(4, MOTOR12_1KHZ);

int tx = 1;
int rx = 0;
  
char inSerial[15];
char command;

void setup()
{
  Serial.begin(9600); //Set the baud rate to your Bluetooth module.
  lcd.init();
  //lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows
  lcd.backlight(); // Turn on the backlight
}

void loop() {

  int i = 0;
  int m = 0
   ;
  delay(500);
  if (Serial.available() > 0) {
    while (Serial.available() > 0) {
      inSerial[i] = Serial.read();
      i++;
    }
    inSerial[i] = '\0';
    Check_Protocol(inSerial);
  }
}

void Check_Protocol(char inStr[]) {
  int i = 0;
  int m = 0;
  Serial.println(inStr);
  
  if (!strcmp(inStr, "*forward#")) {
    forward();
    delay(50);
    
    for (m = 0; m < 11; m++) {
      inStr[m] = 0;
    }
    i = 0;
  }

  if (!strcmp(inStr, "*back#")) {
    back();
    delay(50);
    
    for (m = 0; m < 11; m++) {
      inStr[m] = 0;
    }
    i = 0;
  }

  if (!strcmp(inStr, "*left#")) {
    left();
    delay(1000);
    
    for (m = 0; m < 11; m++) {
      inStr[m] = 0;
      Stop();
    }
    i = 0;
  }
  if (!strcmp(inStr, "*right#")) {
    right();
    delay(1000);
    Stop();
    
    for (m = 0; m < 11; m++) {
      inStr[m] = 0;
    }
    i = 0;
  }

  if (!strcmp(inStr, "*stop#")) {
    Stop();
    for (m = 0; m < 11; m++) {
      inStr[m] = 0;
    }
    i = 0;
  }

  else {
    for (m = 0; m < 11; m++) {
      inStr[m] = 0;
    }
    i = 0;

  }
}

void forward()
{
  lcd.clear();
  motor1.setSpeed(150);
  motor1.run(FORWARD);
  motor2.setSpeed(150);
  motor2.run(FORWARD);
  motor3.setSpeed(150);
  motor3.run(FORWARD);
  motor4.setSpeed(150);
  motor4.run(FORWARD);
  lcd.print("FORWARD");
  
}

void back()
{
  lcd.clear();
  motor1.setSpeed(150);
  motor1.run(BACKWARD);
  motor2.setSpeed(150);
  motor2.run(BACKWARD);
  motor3.setSpeed(150);
  motor3.run(BACKWARD);
  motor4.setSpeed(150);
  motor4.run(BACKWARD);
  lcd.print("BACKWARD");
}

void left()
{
  lcd.clear();
  motor1.setSpeed(255);
  motor1.run(FORWARD);
  motor2.setSpeed(150);
  motor2.run(FORWARD);
  motor3.setSpeed(0);
  motor3.run(RELEASE);
  motor4.setSpeed(0);
  motor4.run(RELEASE);
  lcd.print("LEFT");
}

void right()
{
  lcd.clear();
  motor1.setSpeed(0);
  motor1.run(RELEASE);
  motor2.setSpeed(0);
  motor2.run(RELEASE);
  motor3.setSpeed(255);
  motor3.run(FORWARD);
  motor4.setSpeed(255);
  motor4.run(FORWARD);
  lcd.print("RIGHT");
}

void Stop()
{
  lcd.clear();
  motor1.setSpeed(0);
  motor1.run(RELEASE);
  motor2.setSpeed(0);
  motor2.run(RELEASE);
  motor3.setSpeed(0);
  motor3.run(RELEASE);
  motor4.setSpeed(0);
  motor4.run(RELEASE);
  lcd.print("STOP");
}
