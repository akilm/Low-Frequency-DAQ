#include <avr/io.h>
#include <stdint.h>                     // needed for uint8_t
#include <avr/interrupt.h>
#define FOSC 16000000                       // Clock Speed
#define BAUD 9600                
#define MYUBRR FOSC/16/BAUD -1
volatile int i=0,d[500],flag=0;;
void adc_init()
{
    ADMUX = (1<<REFS0);
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}
uint16_t adc_read(uint8_t ch)
{
  ch &= 0b00000111;  
  ADMUX = (ADMUX & 0xF8)|ch; 
  ADCSRA |= (1<<ADSC);
  while(ADCSRA & (1<<ADSC));
  return (ADC);
}
void USART_Transmit(  uint8_t data )
{ while ( !( UCSR0A & (1<<5)) )
    ;
  UDR0 = data;
}
ISR(TIMER0_COMPA_vect)
{   if(i<500)
    {d[i] = adc_read(0);
    }
    else
    {flag=1;
     TIMSK0&=~(1<<1);
    }
    i++;
    
}
int main(void)
{ adc_init();
  UBRR0H = (MYUBRR >> 8);
  UBRR0L = MYUBRR;
  UCSR0B |= (1 << RXEN0) | (1 << TXEN0);                       
  UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);

  DDRB |= (1 << 1);
  TCCR1A |= (1 << WGM11) | (1 << COM1A1);
  TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS12);
  ICR1 = 1249;
  OCR1A= 624;   //setting timer 1 to generate a square pulse of 50 hz
  TCCR0A|=(1<<WGM01);
  TCCR0B|=(1<<CS02);
  TIMSK0|=(1<<1);
  OCR0A = 62;  
  TCNT0=0;
  sei();//prescaler 256 with sampling frequency = 250 hz > 2*100 hz
  while(1)
  { if(flag)
        { for(int i=0;i<500;i++)
            {   
                uint8_t l= d[i]/100;
                USART_Transmit(l);
                uint8_t u= d[i]%100;
                USART_Transmit(u);
               
            }

              flag=0;
        }
  }
  return 0;
 
}
