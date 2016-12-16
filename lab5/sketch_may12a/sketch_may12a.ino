#define MAX_WAIT_FOR_TIMER 16
unsigned int waitFor(int timer, unsigned long period){
  static unsigned long waitForTimer[MAX_WAIT_FOR_TIMER];
  unsigned long newTime = micros() / period;
  int delta = newTime - waitForTimer[timer];
  if ( delta < 0 ) delta += 1 + (0xFFFFFFFF / period);   
  if ( delta ) waitForTimer[timer] = newTime;
  return delta;
}

// Variables globales pour la communication inter-taches
char mess[32];
byte full;
byte onled = 1;

void Led (int timer, long period, byte led, byte *on) {
  static int val = 0;
  if (!waitFor(timer,period)) return; // sort s'il y a moins d'une période écoulée
  if (*on == 0) {
    val = 0;
  }
  digitalWrite(13,val);
  val = 1 - val;
}

void Mess (byte *full, char * mess) {
  if (! (*full) ) return;
  *full = 0;
  Serial.println(mess);
}

void setup () {
  pinMode(13,OUTPUT);
  Serial.begin(115200);
}

void GetKbd (byte *full, char * mess, byte len, byte *on) {
  static byte index = 0;
  if (!Serial.available()) return;
  char c = Serial.read();
  
  mess[index++] = c;
  if (c == '\n') {
    mess[index-1] = 0;
    index = 0;
    *full = 1;
    *on = (strcmp(mess,"on")==0) ? 1
        : (strcmp(mess,"off")==0) ? 0
        : *on;
        
  } else if (index == len) {
    index--;
  }

  Serial.println(mess);
}

void loop() {
  Led (0,100000,13, &onled);           // Led est exécutée toutes les 100ms
  Mess (&full, mess);           // mess est un buffer d'echange avec getkbd et full une bascule de synchro
  GetKbd (&full, mess, sizeof(mess), &onled);
}
