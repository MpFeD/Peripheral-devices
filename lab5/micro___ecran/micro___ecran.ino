#include <Adafruit_SSD1306.h>


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <string.h>

#define MAX_WAIT_FOR_TIMER 16
unsigned int waitFor(int timer, unsigned long period){
  static unsigned long waitForTimer[MAX_WAIT_FOR_TIMER];
  unsigned long newTime = micros() / period;
  int delta = newTime - waitForTimer[timer];
  if ( delta < 0 ) delta += 1 + (0xFFFFFFFF / period);   
  if ( delta ) waitForTimer[timer] = newTime;
  return delta;
}


#define PIN_LUMI 1  
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

byte lumi, lumiFull;


void Lumi ( // Echantillonne périodiquement le capteur de lumière et rend sa valeur entre 0 et 99
   int timer, unsigned long period, // tâche périodique 
   byte pin,                        // numéro de la broche lue
   byte *lumi,                      // valeur lue comprise entre 0 et 99
   byte *lumiFull                   // drapeau mis à 1 à chaque période après écriture dans lumi
);

void Oled1 ( // Affichage de la lumiere                         
   byte *mess,                      // buffer à afficher
   byte *full                       // drapeau mis à 1 pour demander l'affichage
);



  int micro = 0;
  String str;
  
  void setup() {
    
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(0x01);
  pinMode(13, OUTPUT);
  }
  
  // the loop function runs over and over again forever
  void loop() {
    int n = 1023 - analogRead(micro);

    Lumi (0,1000000, PIN_LUMI, &lumi, &lumiFull);  
    Oled1 (&lumi, &lumiFull);

    if (n>100){
  Serial.println(n);
  str="OUI";
    digitalWrite(13, HIGH);  
    delay(30);              
    digitalWrite(13, LOW);    
  delay(30);                  
    }else{
      str="";
    }
}


void Lumi (int timer, unsigned long period, byte pin, byte *lumi, byte *lumiFull)
{
   if (!waitFor(timer,period)) return;
   *lumi = map(analogRead(pin),0,1023,0,99);
   *lumiFull = 1;   
}

void Oled1 (byte *mess,  byte *full) {
  if (! (*full) ) return;
  *full = 0;
  Serial.println(*mess);
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Est ce que tac suces ???");
  display.print(str);
  //display.println(*mess);
  display.display();
}



