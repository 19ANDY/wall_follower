#include<avr/io.h>
#include<compat/deprecated.h>
#include<util/delay.h>
#include"uart.h"
#include"uart.c"
#include<avr/interrupt.h>


void read_ultra()
{
	float count=0;
	unsigned int time;
	char a[3];
	
	sbi(PORTA,0);
	_delay_us(10);
	cbi(PORTA,0);
	
	while(bit_is_clear(PINA,1));
	TCCR0=(1<<CS00)|(1<<CS02);
	TCNT0=0;
	
	while(bit_is_set(PINA,1));
	TCCR0=0X00;
	
	count=TCNT0;
	time=count*0.0678*1024;
	
	itoa(time,a,10);
	uart_puts(a);
	uart_puts("\r\n");
	
}


void init_pwm()
{
	DDRD=0XFF;
	TCCR1A=(1<<COM1A1)|(1<<WGM10);
	TCCR1B=(1<<CS10);
	TCNT0=0;
}
	
	
void main()
{
sbi(DDRA,0);
cbi(DDRA,1);
init_pwm();
unsigned char c,str[5]={0};
unsigned char s_rx=0;
uart_init(UART_BAUD_SELECT(9600,F_CPU));
sei();


	
	while(1)
	{
		c=uart_getc();	
			
		if(c!=0)
		{
			if(c=='S')
			{
				uart_putc('R');
			}
			
			else if(c=='U')
			{
				while(c!='B')
				{
					c=uart_getc();
					read_ultra();
				}
			}
			
			else if(c=='O')
			{
				sbi(PORTD,6);
				cbi(PORTD,7);
				OCR1A=255;
			}
			
			else if(c=='F')
			{
				OCR1A=0;
			}
			
		}
		
	}
}