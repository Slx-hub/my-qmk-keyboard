/*
 * I2C Communication Test for Split Keyboard
 * Tests master-slave communication over I2C (two wires: SDA + SCL)
 * 
 * Role automatically determined by USB connection:
 * - USB Connected = Master
 * - No USB = Slave
 * 
 * Wiring:
 * - Pin 2 (SDA) to Pin 2 (SDA) between both Pro Micros
 * - Pin 3 (SCL) to Pin 3 (SCL) between both Pro Micros
 * - 4.7kΩ pull-up resistor from SDA to VCC
 * - 4.7kΩ pull-up resistor from SCL to VCC
 * - GND to GND
 */

#include <Wire.h>

// I2C slave address
#define SLAVE_ADDRESS 0x32

// USB detection and master/slave role
boolean isMaster = false;

int RXLED = 17; // The RX LED has a defined Arduino pin
int TXLED = 30; // The TX LED has a defined Arduino pin

// Macro for safe printing (only prints if USB connected)
#define safe_print(...) if (isMaster) { Serial.print(__VA_ARGS__); }
#define safe_println(...) if (isMaster) { Serial.println(__VA_ARGS__); }

// State tracking
unsigned long lastPingTime = 0;
const unsigned long PING_INTERVAL = 2000;  // Master sends ping every 2 seconds

// ========== LED CONTROL ==========
void led_init(void) {
  if (isMaster) {
    pinMode(RXLED, OUTPUT); // Set RX LED as an output
  } else {
    pinMode(TXLED, OUTPUT); // Set TX LED as an output
  }
}

void led_blink(uint16_t duration_ms) {
  if (isMaster) {
    digitalWrite(RXLED, LOW);   // RX LED on
    delay(duration_ms);
    digitalWrite(RXLED, HIGH);  // RX LED off
  } else {
    digitalWrite(TXLED, LOW);   // TX LED on
    delay(duration_ms);
    digitalWrite(TXLED, HIGH);  // TX LED off
  }
}

// ========== USB DETECTION ==========
boolean check_usb(void) {
  Serial.begin(115200);
  delay(1500);  // Wait for USB to enumerate
  
  if (Serial) {
    Serial.println("USB Detected!");
    return true;
  }
  
  return false;
}

// ========== I2C SLAVE CALLBACKS ==========
// Called when master requests data from slave
void requestEvent() {
  led_blink(50);  // Quick blink
  safe_println("[SLAVE] Master requesting data...");
  
  // Send PONG response
  Wire.write('P');
  safe_println("[SLAVE] Sent PONG!");
}

// Called when master sends data to slave
void receiveEvent(int bytes) {
  led_blink(50);  // Quick blink
  safe_print("[SLAVE] Received ");
  safe_print(bytes);
  safe_println(" bytes");
  
  while (Wire.available()) {
    char c = Wire.read();
    safe_print("[SLAVE] Got: '");
    safe_print(c);
    safe_print("' (0x");
    safe_print((uint8_t)c, HEX);
    safe_println(")");
  }
}

void setup() {
  // Detect USB connection and determine role
  isMaster = check_usb();
  
  // Initialize LED
  led_init();
  
  safe_println("\n\n=== I2C Communication Test ===");
  safe_print("Role: ");
  safe_println(isMaster ? "MASTER (USB)" : "SLAVE (NO USB)");
  
  if (isMaster) {
    // Master mode
    Wire.begin();
    Wire.setClock(100000);  // 100kHz I2C clock
    safe_println("I2C Master initialized at 100kHz");
    safe_println("Starting communication test...\n");
  } else {
    // Slave mode
    Wire.begin(SLAVE_ADDRESS);
    Wire.onRequest(requestEvent);  // Register callback for data request
    Wire.onReceive(receiveEvent);  // Register callback for data receive
    safe_println("I2C Slave initialized at address 0x32");
  }
}

void loop() {
  if (isMaster) {
    master_loop();
  } else {
    slave_loop();
  }
}

// ========== MASTER CODE ==========
void master_loop() {
  if (millis() - lastPingTime >= PING_INTERVAL) {
    safe_print("[MASTER] Sending PING at ");
    safe_print(millis());
    safe_println(" ms");
    
    led_blink(50);  // Quick blink
    
    // Send PING to slave
    Wire.beginTransmission(SLAVE_ADDRESS);
    Wire.write('P');
    uint8_t error = Wire.endTransmission();
    
    if (error == 0) {
      safe_println("[MASTER] PING sent successfully");
      
      // Request PONG from slave
      delay(100);  // Short delay
      safe_println("[MASTER] Requesting PONG...");
      
      Wire.requestFrom(SLAVE_ADDRESS, 1);
      
      if (Wire.available()) {
        char response = Wire.read();
        if (response == 'P') {
          safe_println("[MASTER] ✓ Received PONG!");
          safe_println("[MASTER] ✓ Communication successful!\n");
          led_blink(50);  // Success blink
        } else {
          safe_print("[MASTER] ✗ Got unexpected: '");
          safe_print(response);
          safe_print("' (0x");
          safe_print((uint8_t)response, HEX);
          safe_println(")");
        }
      } else {
        safe_println("[MASTER] ✗ No response from slave");
      }
    } else {
      safe_print("[MASTER] ✗ Transmission error: ");
      safe_println(error);
      if (error == 2) {
        safe_println("         (Slave not found - check wiring and slave power)");
      }
    }
    
    lastPingTime = millis();
  }
  delay(10);
}

// ========== SLAVE CODE ==========
void slave_loop() {
  // Slave is interrupt-driven via Wire callbacks
  // Just keep the main loop alive
  delay(10);
}
