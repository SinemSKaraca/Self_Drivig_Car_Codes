#include <IRremote.h>

const ir_data_pini = 2; // Program boyunca pin konumlarında değişiklik olmayacak
const OUT1 = 5; // Motor sürücünün OUTi çıkışı ~ Arduino kartın j numaralı I/O'su
const OUT2 = 6;
const OUT3 = 7;
const OUT4 = 8;

// Motorların hız kontrolü için motor sürücünün pin tanımlamaları:
const int motor_kontrol_1 = 9; // Motor sürücünün ENA (PWM özellikli) - OUT1/2
const int motor_kontrol_2 = 10; // Motor sürücünün ENB Pini - OUT3/4

// HCSR04 Ultaronik mesafe sensörü pin tanımlamaları:
const int echoPin = 11;
const int trigPin = 12;
// Motorların çalışması için ENA ve ENB çıkışlarına gönderilecek PWM sinyalinin sabit değeri
int hiz = 80; 

// IR Sensörü pin tanımlamaları:
IRrecv ir_alici(ir_data_pini);
decode_results results; // kumandadan gelen sinyali çözmek için türetilen nesne

// Kumanda tuş kodlarının tanımlanması:
#define up 16718055    // İLERİ
#define down 16730805  // GERİ
#define right 16734885 // SAĞ
#define left 16716015  // SOL
#define zero 16750695  // ARAÇ DURDURMA
#define star 16738455  // HIZ ARTTIRMA
#define kare 16756815  // HIZ AZALTMA

// Bu kısım Arduino'ya ilk kez enerji verildiğinde/kart resetlendiğinde
// yalnızca bir defa çalışır.
void setup() {
  // Motor sürücüye arduinodan bilgi aktarılacak
  pinMode(OUT1, OUTPUT); 
  pinMode(OUT2, OUTPUT);
  pinMode(OUT3, OUTPUT);
  pinMode(OUT4, OUTPUT);
  pinMode(motor_kontrol_1, OUTPUT);
  pinMode(motor_kontrol_2, OUTPUT);

  // HCSR04 sensörünün pinlerinin işlevleri
  pinMode(echoPin, INTPUT); // Dışardan gelen sinyali alacak
  pinMode(trigPin, OUTPUT); // Dışarıya ultrasonik sinyal verecek

  // Arduino kartına enerji verir vermez aracın hareket etmemesi için:
  digitalWrite(motor_kontrol_1, LOW);
  digitalWrite(motor_kontrol_2, LOW);
  digitalWrite(OUT1, LOW);
  digitalWrite(OUT2, LOW);
  digitalWrite(OUT3, LOW);
  digitalWrite(OUT4, LOW);

  // IR alıcısının başlatılması:
  ir_alici.enableIRIn();
}

void loop() {
  // put your main code here, to run repeatedly:

}
