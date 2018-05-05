#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "uart.c"
#include "lcd.c"
#include "lcd.h"
#include "math.h"
#include<compat/deprecated.h>


char buff0[20]={0};
char buff1[20]={0};

unsigned char Trig1=0;
unsigned char Trig2=0;

unsigned char Flag=0;
unsigned int result;

unsigned int distance_u1=0;
unsigned int distance_u2=0;



int Width_1(unsigned char X)
{
	int i;
	
	for(i=0;i<600000;i++)
	{
		if(!(PINA & (1<<X)))
		continue;
		else
		break;

	}	
	 TCCR1A=0X00;
	 TCCR1B=(1<<CS11);	
	 TCNT1=0x00;			

	for(i=0;i<600000;i++)
	{
		if(PINA & (1<<X))
		{
			if(TCNT1 > 60000) 
			break;
			else
			continue;
				
		}
		else
			break;
	}

     result=TCNT1;
	 TCCR1B=0x00;

}

void forward()
{
	sbi(PORTD,4);
	sbi(PORTD,5);

	cbi(PORTD,2);
	sbi(PORTD,3);

	cbi(PORTD,6);
	sbi(PORTD,7);

}

void backword()
{
	sbi(PORTD,4);
	sbi(PORTD,5);

	sbi(PORTD,2);
	cbi(PORTD,3);

	sbi(PORTD,6);
	cbi(PORTD,7);
}

void right()
{
	sbi(PORTD,4);

	cbi(PORTD,2);
	sbi(PORTD,3);

	cbi(PORTD,6);
	cbi(PORTD,7);
}

void left()
{
	sbi(PORTD,5);

	cbi(PORTD,2);
	cbi(PORTD,3);

	cbi(PORTD,6);
	sbi(PORTD,7);
}

void stop()
{
PORTD=0X00;
}

void Triger_1(void)
{

		 sbi(PORTA,0);
		_delay_us(10);
		 cbi(PORTA,0);
		_delay_us(10);
		
}

void Triger_2(void)
{
		 sbi(PORTA,1);
		_delay_us(10);
		 cbi(PORTA,1);
		_delay_us(10);
}	

void init_motor(void)
{
	sbi(DDRD,2);
	sbi(DDRD,3);
	sbi(DDRD,4);
	sbi(DDRD,5);
	sbi(DDRD,6);
	sbi(DDRD,7);
}

void init_Ultrasonic(void)
{	
	sbi(DDRA,0);	//	Triger of U1
	cbi(DDRA,2);	//	Echo Of U1
	
	sbi(DDRA,1);	// Triger of u2
	cbi(DDRA,3);	// Echo of u2
}

void Read_Ultrasonic()
{
	if(Flag==0)
	{
		Triger_1();
		
		Width_1(2);
		
		distance_u1=result;
		
		distance_u1=(distance_u1/58);
		
		Flag=1;
		
		_delay_ms(10);
	} 
	
	if(Flag==1)
	{
		Triger_2();
		
		Width_1(3);
		
		distance_u2=result;
		
		distance_u2=(distance_u2/58);
		
		Flag=0;
		
		_delay_ms(10);
	}
		
}
	
void main()
{   			

uart_init(UART_BAUD_SELECT(9600,F_CPU));
uart_puts("start");

init_Ultrasonic();
init_motor();

/*
	lcd_init(LCD_DISP_ON);

	
	lcd_clrscr();
	
	lcd_gotoxy(6,0);
	lcd_puts("Wall");
	lcd_gotoxy(4,1);
	lcd_puts("Follower");
	
	_delay_ms(4000);
*/
	
	while(1)
	{    

		Read_Ultrasonic();
	
	/*	itoa(distance_u1,buff0,10);
		
		if(distance_u1<200)
		{
			lcd_clrscr();	
			lcd_gotoxy(0,0);
			lcd_puts(buff0);
		}
		
		itoa(distance_u2,buff1,10);
		
		if(distance_u2<200)
		{
			lcd_clrscr();
			lcd_gotoxy(0,1);
			lcd_puts(buff1);
		}
	*/	
	
				
			if(distance_u1>0 && distance_u1<=5 && distance_u2>9)
			{
				right();
				_delay_ms(200);
				left();				
			}
			
			else if(distance_u1>5 && distance_u1<=9 && distance_u2>9)
			{
				right();
				_delay_ms(50);
				left();	
			}
			
						
			else if(distance_u1>9 && distance_u1<=11 && distance_u2>9)
			{
				forward();
			}
				
			else if(distance_u1>=12 && distance_u1<=15 && distance_u2>9)
			{
				left();
				_delay_ms(50);
				right();
			}
			
			else if(distance_u1>15 && distance_u2>9)
			{
				left();
				_delay_ms(400);
				right();
				_delay_ms(100);
			}
			
			else if(distance_u1>=200 && distance_u2>9)
			{
				stop();
			}
			
			else if(distance_u2<=10)
			{
			
				stop();
				_delay_ms(100);
				backword();
				_delay_ms(200);
				right();
				_delay_ms(800);
				left(300);
				
			}
			_delay_ms(10);
		}
}
		