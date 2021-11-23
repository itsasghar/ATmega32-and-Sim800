/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : smart led
Version : 
Date    : 23/08/2017
Author  : 
Company :  Mohsen & aliasghar
Comments: 


Chip type               : ATmega32A
Program type            : Application
AVR Core Clock frequency: 8/000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*******************************************************/

#include <mega32a.h>
#include <stdlib.h>
#include <stdio.h>
#include <delay.h>
#include <string.h>
// Alphanumeric LCD functions
#include <alcd.h>
// Declare your global variables here
char str_temp[10];
float temp=0.0000;
float adcvalue=0.0000;
char Enter=13;
char Double_quote=34;
char Ctrlz=26;
//char space=32;
char sms[100];
int sms_number=1;
int n=0;
int i1=0; 
int j;
int n1=0;
int n2=0;
int n3=0;

// External Interrupt 0 service routine
interrupt [EXT_INT0] void ext_int0_isr(void)
{
// Place your code here


lcd_gotoxy(0,0);
printf("ATE0%c",Enter);
lcd_puts("Get sms ...");
delay_ms(1000);
printf("AT+CMGF=1%c",Enter); //When We Don’t Have Cable USB To TTL!
lcd_clear();   
printf("AT+CMGR=%d%c",sms_number,Enter);  
printf("AT+CMGW=%d%c",sms_number,Enter);  
sms_number++;

n1=0;
n2=0;
n3=0;
//printf("AT+CMGDA=%cDELL%cALL%c",Double_quote,space,Double_quote);
}
#define DATA_REGISTER_EMPTY (1<<UDRE)
#define RX_COMPLETE (1<<RXC)
#define FRAMING_ERROR (1<<FE)
#define PARITY_ERROR (1<<UPE)
#define DATA_OVERRUN (1<<DOR)

// USART Receiver buffer
#define RX_BUFFER_SIZE 112
char rx_buffer[RX_BUFFER_SIZE];

#if RX_BUFFER_SIZE <= 256
unsigned char rx_wr_index=0,rx_rd_index=0;
#else
unsigned int rx_wr_index=0,rx_rd_index=0;
#endif

#if RX_BUFFER_SIZE < 256
unsigned char rx_counter=0;
#else
unsigned int rx_counter=0;
#endif
// This flag is set on USART Receiver buffer overflow
//bit rx_buffer_overflow;
// USART Receiver interrupt service routine
interrupt [USART_RXC] void usart_rx_isr(void)
{  
    sms[n]=UDR;
    n++;   
              
}


  


 

#ifndef _DEBUG_TERMINAL_IO_
// Get a character from the USART Receiver buffer
#define _ALTERNATE_GETCHAR_
#pragma used+
char getchar(void)
{
char data;
while (rx_counter==0);
data=rx_buffer[rx_rd_index++];
#if RX_BUFFER_SIZE != 256
if (rx_rd_index == RX_BUFFER_SIZE) rx_rd_index=0;
#endif
#asm("cli")
--rx_counter;
#asm("sei")
return data;
}
#pragma used-
#endif

// Standard Input/Output functions
#include <stdio.h>

// Voltage Reference: AVCC pin
#define ADC_VREF_TYPE ((0<<REFS1) | (1<<REFS0) | (0<<ADLAR))

// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | ADC_VREF_TYPE;
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
// Start the AD conversion
ADCSRA|=(1<<ADSC);
// Wait for the AD conversion to complete
while ((ADCSRA & (1<<ADIF))==0);
ADCSRA|=(1<<ADIF);
return ADCW;
}

void main(void)
{
// Declare your local variables here  
// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRC=(0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=In Bit6=Out Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(0<<DDD7) | (1<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=T Bit6=0 Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

// External Interrupt(s) initialization
// INT0: On
// INT0 Mode: Falling Edge
// INT1: Off
// INT2: Off
GICR|=(0<<INT1) | (1<<INT0) | (0<<INT2);
MCUCR=(0<<ISC11) | (0<<ISC10) | (1<<ISC01) | (0<<ISC00);
MCUCSR=(0<<ISC2);
GIFR=(0<<INTF1) | (1<<INTF0) | (0<<INTF2);

// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: On
// USART Transmitter: On
// USART Mode: Asynchronous
// USART Baud Rate: 9600
UCSRA=(0<<RXC) | (0<<TXC) | (0<<UDRE) | (0<<FE) | (0<<DOR) | (0<<UPE) | (0<<U2X) | (0<<MPCM);
UCSRB=(1<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (1<<RXEN) | (1<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);
UCSRC=(1<<URSEL) | (0<<UMSEL) | (0<<UPM1) | (0<<UPM0) | (0<<USBS) | (1<<UCSZ1) | (1<<UCSZ0) | (0<<UCPOL);
UBRRH=0x00;
UBRRL=0x33;

// ADC initialization
// ADC Clock frequency: 1000/000 kHz
// ADC Voltage Reference: AVCC pin
// ADC Auto Trigger Source: Free Running
ADMUX=ADC_VREF_TYPE;
ADCSRA=(1<<ADEN) | (0<<ADSC) | (1<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
SFIOR=(0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);

// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTC Bit 0
// RD - PORTC Bit 1
// EN - PORTC Bit 2
// D4 - PORTC Bit 3
// D5 - PORTC Bit 4
// D6 - PORTC Bit 5
// D7 - PORTC Bit 6
// Characters/line: 16
lcd_init(16);

// Global enable interrupts
#asm("sei")
       

while (1)
      {
      //printf("AT+CMGD=1,4%c",Enter); //Manual settings(When We Have Cable USB To TTL!)
      //printf("AT+CMGD=1%c",Enter);  //Manual settings(When We Have Cable USB To TTL!)
      if(sms_number==20)
       {
         printf("AT+CMGD=1,4%c",Enter); //Because the memory is overwhelmed!
         sms_number=1;
       } 
       
       n=0;  
       adcvalue=read_adc(0); 
       temp=(100*((adcvalue*5)/1023));
       if(temp>=30&i1==0)  
            {  
        i1=1;
        j=temp;
        printf("AT%c",Enter);
        delay_ms(100);  
        printf("AT+CMGF=1%c",Enter);  
        delay_ms(100);  
        printf("AT+CMGS=%c09379103720%c%c",Double_quote,Double_quote,Enter); 
        delay_ms(100);
        printf("Dama> %d%c",j,Ctrlz);  
        delay_ms(100);
            }     
       ftoa(temp,4,str_temp);
       lcd_gotoxy(0,1);
       lcd_puts("temp:");
       lcd_puts(str_temp);        
       delay_ms(500);   
if(strstr(sms,"9379103720"))
{
       if(strstr(sms,"on")&&n1==0)  
       {
        PORTD.6=1;
        n1=1;  
        printf("AT+CMGS=%c09379103720%c%c",Double_quote,Double_quote,Enter); 
        delay_ms(100);
        printf("LED is On now!%c",Ctrlz); 
        delay_ms(100);
        }
       if(strstr(sms,"off")&&n1==0)
       {
        PORTD.6=0;
        n1=1;
        printf("AT+CMGS=%c09379103720%c%c",Double_quote,Double_quote,Enter); 
        delay_ms(100);
        printf("LED is Off now!%c",Ctrlz); 
        delay_ms(100); 
       }     
}



}
}                                                   


 