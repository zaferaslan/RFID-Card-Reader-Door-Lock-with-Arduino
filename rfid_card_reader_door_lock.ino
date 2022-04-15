#include <SPI.h>                          //SPI kütüphanemizi tanımlıyoruz.
#include <MFRC522.h>                      //MFRC522 kütüphanemizi tanımlıyoruz.
#include <Servo.h>                        //Servo kütüphanemizi tanımlıyoruz.
#include<LiquidCrystal.h>                 //LiquidCrystal kütüphanemizi tanımlıyoruz.
LiquidCrystal lcd(7,6,5,4,3,2);           //lcd ekranının kullanacağımız pinlerini belirtip nesnesini oluşturuyoruz

int RST_PIN = 9;                          //RC522 modülü reset pinini tanımlıyoruz.
int SS_PIN = 10;                          //RC522 modülü chip select pinini tanımlıyoruz.
int servoPin = 8;                         //Servo motor pinini tanımlıyoruz.

Servo motor;                              //Servo motor için değişken oluşturuyoruz.
MFRC522 rfid(SS_PIN, RST_PIN);            //RC522 modülü ayarlarını yapıyoruz.
byte ID[4]={51,181,205,2};                //Yetkili kart ID'sini tanımlıyoruz. 


void setup() { 
  motor.attach(servoPin);                 //Servo motor pinini motor değişkeni ile ilişkilendiriyoruz.
  Serial.begin(9600);                     //Seri haberleşmeyi başlatıyoruz.
  SPI.begin();                            //SPI iletişimini başlatıyoruz.
  rfid.PCD_Init();                        //RC522 modülünü başlatıyoruz.
  lcd.begin(16,2);                        //Lcd ekranın 16x2 olduğunu belirttik.

}
 
void loop() {

  if ( ! rfid.PICC_IsNewCardPresent())    //Yeni kartın okunmasını bekliyoruz.
    return;

  if ( ! rfid.PICC_ReadCardSerial())      //Kart okunmadığı zaman bekliyoruz.
    return;

  if (rfid.uid.uidByte[0] == ID[0] &&     //Okunan kart ID'si ile ID değişkenini karşılaştırıyoruz.
    rfid.uid.uidByte[1] == ID[1] && 
    rfid.uid.uidByte[2] == ID[2] && 
    rfid.uid.uidByte[3] == ID[3] ) {
        lcd.setCursor(0, 0);       //Bu işlev imleci ve herhangi bir yazılı metni ekranın herhangi bir yerine yerleştiriyoruz.
        lcd.print("Kapi acildi");  //Lcd ekrana metin yazdırıyoruz.
        delay(1500);               //delay işlevi ile bekletiyoruz.
        lcd.clear();               //Bu işlev, LCD’de halihazırda görüntülenen herhangi bir metni veya veriyi siliyoruz.
        lcd.print("iyi gunler");   //Lcd ekrana metin yazdırıyoruz.
        delay(1500);               //delay işlevi ile bekletiyoruz.
        lcd.clear();               //Bu işlev, LCD’de halihazırda görüntülenen herhangi bir metni veya veriyi siliyoruz.
        motor.write(180);                 //Servo motoru 180 dereceye getiriyoruz.
        delay(2000);
        motor.write(0);                   //Servo motoru 0 dereceye getiriyoruz.
        delay(1000);
    }
    else{                                 //Yetkisiz girişte içerideki komutlar çalıştırılır.
      lcd.clear();                        //Bu işlev, LCD’de halihazırda görüntülenen herhangi bir metni veya veriyi siliyoruz.
      lcd.setCursor(0, 0);                //Bu işlev imleci ve herhangi bir yazılı metni ekranın herhangi bir yerine yerleştiriyoruz.
      lcd.print("Yetkisiz Kart");         //Lcd ekrana metin yazdırıyoruz.
      delay(1500);                        //delay işlevi ile bekletiyoruz.
      lcd.clear();                        //Bu işlev, LCD’de halihazırda görüntülenen herhangi bir metni veya veriyi siliyoruz.
      lcd.print("Kapi acilmaz");          //Lcd ekrana metin yazdırıyoruz.
      delay(1500);                        //delay işlevi ile bekletiyoruz.
      lcd.clear();                        //Bu işlev, LCD’de halihazırda görüntülenen herhangi bir metni veya veriyi siliyoruz.
    }
  rfid.PICC_HaltA();
}
