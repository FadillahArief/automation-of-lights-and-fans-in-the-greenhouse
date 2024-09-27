#include <DHT.h>
#include <Wire.h>
#include <BH1750.h>
#include <LiquidCrystal_I2C.h>

#define dhtPin D3
#define DHTTYPE DHT11

const int IN1 = D5;
const int IN2 = D6;

int temperature;
int lux;


DHT dht(dhtPin, DHTTYPE);
BH1750 lightMeter;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  dht.begin();
  Wire.begin();
  lightMeter.begin();
  lcd.init();
  lcd.backlight();
}

void dhtsensor(){
  temperature = dht.readTemperature();
  
  if (temperature > 30) {
    digitalWrite(IN1, LOW);
  }

  else{
    digitalWrite(IN1, HIGH);
  }
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("C"); 

}

void cahaya(){
  lux = lightMeter.readLightLevel();
  if (lux < 7500) {
    digitalWrite(IN2, LOW);
  }

  else {
    digitalWrite(IN2, HIGH);
  } 

  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx\n");
}

void layar(){
  temperature = dht.readTemperature();
  lux = lightMeter.readLightLevel();

  lcd.clear();
  lcd.setCursor(0, 0);  
  lcd.print("Temp: ");
  lcd.setCursor(5, 0);
  lcd.print(temperature);
  lcd.print((char)223);
  lcd.print("C");
  
  lcd.setCursor(0, 1); 
  lcd.print("Lux: ");
  lcd.setCursor(5, 1); 
  lcd.print(lux);
  lcd.print("lx");

}
void loop() {
  layar();
  dhtsensor();
  cahaya();
  delay(1000);
}
