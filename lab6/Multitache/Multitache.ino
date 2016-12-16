#define MAXTIMER 16

char* buff;
int* on;

long waitForTimer[MAXTIMER];
int waitFor(int timer, long period){
  long newTime = micros() / period;
  int delta = newTime - waitForTimer[timer];
  if ( delta ) {
    waitForTimer[timer] = newTime;
  }
  return delta;
}

void setup() {
  pinMode(13,OUTPUT);
  Serial.begin(115200);
}

void Led(int timer, long period, int led, int* on) {
  static int val = 0;
  if (!waitFor(timer,period)) return;
  val = 1 - val;
  digitalWrite(13,val);
}

void Mess(int timer, long period, const char * mess) {
  if (!waitFor(timer,period)) return;
  Serial.println(mess);
}

void GetKbd(char* b, int* on){
  if(Serial.available() == 0)
    return;
  while(true){
    Serial.read();
    Mess(1, 10000, buff);
    on = 1 - on;
  }
}

void loop() {
  Led (0,100000,13);
  Mess(1,1000000,buffer);
  Mess(2,10000000,"bonjour");
  GetKbd(buffer, &on);
}
