#include <IRremote.h>

int ir_alici_pin = 2;
IRrecv ir_alici(ir_alici_pin);

decode_results results;

void setup() {
  Serial.begin(9600);
  Serial.println("IR Alici Etkinlestiriliyor...");
  ir_alici.enableIRIn(); // IR alicisi baslatilacak
  Serial.println("IR Alici Etkinlestirildi...");
}

void loop() {
  if(ir_alici.decode(&results)) // IR sinyalinin kodunun cozulmesi saglandi
  {
    Serial.println(results.value); // HEX yazmazsan 10'luk sistemde tusu gösterir
    ir_alici.resume(); // Bir sonraki sinyalin alinmasi icin IR alici tekrar baslatilir
  }
  delay(100); // milisaniye
}
