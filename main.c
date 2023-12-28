/*
 * main.c
 *
 *  Created on: 23 Dec 2023
 *      Author: Ziad Yakoot
 */

#include <util/delay.h>

#include "STD_types.h"
#include "bitMath.h"
#include "DIO_interface.h"
#include "PORT_interface.h"
#include "LCD_interface.h"
#include "ADC_interface.h"
#include "KYP_interface.h"

static uint8 comparPass(uint8 Saved_Pass[],uint8 passArr[])
{
	uint8 state =0;
	uint8 store;
	for(int i=0;i<4;i++)
	{
		if(passArr[i]==Saved_Pass[i])
		{
			if(state==0)
			{
				store=1;
			}
		}
		else
		{
			state=1;
			store=0;
		}
	}
	return store;
}




int main(void)
{

	PORT_init();
	ADC_init();
	LCD_voidinit();
	DIO_setPinDirection(DIO_PORTA,PIN1,OUTPUT);// LEDS
	DIO_setPinDirection(DIO_PORTA,PIN2,OUTPUT);//FAN

	uint8 ADC_value=0;
	uint32 analog=0;
	uint8 temp;
	uint8 Saved_Pass[4]={'1','2','3','4'};
    uint8 passArr[4];
    uint8 passStatus=2;
    uint8 iterator=0;
    uint8 trails=0;
    uint8 option=0;

    LCD_voidString("WELCOME TO SMART");
    LCD_setPosition(2,7);
    LCD_voidString("HOME");
    _delay_ms(2000);
    LCD_ClearScreen();
    LCD_voidString("Enter Password:");
    LCD_setPosition(2,1);
    while(iterator<4)
    {
    	do
    	{
    	 passArr[iterator]=getPressed();
    	}while(passArr[iterator] ==0xff);
    	LCD_sendData('*');
    	iterator++;
    }
    _delay_ms(1000);
    LCD_ClearScreen();
    _delay_ms(1);
    while(1)
    {
    	passStatus=comparPass(Saved_Pass,passArr);
    	if(passStatus == FALSE)
    	{
    		trails++;
    		if(trails ==3)
    		{
    			break;
    		}
    		LCD_voidString("Wrong Password");
    		_delay_ms(1000);
    		LCD_ClearScreen();
    		LCD_voidString("Password again");
    		LCD_setPosition(2,1);
    		iterator=0;
		  while(iterator<4)
			{
				do
				{
				 passArr[iterator]=getPressed();
				}while(passArr[iterator] ==0xff);
				LCD_sendData('*');
				iterator++;
			}
		  _delay_ms(1000);
		  LCD_ClearScreen();

    		}
    	else if(passStatus == TRUE)
    	{
    		LCD_voidString("Choose Option:");
    		LCD_setPosition(2,1);
    		LCD_voidString("1-Display Temp");
    		 _delay_ms(1000);
    		 LCD_ClearScreen();

    		 LCD_voidString("2-FAN ON");
    		 LCD_setPosition(2,1);
    		 LCD_voidString("3-FAN OFF");
    		 _delay_ms(1000);
    		  LCD_ClearScreen();
    		  LCD_voidString("4-Light ON");
    		  LCD_setPosition(2,1);
    		  LCD_voidString("5-Light OFF");
    		  _delay_ms(1000);
    		  LCD_ClearScreen();
    		  do
    		  {
    			  option=getPressed();
    			  ADC_value=ADC_StartConversion(ADC0);
    		  }while(option==0xff);
    		  switch(option)
    		  {
    		  case '1':
    			  analog=(uint32)ADC_value * 5000UL /256UL;
    			  temp=analog/10;
    			  LCD_voidString("Temp=");
    			  LCD_setPosition(1,6);
    			  LCD_WriteNum(temp);
    			  LCD_voidString(" C");
    			  _delay_ms(2000);
    			  LCD_ClearScreen();
    			  if(temp>30)
    			  {
    			    DIO_setPinValue(DIO_PORTA,PIN2,HIGH);
    			  }
    			  else if(temp<30)
    			  {
    				  DIO_setPinValue(DIO_PORTA,PIN2,LOW);
    			  }
    			  break;

    		  case '2':
    			  DIO_setPinValue(DIO_PORTA,PIN2,HIGH);
    			  break;
    		  case '3':
    			  DIO_setPinValue(DIO_PORTA,PIN2,LOW);
    			  break;
    		  case '4':
    			  DIO_setPinValue(DIO_PORTA,PIN1,HIGH);
    			  break;
    		  case '5':
				  DIO_setPinValue(DIO_PORTA,PIN1,LOW);
				  break;
    		  default :
    			  break;

    		  }


    	}

    	}


    return 0;
}
