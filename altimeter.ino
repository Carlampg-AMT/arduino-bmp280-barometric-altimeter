
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <LiquidCrystal_I2C.h>
#include <math.h>

// ===== COMPONENTS =====
LiquidCrystal_I2C lcd(0x27, 16, 2);
Adafruit_BMP280 bmp;

// ===== KY-040 PINS =====
const byte CLK_PIN = 2;
const byte DT_PIN  = 3;
const byte SW_PIN  = 4;

// ===== QNH SETTINGS =====
float qnh = 1013.2;
float qnhStep = 0.1;

// Store QNH in tenths to avoid floating-point
// display and rounding problems.
int qnhTenths = 10132;
const int QNH_MIN = 9500;
const int QNH_MAX = 10500;

// ===== PRESSURE AVERAGING =====
const byte N = 10;
float samples[N];
byte sampleIndex = 0;
byte sampleCount = 0;
float pressureSum = 0;

// ===== ENCODER =====
int lastCLK;
bool lastButton = HIGH;
unsigned long lastButtonTime = 0;

// ===== TIMERS =====
unsigned long lastSample = 0;
unsigned long lastDisplay = 0;

// ===== SETUP =====
void setup() {
  Serial.begin(9600);
  Wire.begin();

  pinMode(CLK_PIN, INPUT_PULLUP);
  pinMode(DT_PIN, INPUT_PULLUP);
  pinMode(SW_PIN, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Aircraft Alt.");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");

  bool bmpOK = bmp.begin(0x76);
  if (!bmpOK) {
    bmpOK = bmp.begin(0x77);
  }

  if (!bmpOK) {
    lcd.clear();
    lcd.print("BMP280 ERROR!");
    lcd.setCursor(0, 1);
    lcd.print("Check wiring");

    Serial.println("BMP280 not detected.");
    while (true) {
      delay(100);
    }
  }

  bmp.setSampling(
    Adafruit_BMP280::MODE_NORMAL,
    Adafruit_BMP280::SAMPLING_X2,
    Adafruit_BMP280::SAMPLING_X16,
    Adafruit_BMP280::FILTER_X16,
    Adafruit_BMP280::STANDBY_MS_500
  );

  lastCLK = digitalRead(CLK_PIN);

  delay(1200);
  lcd.clear();

  Serial.println("BMP280 Altimeter ready");
  Serial.println("QNH starts at 1013.2 hPa");
}

// ===== MAIN LOOP =====
void loop() {
  readEncoder();
  readButton();

  if (millis() - lastSample >= 200) {
    lastSample = millis();

    float p = bmp.readPressure() / 100.0;

    if (p > 300.0 && p < 1100.0) {
      if (sampleCount == N) {
        pressureSum -= samples[sampleIndex];
      } else {
        sampleCount++;
      }

      samples[sampleIndex] = p;
      pressureSum += p;

      sampleIndex = (sampleIndex + 1) % N;
    }
  }

  if (millis() - lastDisplay >= 500 &&
      sampleCount > 0) {
    lastDisplay = millis();
    updateDisplay();
  }
}

// ===== ROTARY ENCODER =====
void readEncoder() {
  int clk = digitalRead(CLK_PIN);

  if (clk != lastCLK && clk == LOW) {
    if (digitalRead(DT_PIN) != clk) {
      qnhTenths++;
    } else {
      qnhTenths--;
    }

    qnhTenths = constrain(
      qnhTenths, QNH_MIN, QNH_MAX
    );

    qnh = qnhTenths / 10.0;
  }

  lastCLK = clk;
}

// ===== BUTTON =====
void readButton() {
  bool button = digitalRead(SW_PIN);

  if (lastButton == HIGH &&
      button == LOW &&
      millis() - lastButtonTime > 250) {

    lastButtonTime = millis();

    if (qnhStep < 0.5) {
      qnhStep = 1.0;
    } else {
      qnhStep = 0.1;
    }

    Serial.print("QNH adjustment step: ");
    Serial.print(qnhStep, 1);
    Serial.println(" hPa");
  }

  lastButton = button;
}

// ===== DISPLAY =====
void updateDisplay() {
  float actualPressure = pressureSum / sampleCount;
  float temperatureC = bmp.readTemperature();

  qnh = qnhTenths / 10.0;

  float altitudeM = 44330.0 *
    (1.0 - pow(actualPressure / qnh, 0.19029495));

  float altitudeFt = altitudeM * 3.28084;

  // Row 1: Altitude and temperature
  lcd.setCursor(0, 0);
  lcd.print("A:");
  lcd.print(altitudeFt, 0);
  lcd.print("ft T:");
  lcd.print(temperatureC, 1);
  lcd.print("C ");

// Row 2: Pressure and QNH
int whole = qnhTenths / 10;
int decimal = abs(qnhTenths % 10);

lcd.setCursor(0, 1);
lcd.print("                "); // Clear all 16 characters
lcd.setCursor(0, 1);

lcd.print("P");
lcd.print(actualPressure, 1);
lcd.print(" Q");
lcd.print(whole);
lcd.print('.');
lcd.print(decimal);

  // Serial Monitor
  Serial.print("Altitude: ");
  Serial.print(altitudeFt, 1);
  Serial.print(" ft | Temp: ");
  Serial.print(temperatureC, 1);
  Serial.print(" C | Pressure: ");
  Serial.print(actualPressure, 2);
  Serial.print(" hPa | QNH: ");
  Serial.print(whole);
  Serial.print('.');
  Serial.print(decimal);
  Serial.println(" hPa");
}
