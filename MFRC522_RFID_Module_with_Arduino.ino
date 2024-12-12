#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
#define LED1 2
#define LED2 3
byte readCard[4];
String tag_UID = "33CADA2A";  // Replace this with the UID of your tag!!!
String tag_UID2="232AAE14";
String tagID = "";
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance
void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(LED2, LOW);    // turn the LED off by making the voltage LOW

  Serial.begin(115200);        // Initialize serial communications with the PC
  SPI.begin(); // SPI bus
  mfrc522.PCD_Init(); // Initialise MFRC522
}
void loop()
{
  //Wait until new tag is available
  while (readID())
  {
    if (tagID == tag_UID)
    {
      digitalWrite(LED1, !digitalRead(LED1));  // Turn on or off the onboard led
    }
    else if (tagID == tag_UID2)
    {
      digitalWrite(LED2, !digitalRead(LED2));  // Turn on or off the onboard led
    }
  }
}
  //Read new tag if available
  boolean readID()
  {
    //Check if a new tag is detected or not. If not return.
    if ( ! mfrc522.PICC_IsNewCardPresent())
    {
      return false;
    }
    //Check if a new tag is readable or not. If not return.
    if ( ! mfrc522.PICC_ReadCardSerial())
    {
      return false;
    }
    tagID = "";
    // Read the 4 byte UID
    for ( uint8_t i = 0; i < 4; i++)
    {
      //readCard[i] = mfrc522.uid.uidByte[i];
      tagID.concat(String(mfrc522.uid.uidByte[i], HEX)); // Convert the UID to a single String
    }
    tagID.toUpperCase();
    mfrc522.PICC_HaltA(); // Stop reading
    return true;
  }
