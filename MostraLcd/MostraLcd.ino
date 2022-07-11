#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>

int Contrast = 75;
//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// --- Declaração das variáveis --
int pino_ss       = 10;
int pino_rst      = 8;

MFRC522 mfrc522(pino_ss, pino_rst);  // Criando o objeto do nosso sensor

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init(); // Inicia MFRC522
  lcd.begin(16, 2); //Define o número de colunas e linhas do LCD
  lcd.clear(); //Limpa a tela

}

void loop() {
  analogWrite(9, Contrast);
  lcd.setCursor(0, 0);
  lcd.print("Aproxime...");

  // Verifica se algum cartão foi aproximado do sensor
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Verifica qual cartão foi lido
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  String conteudo = "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  lcd.clear();
  lcd.print("Aguarde...");
  Serial.println(conteudo);
  delay(2000);

  if (Serial.available() > 0) {
    char x = Serial.read();
    if (x == 'R') {
      lcd.clear();
      lcd.print("Erro");
      delay(2000);
    } else if (x == 'P') {
      lcd.clear();
      lcd.print("Pago");
      delay(2000);
    } else if (x == 'A') {
      lcd.clear();
      lcd.print("Atrasado");
      delay(2000);
    } else {
      lcd.clear();
      lcd.print("Erro...");
      delay(1000);
    }
  }
  delay(3000);
}
