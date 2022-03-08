
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <AmebaServo.h>





// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
#define SS_PIN 1
#define RST_PIN 8
#define LED_G 4 //define green LED pin
#define LED_Y 5 //define red LED pin
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.
AmebaServo myservo;


void setup()
{
Serial.begin(115200);  // Initiate a serial communication
SPI.begin();   // Initiate SPI bus
mfrc522.PCD_Init();  // Initiate MFRC522
lcd.begin(16,2);
lcd.backlight(); // Turn on the blacklight and print a message.
myservo.attach(7);
myservo.write(0);
pinMode(LED_G, OUTPUT);
pinMode(LED_Y, OUTPUT);
}




void loop()
{
// Look for new cards
if ( ! mfrc522.PICC_IsNewCardPresent())
{
lcd.setCursor(4,0);
lcd.print("To Enter");
lcd.setCursor(2,1);
lcd.print("Tap ID Card");
return;
}
else{
lcd.clear();
}
// Select one of the cards
if ( ! mfrc522.PICC_ReadCardSerial())
{
return;
}
//Show UID on serial monitor
Serial.print("UID tag :");
String content= "";
byte letter;
for (byte i = 0; i < mfrc522.uid.size; i++)
{
Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
Serial.print(mfrc522.uid.uidByte[i], HEX);
content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
content.concat(String(mfrc522.uid.uidByte[i], HEX));
}
Serial.println();
content.toUpperCase();
if (content.substring(1) == "2A A5 81 24") //change here the UID of the card/cards that you want to give access
{
lcd.print("Daniel");
lcd.setCursor(0,1);
lcd.print("Entering");
digitalWrite(LED_G, HIGH);
delay(3000);
lcd.clear();
delay(2000);
lcd.print("Door Opening...");
delay(3000);
myservo.write(90);
delay(3000);
myservo.write(0);
digitalWrite(LED_G, LOW);
lcd.clear();
}
else if (content.substring(1) == "C9 D1 B7 99") //change here the UID of the card/cards that you want to give access
{
lcd.print("Pluto");
lcd.setCursor(0,1);
lcd.print("Entering");
digitalWrite(LED_G, HIGH);
delay(3000);
lcd.clear();
delay(2000);
lcd.print("Door Opening...");
delay(1000);
myservo.write(90);
delay(3000);
myservo.write(0);
digitalWrite(LED_G, LOW);
lcd.clear();
}
else  {
lcd.print("UNAUTHORIZE");
lcd.setCursor(0,1);
lcd.print("ACCESS!!");
digitalWrite(LED_Y,HIGH);
delay(3000);
digitalWrite(LED_Y,LOW);
lcd.clear();
}
}
