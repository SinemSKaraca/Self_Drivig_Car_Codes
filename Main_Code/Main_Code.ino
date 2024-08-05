#include <IRremote.h>

const int ir_data_pini = 2; // Program boyunca pin konumlarında değişiklik olmayacak
const int OUT1 = 5; // Motor sürücünün OUTi çıkışı ~ Arduino kartın j numaralı I/O'su
const int OUT2 = 6;
const int OUT3 = 7;
const int OUT4 = 8;

// Motorların hız kontrolü için motor sürücünün pin tanımlamaları:
const int EN_A = 9; // Motor sürücünün ENA (PWM özellikli) - OUT1/2
const int EN_B = 10; // Motor sürücünün ENB Pini - OUT3/4

// HCSR04 Ultaronik mesafe sensörü pin tanımlamaları:
const int echoPin = 11;
const int trigPin = 12;
// Motorların çalışması için ENA ve ENB çıkışlarına gönderilecek PWM sinyalinin sabit değeri
int hiz = 155; 

// IR Sensörü pin tanımlamaları:
IRrecv ir_alici(ir_data_pini);
decode_results results; // kumandadan gelen sinyali çözmek için türetilen nesne

// Kumanda tuş kodlarının tanımlanması:
#define up 16718055    // İLERİ
#define down 16730805  // GERİ
#define right 16734885 // SAĞ
#define left 16716015  // SOL
#define zero 16750695  // ARAÇ DURDURMA
#define star 16738455  // HIZ AZALTMA
#define kare 16756815  // HIZ ARTTIRMA

// Bu kısım Arduino'ya ilk kez enerji verildiğinde/kart resetlendiğinde
// yalnızca bir defa çalışır.
void setup() {
  // Motor sürücüye arduinodan bilgi aktarılacak
  pinMode(OUT1, OUTPUT); 
  pinMode(OUT2, OUTPUT);
  pinMode(OUT3, OUTPUT);
  pinMode(OUT4, OUTPUT);
  pinMode(EN_A, OUTPUT);
  pinMode(EN_B, OUTPUT);

  // HCSR04 sensörünün pinlerinin işlevleri
  pinMode(echoPin, INPUT); // Dışardan gelen sinyali alacak
  pinMode(trigPin, OUTPUT); // Dışarıya ultrasonik sinyal verecek

  // Arduino kartına enerji verir vermez aracın hareket etmemesi için:
  digitalWrite(EN_A, LOW);
  digitalWrite(EN_B, LOW);
  digitalWrite(OUT1, LOW);
  digitalWrite(OUT2, LOW);
  digitalWrite(OUT3, LOW);
  digitalWrite(OUT4, LOW);

  // IR alıcısının başlatılması:
  ir_alici.enableIRIn();
  Serial.begin(9600);
}

void loop() {
  int mesafe = mesafe_olcumu();
  if(mesafe > 40) {
    // Kumandadan herhangi bir tuşa basılıp basılmadığını kontrol ediyoruz
    if(ir_alici.decode(&results)) {
      Serial.println(results.value);
      switch(results.value) {
        case kare:
          if(hiz < 255)
            hiz += 5;
          Serial.println("Hizlandi");
          Serial.println(results.value);
          break;
        case star:
          if(hiz > 80)
            hiz -= 5;
          Serial.println("Yavasladi");
          Serial.println(results.value);
          break;
        case up:
          motor_hareketleri(1, 0, 0, 1, hiz);
          Serial.println("Ileri gitti");
          Serial.println(results.value);
          break;
        case down:
          motor_hareketleri(0, 1, 1, 0, hiz);
          Serial.println("Geri gitti");
          Serial.println(results.value);
          break;
        case left:
          motor_hareketleri(0, 1, 0, 1, hiz);
          Serial.println("Sola dondu");
          Serial.println(results.value);
          break;
        case right:
          motor_hareketleri(1, 0, 1, 0, hiz);
          Serial.println("Saga dondu");
          Serial.println(results.value);
          break;
        case zero:
          motor_hareketleri(0, 0, 0, 0, 0);
          Serial.println("Durdu");
          Serial.println(results.value);
          break;
      }
      ir_alici.resume();
    }
  }
  else {
    // Önde engel varsa araç geri gider
    motor_hareketleri(0, 1, 1, 0, hiz);
    delay(500);
    motor_hareketleri(0, 0, 0, 0, 0);
  }
}

int mesafe_olcumu() {
  long sure, mesafe; // sure: sensörden çıkan sinyalin gidiş-dönüşü arasında geçen süre
  digitalWrite(trigPin, LOW); // Sinyal kesim işlemi
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Sinyalin gidiş dönüşüyle alakalı hesaplama
  sure = pulseIn(echoPin, HIGH); // pinin high'dan low'a geçene kadar geçen süreyi hesaplar
  mesafe = sure / 29.1 / 2; // 29.1: cm cinsinden, 2: gidiş-dönüş
  delay(50); // milisaniye aralıklarla işlemler gerçekleşecek

  return mesafe;
}

// Aracın ileri, geri, sağa, sola hareket etmesini sağlayan fonksiyon
// İlk 4 parametre hangi motorun hangi yöne döneceğini belirleyecek
// Parametreler sırasıyla OUT1/2/3/4 ve hız kontrolü için kullanılacak
void motor_hareketleri(int deger1, int deger2, int deger3, int deger4, int hiz) {
  // ENA ve ENB'yi(motorların hepsinin aynı hızda çalışmasını istediğimiz için), hiz ile kontrol edeceğiz
  digitalWrite(OUT1, deger1); // deger1 = 0 ise LOW olur
  digitalWrite(OUT2, deger2);
  digitalWrite(OUT3, deger3);
  digitalWrite(OUT4, deger4);

  analogWrite(EN_A, hiz);
  analogWrite(EN_B, hiz);
}











