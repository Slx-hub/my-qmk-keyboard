/*
 * Simple Pulse-Based Communication Test
 * Master sends 100ms pulse, slave responds with 100ms pulse
 * 
 * Role automatically determined by USB connection:
 * - USB Connected = Master
 * - No USB = Slave
 * 
 * Wire: Pin 3 to Pin 3 between both Pro Micros (with pull-up resistor, typically 4.7k)
 *       Both GND pins connected
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

// USB detection and master/slave role
boolean isMaster = false;  // Automatically set based on USB connection

// Macro for safe printing (only prints if USB connected)
#define safe_print(x) if (isMaster) { Serial.print(x); }
#define safe_println(x) if (isMaster) { Serial.println(x); }

// Pin 3 on Pro Micro (PD0)
#define SERIAL_PIN 3
#define SERIAL_DDR DDRD
#define SERIAL_PORT PORTD
#define SERIAL_INPUT PIND
#define SERIAL_MASK (1 << 0)  // Pin 3 is PD0

int RXLED = 17; // The RX LED has a defined Arduino pin
int TXLED = 30; // The TX LED has a defined Arduino pin

// ========== LED CONTROL ==========
void led_init(void) {
  if (isMaster) {
    pinMode(RXLED, OUTPUT); // Set RX LED as an output
  } else {
    pinMode(TXLED, OUTPUT); // Set TX LED as an output
  }
}

void led_on(void) {
  if (isMaster) {
    digitalWrite(RXLED, LOW); // RX LED on
  } else {
    digitalWrite(TXLED, LOW); // TX LED on
  }
}

void led_off(void) {
  if (isMaster) {
    digitalWrite(RXLED, HIGH); // RX LED off
  } else {
    digitalWrite(TXLED, HIGH); // TX LED off
  }
}

void led_blink(uint16_t duration_ms) {
  led_on();
  delay(duration_ms);
  led_off();
}

// ========== USB DETECTION ==========
// Check if USB is connected using Serial
boolean check_usb(void) {
  // Try Serial communication
  Serial.begin(115200);
  delay(1500);  // Wait for USB to enumerate
  
  // Check if Serial is ready (USB connected)
  if (Serial) {
    Serial.println("USB Detected!");
    return true;
  }
  
  return false;
}

// ========== SINGLE-WIRE PIN CONTROL ==========

// Make pin output (driving it low or releasing to high via pull-up)
void set_output(void) {
  SERIAL_DDR |= SERIAL_MASK;
}

// Make pin input (floating, pulled high by resistor)
void set_input(void) {
  SERIAL_DDR &= ~SERIAL_MASK;
  SERIAL_PORT |= SERIAL_MASK;  // Enable pull-up
}

// Read current pin state
uint8_t read_pin(void) {
  return !!(SERIAL_INPUT & SERIAL_MASK);
}

// Pull line low
void line_low(void) {
  SERIAL_PORT &= ~SERIAL_MASK;
}

// Release line (let pull-up resistor pull it high)
void line_high(void) {
  SERIAL_PORT |= SERIAL_MASK;
}

// Send 100ms pulse (pull low for 100ms)
void send_pulse(void) {
  set_output();
  line_low();
  led_on();
  delay(100);
  line_high();
  led_off();
}

// Wait for falling edge (line goes from high to low)
boolean wait_for_falling_edge(uint32_t timeout_ms) {
  uint32_t start = millis();
  
  // Wait for line to be high first
  while (!read_pin()) {
    if (millis() - start > timeout_ms) {
      return false;
    }
  }
  
  // Now wait for falling edge
  while (read_pin()) {
    if (millis() - start > timeout_ms) {
      return false;
    }
  }
  
  return true;
}

void setup() {
  // Detect USB connection first
  isMaster = check_usb();
  
  // Initialize LED based on USB status
  led_init();
  
  safe_println("\n\n=== Simple Pulse Communication Test ===");
  safe_print("Role: ");
  safe_println(isMaster ? "MASTER (USB)" : "SLAVE (NO USB)");
  safe_println("Starting communication test...\n");
  
  if (isMaster) {
    // Master: set to output initially
    set_output();
    line_high();
  } else {
    // Slave: set to input waiting for master
    set_input();
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
  safe_println("[MASTER] Waiting 500ms...");
  delay(500);
  
  safe_println("[MASTER] Sending pulse...");
  send_pulse();
  
  // Switch to input to wait for response
  safe_println("[MASTER] Waiting for response...");
  set_input();
  
  if (wait_for_falling_edge(2000)) {
    led_blink(50);  // Quick blink on response detected
    safe_println("[MASTER] ✓ Received response!");
    safe_println("[MASTER] ✓ Communication successful!\n");
  } else {
    safe_println("[MASTER] ✗ No response received\n");
  }
  
  // Reset to output for next cycle
  set_output();
  line_high();
  
  delay(1000);  // Wait before next ping
}

// ========== SLAVE CODE ==========
void slave_loop() {
  // Already in input mode from setup
  set_input();
  
  // Wait for falling edge from master
  if (wait_for_falling_edge(5000)) {
    led_blink(50);  // Quick blink on pulse detected
    safe_println("[SLAVE] Received pulse from master!");
    
    // Wait for pulse to finish
    delay(100);
    
    safe_println("[SLAVE] Sending response pulse...");
    send_pulse();
    safe_println("[SLAVE] Response sent!\n");
  }
}
