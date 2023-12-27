/*
 * LCD_cgf.h
 *
 *  Created on: 12 Dec 2023
 *      Author: Ziad Yakoot
 */

#ifndef LCD_CFG_H_
#define LCD_CFG_H_

#define LCD_Mode                            4                       /*SET LCD Mode ( 4 bits , 8 bits)*/


#define LCD_CONTROL_PORT                 DIO_PORTC
/*RS RW EN*/

#define LCD_DATA_PORT                    DIO_PORTD

/*LCD Commands*/
#define SET_HOME        	             0x02
#define Four_bits            	       	 0x28
#define DISPLAY_ON_CURSOR_OFF   	     0x0c
#define DISPLAY_CLEAR               	 0x01
#define ENTRY_MODE                  	 0x06
#define SET_CURSOR                       0x80

/*Control Pins*/
#define LCD_RS                     	 	 PIN1
#define LCD_RW                      	 PIN2
#define LCD_EN                      	 PIN3




#define LCD_ROW_1                           1
#define LCD_ROW_2                           2

#define LCD_COL_1                           1
#define LCD_COL_2                           2
#define LCD_COL_3                           3
#define LCD_COL_4                           4
#define LCD_COL_5                           5
#define LCD_COL_6                           6
#define LCD_COL_7                           7
#define LCD_COL_8                           8
#define LCD_COL_9                           9
#define LCD_COL_10                          10
#define LCD_COL_11                          11
#define LCD_COL_12                          12
#define LCD_COL_13                          13
#define LCD_COL_14                          14
#define LCD_COL_15                          15
#define LCD_COL_16                          16









#endif /* LCD_CFG_H_ */
