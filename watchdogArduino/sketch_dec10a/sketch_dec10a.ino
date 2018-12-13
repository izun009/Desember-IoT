const int led = 13;
int resetpin = 12;

void setup() {
  // put your setup code here, to run once:
  digitalWrite(resetpin, HIGH);
  delay(2000);

  pinMode(led, OUTPUT);
  pinMode(resetpin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Reset");
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10);
  digitalWrite(led, HIGH);
  Serial.println("ON");
  delay(1000);
  digitalWrite(led, LOW);
  Serial.println("OFF");
  delay(1000);
  Serial.println("Resetting");
  delay(10);
  digitalWrite(resetpin, LOW);
  Serial.println("This Never Happens");
  //this never happens because arduino reset
}
