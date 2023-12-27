/*
 * LCD_program.c
 *
 *  Created on: 12 Dec 2023
 *      Author: Ziad Yakoot
 */

#ifndef LCD_PROGRAM_C_
#define LCD_PROGRAM_C_
#include<util/delay.h>
#include "STD_types.h"
#include "bitMath.h"
#include "DIO_interface.h"
#include "LCD_cfg.h"
#include "LCD_interface.h"



void LCD_voidinit                  (void)
{
#if  LCD_Mode == 4

	_delay_ms(50);
	DIO_setPinDirection(LCD_DATA_PORT ,PIN4 ,OUTPUT);
	DIO_setPinDirection(LCD_DATA_PORT ,PIN5 ,OUTPUT);
	DIO_setPinDirection(LCD_DATA_PORT ,PIN6 ,OUTPUT);
	DIO_setPinDirection(LCD_DATA_PORT ,PIN7 ,OUTPUT);

	DIO_setPinDirection(LCD_CONTROL_PORT ,LCD_RS ,OUTPUT);
	DIO_setPinDirection(LCD_CONTROL_PORT ,LCD_RW ,OUTPUT);
	DIO_setPinDirection(LCD_CONTROL_PORT ,LCD_EN ,OUTPUT);

	LCD_sendCommand(SET_HOME);                     //Set Home
	_delay_ms(30);
	LCD_sendCommand(Four_bits);                    //Function set
	_delay_ms(1);
	LCD_sendCommand(DISPLAY_ON_CURSOR_OFF);        //display ON
	_delay_ms(1);
	LCD_sendCommand(DISPLAY_CLEAR);                //Display clear
	_delay_ms(10);
	LCD_sendCommand(ENTRY_MODE);                   //Entry Mode
	_delay_ms(1);

#endif
}



void LCD_sendData                  (uint8 copy_Data)
{
#if LCD_Mode == 4
	DIO_setPinValue(LCD_CONTROL_PORT ,LCD_RS,HIGH);
	DIO_setPinValue(LCD_CONTROL_PORT ,LCD_RW ,LOW);
	DIO_setHighFourPins(LCD_DATA_PORT,(copy_Data>>4));
	LCD_SendFallingEdge();
	DIO_setHighFourPins(LCD_DATA_PORT,copy_Data);
	LCD_SendFallingEdge();
#endif
}


void LCD_sendCommand                 (uint8 copy_Data)
{
#if LCD_Mode == 4
	DIO_setPinValue(LCD_CONTROL_PORT ,LCD_RS,LOW);
	DIO_setPinValue(LCD_CONTROL_PORT ,LCD_RW ,LOW);
	DIO_setHighFourPins(LCD_DATA_PORT,(copy_Data>>4));
	LCD_SendFallingEdge();
	DIO_setHighFourPins(LCD_DATA_PORT,copy_Data);
	LCD_SendFallingEdge();
#endif
}

void LCD_SendFallingEdge (void)
{
	DIO_setPinValue(LCD_CONTROL_PORT ,LCD_EN ,HIGH);
	_delay_ms(1);
	DIO_setPinValue(LCD_CONTROL_PORT ,LCD_EN ,LOW);
	_delay_ms(1);
}

void LCD_ClearScreen(void)
{
	LCD_sendCommand(DISPLAY_CLEAR);
}

void LCD_voidString                (uint8 * copy_String)
{
	uint8 stringIndex = 0;
	while(copy_String[stringIndex]!= '\0')
	{
		LCD_sendData(copy_String[stringIndex]);
		stringIndex ++;
	}
}

void LCD_voidSpace                  (void                )
{
	LCD_sendData(' ');
}
void LCD_setPosition                (uint8 copy_Row, uint8 copy_col)
{
	uint8 loc_data;
	if(copy_Row>2 ||copy_Row<1 ||copy_col>16||copy_col<1)
	{
		loc_data=SET_CURSOR;
	}
	else if(copy_Row ==LCD_ROW_1)
	{
		loc_data=(SET_CURSOR) + (copy_col -1);
	}
	else if(copy_Row ==LCD_ROW_2)
	{
		loc_data=((SET_CURSOR) +(64) + (copy_col -1));
	}
	LCD_sendCommand(loc_data);
	_delay_ms(1);

}
void LCD_WriteNum                   (uint8 copy_number   )
{
  if(copy_number<10)
  {
	  LCD_sendData(copy_number+'0');
	  _delay_ms(1000);
  }
  else if (copy_number<100)
  {
	  LCD_sendData(copy_number/10+'0');
	  LCD_sendData(copy_number%10+'0');
	  _delay_ms(1000);
  }
  else if(copy_number<1000)
  {
	  LCD_sendData(copy_number/100+'0');
	  LCD_sendData((copy_number%100)/10+'0');
	  LCD_sendData(copy_number%10+'0');
	  _delay_ms(1000);
  }
}
#endif /* LCD_PROGRAM_C_ */
