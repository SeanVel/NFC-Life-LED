#include "HT1632.h"
#include "life.h"

#define DATA 2
#define WR 3
#define CS 4
#define ROWS 16
#define COLS 24

#include <Wire.h>
#include <Adafruit_NFCShield_I2C.h>

#define IRQ   (2)
#define RESET (3)  // Not connected by default on the NFC Shield

Adafruit_NFCShield_I2C nfc(IRQ, RESET);


HT1632LEDMatrix matrix = HT1632LEDMatrix(DATA, WR, CS);

Life life(ROWS, COLS);

uint8_t lastCardFirst = 0;
uint8_t lastCardLast = 0;
uint8_t lastCard =0;
void setup()
{
  Serial.begin(9600);
  matrix.begin(HT1632_COMMON_16NMOS);
  delay(100);
  matrix.clearScreen();
  /*
  life.setCell(6, 4);
  life.setCell(6, 5);
  life.setCell(6, 6);
  life.setCell(5, 6);
  life.setCell(4, 5);
  
  // "5x5 infinite"
life.setCell(1, 1);
life.setCell(1, 2);
life.setCell(1, 3);
life.setCell(1, 5);
life.setCell(2, 1);
life.setCell(3, 4);
life.setCell(3, 5);
life.setCell(4, 2);
life.setCell(4, 3);
life.setCell(4, 5);
life.setCell(5, 1);
life.setCell(5, 3);
life.setCell(5, 5);
// "r-pentomino"
life.setCell(2, 1);
life.setCell(1, 2);
life.setCell(2, 2);
life.setCell(3, 2);
life.setCell(1, 3);
*/
  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  // Got ok data, print it out!
  Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX); 
  Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC); 
  Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);
  
  // Set the max number of retry attempts to read from a card
  // This prevents us from waiting forever for a card, which is
  // the default behaviour of the PN532.
  nfc.setPassiveActivationRetries(0x01);
  
  // configure board to read RFID tags
  nfc.SAMConfig();
    
  Serial.println("Waiting for an ISO14443A card");
}

void printGame()
{
  for (int row = 0; row < ROWS; ++row)
  {
    for (int col = 0; col < COLS; ++col)
    {
      if (life.checkCell(row, col) == 0)
        matrix.clrPixel(col, row);
      else
        matrix.setPixel(col, row);
    }
  }
  matrix.writeScreen();
}

void readCard()
{
   boolean success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  
  // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
  // 'uid' will be populated with the UID, and uidLength will indicate
  // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
  success = nfc.readPassiveTargetIDFelica(&uid[0], &uidLength);
  
  if (success) {
    uint8_t xShift;
    uint8_t yShift;
    Serial.println("Found a card!");
    Serial.print("UID Length: ");Serial.print(uidLength, DEC);Serial.println(" bytes");
    Serial.print("UID Value: ");
    for (uint8_t i=0; i < uidLength; i++) 
    {
      Serial.print(" 0x");Serial.print(uid[i], HEX); 
    }
    Serial.println("");
    if (lastCardFirst != uid[6] && lastCardLast != uid[7])
    {
      life.inputNFCID(uid[6],uid[7]);    
      lastCardFirst = uid[6];
      lastCardLast = uid[7];
    }
    else{}
  }
  else
  {
    // PN532 probably timed out waiting for a card
    Serial.println("Timed out waiting for a card");
    lastCardFirst = 0;
    lastCardLast = 0;
  }
}

void readOldCard()
{
 boolean success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  
  // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
  // 'uid' will be populated with the UID, and uidLength will indicate
  // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);
  
  if (success) {
    Serial.println("Found a card!");
    Serial.print("UID Length: ");Serial.print(uidLength, DEC);Serial.println(" bytes");
    Serial.print("UID Value: ");
    for (uint8_t i=0; i < uidLength; i++) 
    {
      Serial.print(" 0x");Serial.print(uid[i], HEX); 
    }
    Serial.println("");
    if (lastCard != uid[0])
    {
      switch(uid[0])
      {
      case 0xDD:
        // "5x5 infinite..?"
        life.setCell(1+8, 1+12);
        life.setCell(1+8, 2+12);
        life.setCell(1+8, 3+12);
        life.setCell(1+8, 5+12);
        life.setCell(2+8, 1+12);
        life.setCell(3+8, 4+12);
        life.setCell(3+8, 5+12);
        life.setCell(4+8, 2+12);
        life.setCell(4+8, 3+12);
        life.setCell(4+8, 5+12);
        life.setCell(5+8, 1+12);
        life.setCell(5+8, 3+12);
        life.setCell(5+8, 5+12);
        break;
      case 0xFD:
        // "r-pentomino"
        life.setCell(10, 9);
        life.setCell(9, 10);
        life.setCell(10, 10);
        life.setCell(11, 10);
        life.setCell(9, 11);
        break;
      case 0x3D:
        // "diehard"
        life.setCell(7, 6);
        life.setCell(7, 7);
        life.setCell(8, 7);
        life.setCell(6, 12);
        life.setCell(8, 11);
        life.setCell(8, 12);
        life.setCell(8, 13);
        break;
      case 0x2D:
        life.death();
        break;
      default:
        life.setCell(6, 4);
        life.setCell(6, 5);
        life.setCell(6, 6);
        life.setCell(5, 6);
        life.setCell(4, 5);
        break;
      }         
      lastCard = uid[0];
    }
    else{}
  }
  else
  {
    // PN532 probably timed out waiting for a card
    Serial.println("Timed out waiting for a card");
    lastCard = 0;
  } 
}


void loop() {
  Serial.println("Print Game!");
  life.tick();
  printGame();
  Serial.println("Read Card!");
  readCard();
  readOldCard();
  Serial.println("Tick Game!");
  delay(100);
}
