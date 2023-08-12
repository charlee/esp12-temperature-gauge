#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTTYPE DHT11
#define DHTPIN 14       // D5


DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);


uint32_t delayMS;
char line1[16];
char line2[16];

void setup() {
  
  Serial.begin(115200);
  dht.begin();
  lcd.init();
  lcd.backlight();
  Serial.println("Temperature Gauge start");
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  
  sprintf(line1, "Temp:    %.1f" "\xDF" "C", t);
  sprintf(line2, "Humidity: %.1f%%", h);
  
  Serial.println(line1);
  Serial.println(line2);
  
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}