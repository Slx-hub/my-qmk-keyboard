/*
 * USB Detection Test for Pro Micro
 * Blinks LED at different rates depending on USB connection status
 * 
 * - USB Connected: 1 second interval
 * - No USB: 0.5 second interval
 */

#include <avr/io.h>
#include <util/delay.h>

int RXLED = 17; // The RX LED has a defined Arduino pin
int TXLED = 30; // The TX LED has a defined Arduino pin

// USB detection
boolean hasUSB = false;

// ========== LED CONTROL ==========
void led_init(void) {
  if (hasUSB) {
    pinMode(RXLED, OUTPUT); // Set RX LED as an output
  } else {
    pinMode(TXLED, OUTPUT); // Set TX LED as an output
  }
}

// ========== USB DETECTION ==========
// Check if USB is connected using Serial
boolean check_usb(void) {
  // Method 1: Try Serial communication
  Serial.begin(115200);
  delay(1500);  // Wait for USB to enumerate
  
  // Check if Serial is ready (USB connected)
  if (Serial) {
    Serial.println("USB Detected!");
    return true;
  }
  
  return false;
}

void led_blink(uint16_t duration_ms) {
  if (hasUSB) {
    digitalWrite(RXLED, HIGH); // set the LED off
  } else {
    digitalWrite(TXLED, HIGH); // set the LED off
  }
  delay(duration_ms / 2);
  if (hasUSB) {
    digitalWrite(RXLED, LOW); // set the LED off
  } else {
    digitalWrite(TXLED, LOW); // set the LED off
  }
  delay(duration_ms / 2);
}

void setup() {
  // Detect USB connection first
  hasUSB = check_usb();
  
  // Initialize LED based on USB status
  led_init();
  
  if (hasUSB) {
    Serial.println("USB Connected - RX LED blinking at 1 second interval");
  }
}

void loop() {
  if (hasUSB) {
    led_blink(1000);
  } else {
    led_blink(500);
  }
}
