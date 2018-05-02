#define buz 8
#define RESET_DIO 9
#define SDA_DIO 10
#define UPDATE_RATE 2000        // in ms
#define UNLOCK_TIME 4           // in sec

#include <LiquidCrystal.h>
#include <SPI.h>
#include <RFID.h>

RFID RC522(SDA_DIO, RESET_DIO);
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void start_countdown(int ct = UNLOCK_TIME - 1);

bool locked = true;

char id_list[][5] = {
    //UIDs are stored in gpg encrypted file in /gpg
};

String members[] = {
  "Nikhil",
  "Viral",
  "Nisar",
  "Sunny",
  "Deep",
  "Abhay",
  "Mihir",
  "Sanil",
  "Vedant",
  "Shubham",
  "Jayshil",
  "Deep",                                                                       //TAG1
  "Mridul",
  "Sid",                                                                         //TAG2
  "Sid",
  "Lakshman",
  "Armaan"
};
void setup() {
  lcd.begin(16, 2);
  SPI.begin();
  RC522.init();
  pinMode(buz, OUTPUT);
  //  pinMode(bar_emagnet, OUTPUT);
  DDRC = DDRC | B001111;
  lock_door();
  lcd_boot();
  lcd.noCursor();
}

void loop() {
  checkID();
  update_lcd();
}
