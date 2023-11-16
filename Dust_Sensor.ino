/*

 Interfacing Sharp Optical Dust Sensor GP2Y1014AU0F with Arduino

*/
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#define measurePin  A0 //Connect dust sensor to Arduino A0 pin
#define ledPower  2   //Connect 3 led driver pins of dust sensor to Arduino D2
long sum;
int avgDustDensity;
int samplingTime = 280; // time required to sample signal coming out   of the sensor

int deltaTime = 40; // 
int sleepTime = 9680;
float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
void setup(){
 Serial.begin(9600);
 lcd.init();                      // initialize the lcd 
 lcd.init();
 lcd.backlight();
 lcd.setCursor(0,0);
 lcd.print("   HEXTRONICS  ");
 pinMode(ledPower,OUTPUT);
delay(2000);
lcd.clear();
}

void loop(){


 //////////////Averaging////////////////
 for(int i=0;i<100;i++){
    digitalWrite(ledPower,LOW); // power on the LED
  delayMicroseconds(samplingTime);
  voMeasured = analogRead(measurePin); // read the dust value
  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH); // turn the LED off
  delayMicroseconds(sleepTime);
  // 0 - 5V mapped to 0 - 1023 integer values
  calcVoltage = voMeasured * (5.0 / 1024.0);

  dustDensity = 170 * calcVoltage - 0.1;
  sum+=dustDensity;
 }
 avgDustDensity=sum/100;
  Serial.println(avgDustDensity); // unit: ug/m3
  sum=0;

  //delay(10);
//////////////LCD?////////
lcd.setCursor(0,0);
lcd.print("  Dust Density");
lcd.setCursor(3,1);
lcd.print(avgDustDensity);
lcd.print(" ug/m3 ");

}
