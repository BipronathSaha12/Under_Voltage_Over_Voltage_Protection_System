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
#include <Filters.h> 
#include <LiquidCrystal_I2C.h>

// Define the pin numbers for the LCD
const int rs = 3, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8;

// Create an instance of the LiquidCrystal class with the specified pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

float testFrequency = 50;  // Test frequency (not used in this code)

int sensor = 0; // Variable to store the sensor reading
int relay = 10; // Pin number for the relay control
int yellow = 12; // Pin number for the yellow LED
int green = 11; // Pin number for the green LED

float intercept = 0.7; // Intercept value for voltage calculation
float slope = 0.04; // Slope value for voltage calculation
float current_Volts; // Variable to store the current voltage

unsigned long printPeriod = 1000; // Time period for printing voltage (in milliseconds)
unsigned long previousMillis = 0; // Stores the last time the voltage was printed

void setup() {
    lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows
    pinMode(relay, OUTPUT); // Set the relay pin as an output
    pinMode(yellow, OUTPUT); // Set the yellow LED pin as an output
    pinMode(green, OUTPUT); // Set the green LED pin as an output
    lcd.print("Voltage:"); // Print "Voltage:" on the LCD
    delay(1000); // Wait for 1 second
}

void loop() {
    RunningStatistics inputStats; // Create a RunningStatistics object to calculate statistics on the input

    while (true) {
        sensor = analogRead(A0); // Read the analog value from pin A0
        inputStats.input(sensor); // Input the sensor value into the RunningStatistics object

        if ((unsigned long)(millis() - previousMillis) >= printPeriod) { // Check if it's time to print the voltage
            previousMillis = millis(); // Update the previousMillis variable to the current time

            // Calculate the current voltage using the intercept and slope
            current_Volts = intercept + slope * inputStats.sigma(); 
            current_Volts = current_Volts * (40.3231); // Convert to the actual voltage value

            lcd.setCursor(9, 0); // Set the cursor to the appropriate position on the LCD
            lcd.print(current_Volts); // Print the current voltage on the LCD
            lcd.print("V"); // Print the unit 'V' for voltage
        }

        // Check if the voltage is under the specified range
        if ((current_Volts > 0) && (current_Volts < 190)) {
            lcd.setCursor(0, 1); // Set the cursor to the second row on the LCD
            lcd.print("Under Voltage"); // Print "Under Voltage" on the LCD
            digitalWrite(relay, LOW); // Turn off the relay
            digitalWrite(yellow, LOW); // Turn off the yellow LED
            digitalWrite(green, HIGH); // Turn on the green LED
        }

        // Check if the voltage is within the normal range
        if ((current_Volts >= 190) && (current_Volts <= 220)) {
            lcd.setCursor(0, 1); // Set the cursor to the second row on the LCD
            lcd.print("Normal Voltage"); // Print "Normal Voltage" on the LCD
            digitalWrite(relay, HIGH); // Turn on the relay
            digitalWrite(yellow, LOW); // Turn off the yellow LED
            digitalWrite(green, LOW); // Turn off the green LED
        }

        // Check if the voltage is over the specified range
        if (current_Volts > 220) {
            lcd.setCursor(0, 1); // Set the cursor to the second row on the LCD
            lcd.print("Over Voltage"); // Print "Over Voltage" on the LCD
            digitalWrite(relay, LOW); // Turn off the relay
            digitalWrite(yellow, HIGH); // Turn on the yellow LED
            digitalWrite(green, LOW); // Turn off the green LED
        }
    }
} 
