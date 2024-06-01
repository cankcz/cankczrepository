

#include <SPI.h>
#include <RFID.h>
#include <Keyboard.h>

#define SS_PIN 10
#define RST_PIN 7

#define ANAHTARLIK_0 147
#define ANAHTARLIK_1 193
#define ANAHTARLIK_2 139

#define KART_0 162
#define KART_1 254
#define KART_2 130

RFID rfid(SS_PIN,RST_PIN);

int buzzer = 7;

void setup() {
  pinMode(buzzer,OUTPUT);
  digitalWrite(buzzer,LOW);
  SPI.begin();
  rfid.init();
  Keyboard.begin();
  Serial.println();

}

void loop() {

  if(rfid.isCard()){
    if(rfid.readCardSerial()){
      if((rfid.serNum[0] == ANAHTARLIK_0 && rfid.serNum[1] == ANAHTARLIK_1 && rfid.serNum[2] == ANAHTARLIK_2) || 
         (rfid.serNum[0] == KART_0 && rfid.serNum[1] == KART_1 && rfid.serNum[2] == KART_2)){

        // başarılı
        digitalWrite(buzzer,HIGH);
        delay(100);
        digitalWrite(buzzer,LOW);
        delay(100);
        digitalWrite(buzzer,HIGH);
        delay(100);
        digitalWrite(buzzer,LOW);
        Keyboard.press(KEY_RETURN);
        delay(50);
        Keyboard.releaseAll();
        delay(200);

        Keyboard.print("YOUR_PASSWORD_HERE");
        Keyboard.press(KEY_RETURN);
        delay(50);
        Keyboard.releaseAll();
        delay(200);
        
      }
    }
  }
rfid.halt();
}