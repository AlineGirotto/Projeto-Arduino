#include <SPI.h>
#include <MFRC522.h>


// --- Declaração das variáveis --
int pino_ss       = 10;
int pino_rst      = 9;

MFRC522 mfrc522(pino_ss, pino_rst);  // Criando o objeto do nosso sensor

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init(); // Inicia MFRC522
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char x = Serial.read();
    if (x == 'R') {
      analogWrite(A2, 0);
      analogWrite(A1, 0);
      analogWrite(A0, 255);
      delay(2000);
    } else if (x == 'G') {
      analogWrite(A2, 0);
      analogWrite(A1, 255);
      analogWrite(A0, 0);      
      delay(2000);
    }else{      
      analogWrite(A2, 255);
      analogWrite(A1, 0);
      analogWrite(A0, 0);
      delay(1000);
    }
  }
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

  Serial.println(conteudo);
  delay(3000);
  Serial.flush();
}
