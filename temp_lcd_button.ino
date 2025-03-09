#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define BUTTON_PIN 3

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

bool lastButtonState = LOW;
bool buttonState = LOW;
bool isMeasuring = false;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("Click button");
  delay(2000);
  lcd.clear();
}

void loop() {
  buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == HIGH && lastButtonState == LOW) {
    delay(50);
    lastButtonState = buttonState;

    isMeasuring = !isMeasuring;
    if (isMeasuring) {
      showMeasurementProcess();
    } else {
      lcd.clear();
      lcd.print("Pomiar.");
      delay(1000);
      lcd.clear();
      int temp = dht.readTemperature();
      if (isnan(temp)) {
        lcd.print("Blad pomiaru!");
      } else {
        lcd.print("Temp:");
        lcd.setCursor(5, 0);
        lcd.print(temp);
        lcd.print(" C");
      }
    }
  }

  lastButtonState = buttonState;
}

void showMeasurementProcess() {
  for (int i = 0; i < 3; i++) {
    lcd.clear();
    lcd.print("Pomiar.");
    for (int j = 1; j <= i; j++) {
      lcd.print(".");
      delay(500);
    }
  }
  delay(500);
}