
// interrupt ile deneyelim

#include <LiquidCrystal.h>
const int RS=7, EN=6, D4=5, D5=4, D6=3, D7=2;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

uint8_t ship[8] = {0x00, 0x18, 0x1C, 0x1F, 0x1C, 0x18, 0x00, 0x00};

uint8_t enemy[8] = {0x00, 0x0E, 0x1B, 0x1F, 0x03, 0x1F, 0x0E, 0x00};


int posS = 0;
int posE = 15;
unsigned long eskiZaman = 0;
const long aralik = 500; 


void setup() {
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  
  lcd.begin(16, 2);
  lcd.createChar(0,ship);
  lcd.createChar(1,enemy);
  
  lcd.setCursor(0,posS);
  lcd.write((byte)0);
  lcd.setCursor(posE,0);
  lcd.write((byte)1);
}

void enemyMove() {
  unsigned long suAnkiZaman = millis(); // millis başta başlayınca, saymaya devam ediyor sürekli
  if(suAnkiZaman - eskiZaman >= aralik) {
    eskiZaman = suAnkiZaman;
    lcd.setCursor(posE+1, 0);
    lcd.print(" ");
    lcd.setCursor(posE, 0);
    lcd.write((byte)1);
    posE--;
    
    if(posE<-1)
      posE = 15;
  }
}

void up() {
  posS = 0;
  lcd.setCursor(0,1);
  lcd.print(" ");
  lcd.setCursor(0,posS);
  lcd.write((byte)0);
}

void down() {
  posS = 1;
  lcd.setCursor(0,0);
  lcd.print(" ");
  lcd.setCursor(0,posS);
  lcd.write((byte)0);
}

bool collision(){
  if(posE == 0 && posS == 0) {
    lcd.clear();
    lcd.print("OYUN BITTI");
    return true;
  }
  return false;
}

void loop() {
  if(collision()) {
    exit(0); // bunda da arka planda sonsuz döngüye giriyormuş
  }
  
  enemyMove();

  if(!digitalRead(8)) {
    up();  
  }
  if(!digitalRead(9)) {
    down();
  }
  
  delay(20);
}
