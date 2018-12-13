#include <avr/wdt.h>

byte counter = 0;

void setup() {
  // put your setup code here, to run once:
  //disable wdt
  //lalu tunggi hingga stabil
  wdt_disable();
  delay(2000);
  Serial.begin(19200);
  while(!Serial);

  Serial.print("======Start Porgram");

  //aktifkan wdt dg waktu tunggu 4 detik
  wdt_enable(WDTO_4S);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Counter");
  Serial.print(counter);
  Serial.print("=>");

  if(counter == 0){
    //blok program 2 detik
    Serial.println("2 detik");
    delay(2000);
  }
  else if(counter == 1){
    //blok program 6 detik
    Serial.println("6 detik");
    delay(1000);
    delay(1000);
    delay(1000);
    wdt_reset();
    delay(1000);
    delay(1000);
    delay(1000);
    wdt_reset();
  }
  else if(counter == 2){
    //blok program 11 detik
    Serial.println("11 detik");
    for(byte i = 0; i < 11; i++){
      delay(1000);
      wdt_reset();
    }
  }else{
    //blok program 4.5 detik
    Serial.println("4.5 detik");
    delay(4500);
  }

  counter++;

  //reset wdt sudah habis

  wdt_reset();
}
