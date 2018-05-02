void checkID() {
  if (RC522.isCard())
  {
    if (readCard());
    { tone(buz, 2000);
      delay(200);
      noTone(buz);
      char card_inRead[5] = "";
      for (int  i = 0; i < 5; i++)
        card_inRead[i] = RC522.serNum[i];
      int auth = RFID_match(card_inRead);
      if (auth >= 0) {
        unlock_door(auth);
        start_countdown();                // This func will lock the door itself after the countdown is over
      }
      else {
        unauth();
      }
    }
  }
}


//bool readCard() {
//  bool consistent = false;
//  int tries = 0;
//  while (!consistent && tries < 3) {
//    RC522.readCardSerial();
//    char temp[5] = "", temp2[5] = "";
//    for (int i = 0; i < 5; i++)
//      temp[i] = RC522.serNum[i];
//    delay(50);
//    RC522.readCardSerial();
//    if (temp[0] == (char)RC522.serNum[0] && temp[1] == (char)RC522.serNum[1] && temp[2] == (char)RC522.serNum[2] && temp[3] == (char)RC522.serNum[3] && temp[4] == (char)RC522.serNum[4] && RC522.isCard())
//    {
//      for (int i = 0; i < 5; i++)
//        temp2[i] = RC522.serNum[i];
//      delay(50);
//      RC522.readCardSerial();
//      if (temp2[0] == (char)RC522.serNum[0] && temp2[1] == (char)RC522.serNum[1] && temp2[2] == (char)RC522.serNum[2] && temp2[3] == (char)RC522.serNum[3] && temp2[4] == (char)RC522.serNum[4] && RC522.isCard())
//        consistent = true;
//    }
//    tries++;
//  }
//  return consistent;
//}

//bool readCard() {
//  bool consistent = false;
//  int tries = 0;
//  while (!consistent && tries < 3) {
//    for (int j = 0; j < 3; j++) {
//      RC522.readCardSerial();
//      char temp[5] = "";
//      for (int i = 0; i < 5; i++)
//        temp[i] = RC522.serNum[i];
//      delay(50);
//      RC522.readCardSerial();
//      if (temp[0] == (char)RC522.serNum[0] && temp[1] == (char)RC522.serNum[1] && temp[2] == (char)RC522.serNum[2] && temp[3] == (char)RC522.serNum[3] && temp[4] == (char)RC522.serNum[4])
//        consistent = true;
//      else consistent = false;
//    }
//    tries++;
//  }
//  return consistent;
//}

bool readCard() {
  bool consistent = false;
  int tries = 0;
  char temp[5] = "", match[5] = "";
  while (!consistent && tries < 3) {
    RC522.readCardSerial();
    for (int i = 0; i < 5; i++)
      match[i] = RC522.serNum[i];
    Serial.println("here..");
    for (int j = 0; j < 10; j++) {
      delay(25);
      RC522.readCardSerial();
      for (int i = 0; i < 5; i++)
        temp[i] = RC522.serNum[i];
      if (temp[0] == (char)match[0] && temp[1] == (char)match[1] && temp[2] == (char)match[2] && temp[3] == (char)match[3] && temp[4] == (char)match[4])
        consistent = true;
        else {
          consistent = false;
          break;
        }
    }
    tries++;
  }
  return consistent;
}
