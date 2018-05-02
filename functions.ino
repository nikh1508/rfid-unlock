void startup_tone() {
  tone(buz, 1800);
  delay(230);
  tone(buz, 2000);
  delay(230);
  tone(buz, 2400);
  delay(400);
  noTone(buz);
}

void lcd_boot() {
  lcd.setCursor(4, 0);
  lcd.print("Booting");
  for (int i = 0; i <= 100; i++) {
    lcd.setCursor(11, 0);
    int tmp = i / 30;
    //    if (i % 30 == 0)
    //      tone(buz, 2000, 150);
    while (tmp--)
      lcd.print(".");
    lcd.setCursor(6, 1);
    lcd.print(i);
    lcd.print("%");
    delay(4);
  }
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Ready...");
  startup_tone();
}

long long last_update = millis();
bool update_screen = true;

void update_lcd() {
  if (millis() - last_update > UPDATE_RATE)
  {
    last_update = millis();
    update_screen = !update_screen;
    switch (update_screen) {
      case true:
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("SRM TEAM");
        lcd.setCursor(2, 1);
        lcd.print("R O B O C O N");
        break;
      case false:
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Door Status:");
        if (locked) {
          lcd.setCursor(5, 1);
          lcd.print("LOCKED");
        } else
        {
          lcd.setCursor(4, 1);
          lcd.print("UNLOCKED");
        }
        break;
    }
  }
}

int RFID_match(char id[5]) {
  int id_index = 0;
  for (char *current : id_list) {
    if (current[0] == id[0] && current[1] == id[1] && current[2] == id[2] && current[3] == id[3] && current[4] == id[4])
      return id_index;
    id_index++;
  }
  return -1;
}

void lock_door() {
  locked = true;
  //digitalWrite(bar_emagnet, LOW);
  PORTC = PORTC & B110000;
}

void unlock_door(int indx) {
  locked = false;
  delay(200);
  //  digitalWrite(bar_emagnet, HIGH);
  PORTC = PORTC | B001111;
  say_greeting(indx);
  tone(buz, 2500);
  delay(300);
  noTone(buz);
  tone(buz, 2100);
  delay(200);
  noTone(buz);
  delay(500);
}

void say_greeting(int  indx) {
  lcd.clear();
  lcd.setCursor(7, 0);
  lcd.print("Hi,");
  lcd.setCursor((16 - members[indx].length()) / 2, 1);
  lcd.print(members[indx]);
}

void start_countdown(int ct = UNLOCK_TIME - 1) {
  long long unlock = millis() + ct * 1000;
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Door Locking");
  while (unlock - millis() > 0) {
    lcd.setCursor(1, 1);
    lcd.print("Back in: ");
    lcd.print((int)(unlock - millis()) / 1000);
    lcd.print(" Sec");
  }
  lcd.clear();
  lcd.setCursor(2, 0); 
  lcd.print("Locking back");
  lcd.setCursor(4, 1);
  lcd.print("the Door");
  lock_door();
  delay(1000);
}

void unauth() {
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("UNAUTHORIZED");
  lcd.setCursor(0, 1);
  lcd.print("Contacting ADMIN");
  noTone(buz);
  for (int i = 0; i < 15; i++) {
    tone(buz, 2500);
    delay(350);
    noTone(buz);
    delay(150);
  }
}
