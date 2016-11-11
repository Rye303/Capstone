/*
 * 
 * Working Code for Write block
 * 
 * 
 * Nov 11, 2016
 * Ryan McLean
 * 
 * Writes to block 2 in sector 0
 * 
 * First value corresponds to x value
 * Second value corresponds to y value
 * 
 * Both are in hexidecimal
 * 
 * Change datablock[] to change written values
 * 
 */

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.
MFRC522::StatusCode status;
MFRC522::MIFARE_Key key;


void setup() {
    Serial.begin(9600); // Initialize serial communications with the PC
    while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
    SPI.begin();        // Init SPI bus
    mfrc522.PCD_Init(); // Init MFRC522 card
    
    for (byte i = 0; i < MFRC522::MF_KEY_SIZE; ++i) {
        key.keyByte[i] = 0xFF;
    }

    // Print notification to start scanning
    Serial.println("Scan a card: ");
    
} // Set-up


void loop() {

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

        
byte buffer[18];
byte sector = 0;
byte len = 2;
byte dataBlock[]    = {
        0x06, 0x07, 0x00, 0x00, //  1,  2,   3,  4,
        0x00, 0x00, 0x00, 0x00, //  5,  6,   7,  8,
        0x00, 0x00, 0x0,  0x00, //  9, 10, 255, 12,
        0x00, 0x00, 0x00, 0x00  // 13, 14,  15, 16
    };
byte blockAddr = 2;
byte size = sizeof(buffer);
MFRC522::StatusCode status;

// Authenticate using key A
    mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockAddr, &key, &(mfrc522.uid));

// write data
  mfrc522.MIFARE_Write(blockAddr, dataBlock, 16);

 // Read data from the block
    Serial.print("New data written to block: ");Serial.print(blockAddr); Serial.println("...");
    mfrc522.MIFARE_Read(blockAddr, buffer, &size);
    dump_byte_array(buffer, len); 
    
    // Only used for test, might not use for final project
    Serial.println();
      
      // Stop reading
      mfrc522.PICC_HaltA();
      // Stop encrypting
      mfrc522.PCD_StopCrypto1();
}

// Print to serial the bytes from blockAddr
void dump_byte_array(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
}
