/*
Algorithm 
1. Initialize:
   - Include libraries: Filters.h, LiquidCrystal.h
   - Define constants for LCD pins, sensor pin, relay pin, and LED pins
   - Initialize LCD object with specified pins
   - Set initial parameters: intercept, slope, frequency, timing variables
2. Setup:
   - Initialize LCD with size 16x2
   - Set relay and LED pins as output
   - Display "Voltage:" on LCD
   - Delay for initial display
3. Main Loop:
   - Create RunningStatistics instance
   - Enter infinite loop
4. Read and Process Sensor Data:
   - Read analog data from sensor (A0)
   - Input sensor data into RunningStatistics
5. Periodic Voltage Display:
   - Check if elapsed time >= printPeriod
   - Update previousMillis to current time
   - Calculate current voltage using intercept, slope, and sigma()
   - Convert voltage to meaningful scale
6. Display Voltage on LCD:
   - Set cursor position on LCD
   - Print voltage value followed by "V"
7. Voltage Range Checking:
   - Under Voltage (0 < voltage < 190):
     - Display "Under Voltage" on LCD
     - Turn off relay and yellow LED
     - Turn on green LED
   - Normal Voltage (190 <= voltage <= 220):
     - Display "Normal Voltage" on LCD
     - Turn on relay
     - Turn off yellow and green LEDs
   - Over Voltage (voltage > 220):
     - Display "Over Voltage" on LCD
     - Turn off relay and green LED
     - Turn on yellow LED
 */
// code 
#include <LiquidCrystal_I2C.h>
#include <ZMPT101B.h>

#define SENSITIVITY 500.0f

// ZMPT101B sensor output connected to analog pin A0
// and the voltage source frequency is 50 Hz.
ZMPT101B voltageSensor(A0, 50.0);
// Pin configuration
const int voltageSensorPin = A0;  // Voltage sensor input
const int relayPin2 = 7;    // Relay module 2 control pin
const int greenLEDPin = 9;  // Green LED pin
const int redLEDPin = 10;   // Red LED pin

// LCD pin configuration: (RS, EN, D4, D5, D6, D7)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Thresholds for protection
const float overVoltageThreshold = 235.0;   // threshold in over volts
const float underVoltageThreshold = 220.0;  // threshold in under volts

void setup() {
  Serial.begin(9600);
  pinMode(voltageSensorPin, INPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);

  //lcd.begin();  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  lcd.print("Voltage: ");
  voltageSensor.setSensitivity(SENSITIVITY);
}

void loop() {
  int voltageNow =map(voltageSensor.getRmsVoltage(), 28, 620, 0, 220);
  //voltageNow=(voltageNow<0)? 0:voltageNow;
  lcd.setCursor(0, 1);
  lcd.print("          "); // Clear the previous voltage
  lcd.setCursor(0, 1);
  lcd.print(voltageNow);
  lcd.print("V");

  // Check voltage conditions and control relay and LEDs
  if (voltageNow > overVoltageThreshold) {
    // Over voltage
    digitalWrite(relayPin2, LOW);    // Turn off relay
    digitalWrite(greenLEDPin, LOW);  // Turn off green LED
    digitalWrite(redLEDPin, HIGH);   // Turn on red LED

    lcd.setCursor(9, 0);
    lcd.print("      ");  // Clear previous status
    lcd.setCursor(9, 0);
    lcd.print("OVER");

  } else if (voltageNow < underVoltageThreshold) {
    // Under voltage
    digitalWrite(relayPin2, LOW);    // Turn off relay
    digitalWrite(greenLEDPin, LOW);  // Turn off green LED
    digitalWrite(redLEDPin, HIGH);   // Turn on red LED

    lcd.setCursor(9, 0);
    lcd.print("      ");  // Clear previous status
    lcd.setCursor(9, 0);
    lcd.print("UNDER");

  } else {
    // Normal voltage
    digitalWrite(relayPin2, HIGH);   // Turn on relay
    digitalWrite(greenLEDPin, HIGH); // Turn on green LED
    digitalWrite(redLEDPin, LOW);    // Turn off red LED

    lcd.setCursor(9, 0);
    lcd.print("      ");  // Clear previous status
    lcd.setCursor(9, 0);
    lcd.print("NORMAL");
  }

  delay(500);
}
