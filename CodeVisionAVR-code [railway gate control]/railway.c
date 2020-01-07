#include <mega32.h>
#include <alcd.h>
#include <delay.h> 
#include <stdlib.h>


#define push1   PIND.2
#define push2   PIND.3
#define push3   PIND.4
#define push4   PIND.5

#define buzz_ddr  DDRB
#define buzz PORTB

// Declare your global variables here
float speed=0;
char disp[16];
int second=0, time=0;
int distance=10; // distance= 10 meter

// Timer1 overflow interrupt service routine
interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{
// Place your code here
TCNT1H=0xC2;
TCNT1L=0xF7;   
   
   second++;
 
  if(second==2){
    PORTC = 0b00000000;   
  }
  
}

void main(void)
{
    buzz_ddr=0xFF;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 15.625 kHz
// Mode: Normal top=0xFFFF
// OC1A output: Disconnected
// OC1B output: Disconnected
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer Period: 4.1943 s
// Timer1 Overflow Interrupt: On
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (1<<CS12) | (0<<CS11) | (1<<CS10);
TCNT1H=0xC2;
TCNT1L=0xF7;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00; 
      
// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (1<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);


//// External Interrupt(s) initialization
//// INT0: Off
//// INT1: Off
//// INT2: Off
//MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
//MCUCSR=(0<<ISC2);


        lcd_init(16);
        lcd_gotoxy(0,0); 
        
        DDRC=0xFF;
        DDRD=0x00;

// Global enable interrupts
#asm("sei")

while (1)

      { 
      if(push1==1)
      { 
      
      
      while (1)
      {
      // Place your code here
        if(push1==1){ 

        lcd_clear();            
        lcd_gotoxy(0,0);              
        lcd_putsf("Train Comming");          
        lcd_gotoxy(0,1);          
        lcd_putsf("Gate Close");
        delay_ms(10);
                
         //clockwise rotation
         PORTC = 0b00000101;
         second=0;   
         //delay_ms(2000);         // wait 2s      
         //PORTC = 0b00000000;  
         
         buzz = 0xFF;       
         }
           
       if(push3==1){
         lcd_clear();             
         lcd_gotoxy(0,0);              
         lcd_putsf("Train speed:");
         delay_ms(5);    
         lcd_gotoxy(0,1); 
         time=second;
         second=0;
//         itoa(time,disp);
//         lcd_puts(disp);
         delay_ms(500);                                
         speed=distance*3.6;    //speed= km/hr 
         speed=speed/time;
         ftoa(speed,2,disp);
         lcd_puts(disp);
         delay_ms(5);
         lcd_gotoxy(8,1);          
         lcd_putsf("km/hr"); 
         delay_ms(10);   
         second=0;        
         } 
         
        
        if(push2==1){   
        
        buzz = 0x00; 
         
        lcd_clear();            
        lcd_gotoxy(0,0);              
        lcd_putsf("Train departure");           
        lcd_gotoxy(0,1);          
        lcd_putsf("Gate Open"); 
          
       // counter-clockwise rotation
          PORTC = 0b00001010;    
          delay_ms(2000);         // wait 2s
          PORTC = 0b00000000; 
           
          break;
       }

      }
      } 
      
      ////////////////////////////////////////////////////////
      
      if(push2==1)
      {
      while (1)
      {
      // Place your code here
        if(push2==1){ 

        lcd_clear();            
        lcd_gotoxy(0,0);              
        lcd_putsf("Train Comming");          
        lcd_gotoxy(0,1);          
        lcd_putsf("Gate Close");
        delay_ms(10);
                
         //clockwise rotation
         PORTC = 0b00000101;
         second=0;   
         //delay_ms(2000);         // wait 2s      
         //PORTC = 0b00000000;  
            
         buzz = 0xFF;     
         }
           
       if(push4==1){
         lcd_clear();             
         lcd_gotoxy(0,0);              
         lcd_putsf("Train speed:");
         delay_ms(5);    
         lcd_gotoxy(0,1); 
         time=second;
         second=0;
//         itoa(time,disp);
//         lcd_puts(disp);
         delay_ms(500);                                
         speed=distance*3.6/time;    //speed= km/hr 
         //speed=speed/time;
         ftoa(speed,2,disp);
         lcd_puts(disp);
         delay_ms(5);
         lcd_gotoxy(8,1);          
         lcd_putsf("km/hr"); 
         delay_ms(10);   
         second=0;        
         } 
         
        
        if(push1==1){  
         
        buzz = 0x00; 
        
        lcd_clear();            
        lcd_gotoxy(0,0);              
        lcd_putsf("Train departure");           
        lcd_gotoxy(0,1);          
        lcd_putsf("Gate Open"); 
          
       // counter-clockwise rotation
          PORTC = 0b00001010;    
          delay_ms(2000);         // wait 2s
          PORTC = 0b00000000; 
          
          break;
       }
       }
       } 
}
}
