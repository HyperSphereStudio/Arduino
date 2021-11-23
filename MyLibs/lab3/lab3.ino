int pinA=2;
int pinB=3;
int pinC=4;
int pinF=5;

void setup() {
  Serial.begin(115200);
  pinMode(pinA,OUTPUT);
  pinMode(pinB,OUTPUT);
  pinMode(pinF,INPUT);
  
  digitalWrite(pinA,LOW);
  digitalWrite(pinB,LOW);
  bool offOff = digitalRead(pinF);
  digitalWrite(pinA, HIGH);
  bool onOff = digitalRead(pinF);
  digitalWrite(pinB, HIGH);
  bool onOn = digitalRead(pinF);
  digitalWrite(pinA, LOW);
  bool offOn = digitalRead(pinF);
  digitalWrite(pinB, LOW);
  Serial.println(String(offOff) + " " + String(onOff) + " " + String(onOn) + " " + String(offOn));
  
  digitalWrite(pinA,LOW);
  digitalWrite(pinB,LOW);
}

void test(bool a, bool b, bool c){
   active(pinA,a);
   active(pinB,b);
   active(pinC,c);
   Serial.println("A:" + String(a) + "\tB:" + String(b) + "\tC:" + String(c) + "\tF:" + String(digitalRead(pinF)));
}

void active(int pin, bool value){
   digitalWrite(pin, value ? HIGH : LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
}
