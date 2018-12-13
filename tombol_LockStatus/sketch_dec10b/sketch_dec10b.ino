//mengset tombol active menjadi low
#define ON LOW
#define OFF !ON

const byte pin_button = 2;
//data awal adalah off
//data sebelumnnya adalah juga off
boolean data = OFF;
boolean data_last = data;

//variabel untuk lock status 
boolean logika = data;

//delay untuk penekanan tombol
//setalah ditekan, maka selama 150ms
//tidak dapat ditekan
//delay ini berguna untuk menghindari 2 kali eksekusi
unsigned long  delay_press = 150;
unsigned long  delay_press_last = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);

  //input tombol denga pullup resistors
  pinMode(pin_button, INPUT_PULLUP);
}

void loop() {
  //jika selisih waktu penekanan tombol
  //lebih besar dari waktu delay tombol
  //baca tomol lagi, jika tidak tombol tidak dibaca
  if(millis() - delay_press_last > delay_press){
    
    //baca data tombol
    data = digitalRead(pin_button);

    //jika data berbeda dari data sebelumnya
    //cetak ke serial monitor
    if(data != data_last){

      //jika data = ON
      if(data == ON){

        //balik status logika tombol
        logika = !logika;

        //pencetakan kondisi tombol ke serial monitor, ON atau OFF
        if(logika == ON){
          Serial.println("ON");
        }else{
          Serial.println("OFF");
        }
      }
      //simpan data sebagai data sebelumnya
      data_last = data;
      //catat waktu penekanan tombol terakhir
      delay_press_last = millis();
    }
  }
} 
