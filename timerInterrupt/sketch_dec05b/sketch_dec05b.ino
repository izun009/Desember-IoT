#define BUZZER_ON LOW
#define BUZZER_OFF !BUZZER_ON

  // GND buzzer dihubungkan ke pin 2
const byte PIN_BUZZER = 13;
  // variabel untuk cek waktu kirim
unsigned long waktu_kirim = 0;
  // logika buzzer
const unsigned long buzzer_delay[] = {0,200,100,200};
const boolean buzzer_state[] = {BUZZER_ON, BUZZER_OFF, BUZZER_ON,BUZZER_OFF};
byte buzzer_state_counter = sizeof(buzzer_state);
  // pencatat waktu timer buzzer
unsigned long buzzer_time = 0;
unsigned long buzzer_time_last = 0;
  // pencatat waktu timer kirim data
unsigned long kirimdata_time = 0;
unsigned long kirimdata_time_last = 0;
  // delay kirim data 3 detik
const long kirimdata_delay = 3000;
  // timer interrupt 10kHz
int Data_Hz = 10000; // per 0.1 S
  // hitung register untuk dicocokkan
long INT_REGISTER = (16000000L / (Data_Hz*1024L)) - 1;

void setup() {
    // aktifkan komunikasi serial
    // pada baudrate 19200
  Serial.begin(19200);
    // tunggu hinga Serial siap digunakan
  while(!Serial);
    // pin buzzer sebagai output
  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_BUZZER, BUZZER_OFF);
    // catat waktu kirim pertama kali
  waktu_kirim = millis();
    // setting interrupt
  cli(); //stop interrupts
  TCCR1A = 0; // set TCCR1A register = 0
  TCCR1B = 0; // set TCCR1B register = 0
  TCNT1 = 0; // inisialisasi counter = 0
  OCR1A = INT_REGISTER; // untuk 10kHz
  TCCR1B |= (1 << WGM12); // aktifkan CTC mode
  TCCR1B |= (1 << CS12) | (1 << CS10); // Set CS12&CS10bits=1024 prescaler
  TIMSK1 |= (1 << OCIE1A); // aktifkan timer compare interrupt
  sei(); //allow interrupts
}

void loop() {
  // program utama
  delay(300000);
  delay(300000);
  delay(300000);
}
  // ======================================
  // eksekusi sesuai timer interrupt
  // ======================================
ISR(TIMER1_COMPA_vect){
  cli(); //stop interrupts
    // kirim data
  KirimData();
    // bunyi tilit tilit
  TilitTilit();
  sei(); //allow interrupts
}

void TilitTilit(){
    // state ada 4 kondisi : 0 1 2 dan 3
    // 0 adalah bip pertama 200ms
    // 1 adalah matinya bip pertama 100ms
    // 2 adalah bip kedua 200ms
    // 3 adalah matinya bip kedua
    // jika buzzer_state_counter >= 4,
    // maka blok program ini tdk dieksekusi.
  if( buzzer_state_counter < sizeof(buzzer_state) ){
      // catat waktu saat ini
    buzzer_time = millis();
      // cek apakah delay pada index state sudah terpenuhi
    if(buzzer_time - buzzer_time_last >=
    buzzer_delay[buzzer_state_counter]){
      // aktifkan atau matika buzzer sesuai
      // logika pada index state
    digitalWrite(PIN_BUZZER, buzzer_state[buzzer_state_counter]);
      // pindah state berikutnya
    buzzer_state_counter++;
      // catat waktu tadi sebagai waktu eksekusi terakhir
    buzzer_time_last = buzzer_time;
    }
  }
}
  
    // fungsi untuk mengirim data
void KirimData(){
    // catat waktu sekarang
  kirimdata_time = millis();
    // apabila waktu kirim terakhir dan waktu sekarang sudah 3 detik
    // eksekusi blok program berikut
  if( kirimdata_time - kirimdata_time_last >= kirimdata_delay ){
      // cetak selisih waktu kirim sebelumnya
      // dengan pengiriman saat ini
    Serial.print("Selisih Waktu : ");
    Serial.println( millis() - waktu_kirim );
      // catat waktu kirim data
    waktu_kirim = millis();
      // catat waktu kirim data terakhir
    kirimdata_time_last = kirimdata_time;
      // setelah ngirim data
      // reset state buzzer menjadi 0
      // sehingga blok program pada
      // baris 72 dieksekusi
    buzzer_state_counter = 0;
  }
}
