#include <p18f452.h>
#include "LCD.h"
#include <stdio.h>
#include <delays.h>

// ;18F252 Configuration Registers
#pragma config OSC = HSPLL          // external crystal 10 MHzx 4
#pragma config OSCS = OFF           // disable clock switching
#pragma config PWRT = ON            // power up timer on
#pragma config WDT = OFF            // important - prevents regular reset 
#pragma config LVP = OFF            // disable LVP - really important
#pragma config STVR = OFF           // stack overflow disabled
#pragma config CCP2MUX = OFF        // CCP pin select 

#define LCD_RS PORTAbits.RA3
#define LCD_EN PORTAbits.RA1
#define LCD_WR PORTAbits.RA2
#define set_dd_line1_pos1 0x80
#define set_dd_line2_pos1 0xC0
#define button PORTAbits.RA4

char BTemp [40], BRh [40], BSolar [40];
int i1,i2,sum1,sum2,temp,rh,Solar;

void lcd_write(unsigned char c)
{
   unsigned char temp2;
   LCD_RS = 0;
   Delay10TCYx(4);

   temp2 = c;
   temp2 = temp2 >>4;
   PORTD=temp2 & 0x0F;

   Delay1KTCYx(1);
   lcd_strobe();
   Delay1KTCYx(1);

   temp2 = c;
   PORTD = temp2 & 0x0F;
   Delay1KTCYx(1);
   lcd_strobe();
   Delay1KTCYx(1);


}
void lcd_clear(void)
{
   LCD_RS = 0;
   Delay10TCYx(4);
   lcd_write(0x01);
   Delay1KTCYx(2);
}

void lcd_putch(char c)
{
char temp1;

   LCD_RS = 1;
   Delay10TCYx(4);

   temp1 =c;
   temp1 = temp1>>4;
   PORTD = temp1 & 0x0F;

   Delay1KTCYx(1);
   lcd_strobe();
   Delay1KTCYx(1);

   temp1=c;
   PORTD= temp1 & 0x0F;
   Delay1KTCYx(1);
   lcd_strobe();
   Delay1KTCYx(1);
}

void lcd_goto(unsigned char LCD_POS)
{
   LCD_RS = 0;
   Delay10TCYx(4);

   lcd_write(LCD_POS);
}

void lcd_strobe(void)
{
   LCD_EN =1;
   Delay10TCYx(4);

   LCD_EN =0;
   Delay10TCYx(4);
}

void lcd_init(void)
{
   TRISD = 0;          // all output
   LCD_RS=0;
   LCD_WR=0;

   Delay1KTCYx(250);
   Delay1KTCYx(250);
   Delay1KTCYx(250);
   Delay1KTCYx(250);

   PORTD = 0x03;

   lcd_strobe();
   Delay1KTCYx(250);

   PORTD=0x03;
   lcd_strobe();
   Delay1KTCYx(250);

   PORTD=0x03;
   lcd_strobe();
   Delay1KTCYx(250);

   PORTD=0x02;
   lcd_strobe();
   Delay1KTCYx(250);
   Delay1KTCYx(250);

   lcd_write(0x28);
   Delay1KTCYx(20);
   lcd_write(0x01);
   Delay1KTCYx(20);

   Delay1KTCYx(20);
   lcd_write(0x0F);

   Delay1KTCYx(20);

   lcd_write(0x06);

   Delay1KTCYx(20); 

}



int adc1 (void)
{
	//TRISA= 0xFF;

	ADCON0= 0b11110001;
	ADCON1= 0b00000000;
	
	ADCON0bits.GO =1;
	
	while(ADCON0bits.GO == 1);
	i1=ADRESH;
	PIR1bits.ADIF = 0;

	ADCON0= 0b11111001;
	ADCON1= 0b00000000;
	
	ADCON0bits.GO =1;
	
	while(ADCON0bits.GO == 1);
	i2=ADRESH;
	PIR1bits.ADIF = 0;
}




int calculate (void)
{
	sum1=i1|i2;
	sum2=i2|i1;
}

int motor (void)
{
	//#define value 0x7F
	//calculate();
	PORTBbits.RB0=1;

	
	while(i1>i2)
	{
		//PORTBbits.RB0=1;
		Delay1KTCYx(500); 
		PORTBbits.RB1=1;
		PORTBbits.RB2=0;
		Delay1KTCYx(500);
		adc1();
		//adc2();
	}
	

		//PORTBbits.RB0=1;
		Delay1KTCYx(500);
		PORTBbits.RB2=0;
		PORTBbits.RB1=0;
		Delay1KTCYx(500);


}

int temperature (void)
{


	TRISAbits.TRISA0=1;
	ADCON0=0b11000001;
	ADCON1=0b00001110;
	ADCON0bits.GO=1;
	while(PIR1bits.ADIF == 0 );
	temp=(float)ADRESH/256.0*50.0;
	PIR1bits.ADIF=0;

}

int humidity (void)
{
	TRISAbits.TRISA5=1;
	ADCON0=0b11100001;
	ADCON1=0b00000000;
	ADCON0bits.GO=1;
	while(PIR1bits.ADIF == 0 );
	rh=(float)ADRESH/256.0*50.0;
	PIR1bits.ADIF=0;
}

void main(void)
{


char A,B,b,c;
unsigned char SizeBTemp, SizeBRh;
SizeBTemp= 16;
SizeBRh  = 16;


TRISB=0x00;
PORTB=0x00;

   

   while(1)
{


	temperature();
	Delay1KTCYx(1);
	humidity();
	ADCON1= 0x07;
	TRISAbits.TRISA1=0;
	TRISAbits.TRISA2=0;
	TRISAbits.TRISA3=0;
	
   LCD_EN=0;
   LCD_RS=0;
   LCD_WR=0;

   Delay1KTCYx(1);
   lcd_init();

   LCD_RS=1;

   Delay1KTCYx(1);	
 

	
	sprintf(BTemp,"Temp= %d Celcius  \0",temp);
  
	lcd_goto(set_dd_line1_pos1);
    for(b=0; b< SizeBTemp; b++)
       {
           A=BTemp[b];
           Delay1KTCYx(250);
           lcd_putch(A);
       }
 
 
       Delay1KTCYx(250);
       Delay1KTCYx(250);
       Delay1KTCYx(250);


	sprintf(BRh,"Rh= %d         %\0",rh);

	lcd_goto(set_dd_line1_pos1);
    for(c=0; c< SizeBRh; c++)
       {
           B=BRh[c];
           Delay1KTCYx(250);
           lcd_putch(B);
       }
 
 
       Delay1KTCYx(250);
       Delay1KTCYx(250);
       Delay1KTCYx(250);
   
	Delay1KTCYx(250);


	
    lcd_goto(set_dd_line1_pos1);
   }
}