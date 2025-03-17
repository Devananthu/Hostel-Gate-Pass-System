#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5
#define RST_PIN 15

MFRC522 rfid(SS_PIN, RST_PIN); // Create MFRC522 instance

const int led1Pin = 25; // LED for Card 1
const int led2Pin = 26; // LED for Card 2

// Update this with your actual card UIDs
byte card1[] = {0xB3, 0x63, 0x3A, 0x2A}; // Card 1 UID
byte card2[] = {0xF1, 0xF6, 0xAE, 0x2}; // Card 2 UID (example, change as needed)

void setup() {
  Serial.begin(115200);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);
  Serial.println("Place your card near the reader...");
}

void loop() {
  // Look for a new card
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    // Check which card is scanned
    if (compareUid(rfid.uid.uidByte, card1, sizeof(card1))) {
      digitalWrite(led1Pin, HIGH); // Turn on LED 1
      Serial.println("Card 1 scanned!");
      delay(1000);
      digitalWrite(led1Pin, LOW); // Turn off LED 1
    } else if (compareUid(rfid.uid.uidByte, card2, sizeof(card2))) {
      digitalWrite(led2Pin, HIGH); // Turn on LED 2
      Serial.println("Card 2 scanned!");
      delay(1000);
      digitalWrite(led2Pin, LOW); // Turn off LED 2
    }

    rfid.PICC_HaltA(); // Halt PICC
  }
}

bool compareUid(byte *uid1, byte *uid2, byte size) {
  for (byte i = 0; i < size; i++) {
    if (uid1[i] != uid2[i]) {
      return false;
    }
  }
  return true;
}
