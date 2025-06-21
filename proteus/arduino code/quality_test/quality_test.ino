#include <LiquidCrystal.h>

#define TDS_PIN A0
#define TURBIDITY_ANALOG A1
#define TURBIDITY_DIGITAL 9
#define PH_PIN A2
#define CONDUCTIVITY_PIN A3
#define BUZZER_PIN 8

#define VREF 5.0
#define TDS_MAX_VOLTAGE 2.3
#define CONDUCTIVITY_THRESHOLD 1000
#define TURBIDITY_THRESHOLD 5.0  // NTU threshold

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  Serial.print("Welcome! Loading...");
  pinMode(TURBIDITY_DIGITAL, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  delay(1500);
}

void loop() {
  // --- Read TDS ---
  int tdsRaw = analogRead(TDS_PIN);
  float tdsVolt = tdsRaw * VREF / 1024.0;
  float tds = (tdsVolt * 1000.0) / TDS_MAX_VOLTAGE;

  // --- Read Conductivity ---
  int conductRaw = analogRead(CONDUCTIVITY_PIN);
  // float conductVolt = conductRaw * (5.0 / 1023.0);
  float conductivity = map(conductRaw, 0, 1023, 0, 2000);

  // --- Read Turbidity (Analog) ---
  int turbRaw = analogRead(TURBIDITY_ANALOG);
  float turbVolt = turbRaw * (5.0 / 1023.0);

  // Auto-scale mapping to work with actual Proteus range
  // Maps your actual ADC range to full 0-1000 NTU range
  // float turbidity = map(turbRaw, 0, 1023, 1000, 0);

  // Alternative: If you want to use voltage-based mapping with your actual range
  // Uncomment the line below and comment the map() line above
  float turbidity = ((4.0 - turbVolt) / 4.0) * 1000.0;  // Assumes 0-4V range

  // Constrain to valid range
  turbidity = constrain(turbidity, 0.0, 1000.0);

  // --- Read Turbidity (Digital) ---
  int turbDigital = digitalRead(TURBIDITY_DIGITAL);

  // --- Read pH ---
  int phReadings[10], temp;
  for (int i = 0; i < 10; i++) {
    phReadings[i] = analogRead(PH_PIN);
    delay(10);
  }
  for (int i = 0; i < 9; i++) {
    for (int j = i + 1; j < 10; j++) {
      if (phReadings[i] > phReadings[j]) {
        temp = phReadings[i];
        phReadings[i] = phReadings[j];
        phReadings[j] = temp;
      }
    }
  }
  long avgPH = 0;
  for (int i = 2; i < 8; i++) avgPH += phReadings[i];
  float phValue = 14 * (avgPH / 6.0) / 1023.0;

  // --- Threshold checks ---
  bool phAlert = (phValue < 6.5 || phValue > 8.5);
  bool tdsAlert = (tds > 500);
  bool conductAlert = (conductivity > CONDUCTIVITY_THRESHOLD); // Conductivity alert
  bool turbAnalogAlert = (turbidity > TURBIDITY_THRESHOLD);  // Analog turbidity alert
  bool turbDigitalAlert = (turbDigital == HIGH);             // Digital turbidity alert
  bool turbAlert = turbAnalogAlert || turbDigitalAlert;      // Combined turbidity alert
  bool alert = phAlert || conductAlert || tdsAlert || turbAlert;

  // --- Buzzer ---
  if (alert) tone(BUZZER_PIN, 1000);
  else noTone(BUZZER_PIN);

  // --- LCD Display ---
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("pH:");
  lcd.print(phValue, 1);
  lcd.print(phAlert ? " ALERT" : " OK");

  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.print(turbAlert ? "A" : "O");
  lcd.print(" D:");
  lcd.print(tdsAlert ? "A" : "O");

  // --- Serial Debug Info ---

  Serial.print("pH: ");
  Serial.print(phValue, 2);
  Serial.println(phAlert ? " (ALERT)" : " (OK)");
  Serial.print("TDS: ");
  Serial.print(tds, 1);
  Serial.println(tdsAlert ? " (ALERT)" : " (OK)");
  Serial.print("Turbidity Analog: ");
  Serial.print(turbidity, 1);
  Serial.print(" NTU");
  Serial.println(turbAnalogAlert ? " (ALERT)" : " (OK)");
  Serial.print("Turbidity Digital: ");
  Serial.println(turbDigital == HIGH ? "HIGH (Above threshold)" : "LOW (Normal)");
  
  Serial.print("Conductivity: ");
  Serial.print(conductivity, 1);
  Serial.print(" uS/cm");
  Serial.println(conductAlert ? " (ALERT)" : " (OK)");

  delay(1000);
}