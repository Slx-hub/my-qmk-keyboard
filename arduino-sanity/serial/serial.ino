/*
 * Dactyl Manuform Single-Wire Serial Communication Sanity Check
 * Tests ping-pong communication over pin 3 using open-drain logic (like QMK)
 * 
 * Set isMaster to true on ONE Pro Micro, false on the OTHER
 * Wire: Pin 3 to Pin 3 between both Pro Micros (with pull-up resistor, typically 4.7k)
 *       Both GND pins connected
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

// USB detection and master/slave role
boolean isMaster = false;  // Automatically set based on USB connection

// Only enable serial debug if USB is connected
#define DEBUG_SERIAL isMaster

// Macro for safe printing (only prints if USB connected)
#define safe_print(...) if (isMaster) { Serial.print(__VA_ARGS__); }
#define safe_println(...) if (isMaster) { Serial.println(__VA_ARGS__); }

// Pin 3 on Pro Micro (PD0)
#define SERIAL_PIN 3
#define SERIAL_DDR DDRD
#define SERIAL_PORT PORTD
#define SERIAL_INPUT PIND
#define SERIAL_MASK (1 << 0)  // Pin 3 is PD0

// Timing (in microseconds) - matches QMK's SERIAL_DELAY
#define SERIAL_DELAY 24

// Synchronization delay for stability
inline void serial_delay(void) {
  _delay_us(SERIAL_DELAY);
}

// State tracking
unsigned long lastPingTime = 0;
const unsigned long PING_INTERVAL = 2000;  // Master sends ping every 2 seconds


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

void setup() {
  // Detect USB connection first
  isMaster = check_usb();
  
  safe_println("\n\n=== Dactyl Sanity Check (Single Wire) ===");
  safe_print("Role: ");
  safe_println(isMaster ? "MASTER (USB)" : "SLAVE (NO USB)");
  safe_print("USB Connected: ");
  safe_println(isMaster ? "YES" : "NO");
  safe_println("Waiting for connection...\n");
  
  if (isMaster) {
    serial_master_init();
  } else {
    serial_slave_init();
  }
}

// Master initialization
void serial_master_init(void) {
  
  set_output();
  line_high();
}

// Slave initialization
void serial_slave_init(void) {
  set_input();
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
    
    // Initiate communication - pull line low briefly
    set_output();
    line_low();
    serial_delay();
    
    // Wait for slave to sync
    sync_recv();
    
    // Now send our byte
    serial_write_byte('P');
    sync_recv();  // Wait for slave's ack
    
    // Receive response
    safe_println("[MASTER] Waiting for PONG...");
    uint8_t response = serial_read_byte();
    sync_send();  // Acknowledge receipt
    
    if (response == 'P') {
      safe_println("[MASTER] ✓ Received PONG!");
      safe_println("[MASTER] ✓ Communication successful!\n");
    } else {
      safe_print("[MASTER] ✗ Got unexpected: 0x");
      safe_println(response, HEX);
    }
    
    // Reset to idle
    set_output();
    line_high();
    
    lastPingTime = millis();
  }
  delay(10);
}

// ========== SLAVE CODE ==========
void slave_loop() {
  // Check if master is pulling line low
  if (!(SERIAL_INPUT & SERIAL_MASK)) {
    // Pin is low, master is initiating
    safe_println("[SLAVE] Master signal detected!");
    
    // Send sync to acknowledge
    sync_send();
    
    // Read master's byte
    uint8_t received = serial_read_byte();
    sync_send();  // Acknowledge receipt
    
    if (received == 'P') {
      safe_print("[SLAVE] Received PING: 0x");
      safe_print(received, HEX);
      safe_println("");
      
      // Send response
      safe_println("[SLAVE] Sending PONG back...");
      serial_write_byte('P');
      sync_recv();  // Wait for master's ack
      safe_println("[SLAVE] PONG sent!\n");
    } else {
      safe_print("[SLAVE] Got unexpected: 0x");
      safe_println(received, HEX);
    }
    
    // Return to idle
    set_input();
  }
  delay(10);
}

// ========== SINGLE-WIRE PROTOCOL ==========

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

// ========== SYNCHRONIZATION ==========
// Used by master to synchronize with slave
void sync_recv(void) {
  set_input();
  // Wait for line to go high (slave releases)
  while (!read_pin());
  serial_delay();
}

// Used by slave to send sync signal
void sync_send(void) {
  set_output();
  line_low();
  serial_delay();
  line_high();
}

// ========== BYTE TRANSMISSION ==========

// Send one byte (MSB first) - matches QMK protocol
void serial_write_byte(uint8_t data) {
  set_output();
  uint8_t b = 8;
  while (b--) {
    if (data & (1 << b)) {
      line_high();
    } else {
      line_low();
    }
    serial_delay();
  }
}

// Receive one byte - matches QMK protocol
uint8_t serial_read_byte(void) {
  uint8_t byte = 0;
  set_input();
  for (uint8_t i = 0; i < 8; ++i) {
    byte = (byte << 1) | read_pin();
    serial_delay();
    _delay_us(1);  // Extra delay for stability
  }
  return byte;
}

// Master sends single byte with sync
void send_byte(uint8_t byte) {
  serial_write_byte(byte);
  sync_recv();  // Wait for slave to acknowledge
}

// Slave receives byte and sends sync
uint8_t recv_byte(void) {
  uint8_t byte = serial_read_byte();
  sync_send();  // Acknowledge receipt
  return byte;
}

// Delay for timing (REMOVED - using _delay_us instead)
// void delay_us(uint16_t us) { ... }

