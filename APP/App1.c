/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 24-11-2023            */
/*          Version: 1.0                */
/*          Module: 7 Apps              */
/****************************************/
//Task1 to Task7
//Task1 : 
//Task2 :
//Task3 :
//Task4 :
//Task5 :
//Task6 :
//Task7 :


#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdlib.h>

#include "../MCAL/DIO/STD_Types.h"
#include "../MCAL/DIO/DIO_Header.h"
#include "../MCAL/ADC/ADC_INIT.h"
#include "../MCAL/ADC/ADC_CONFIG.h"
#include "../MCAL/INTERRUPT/Interrupt_H.h"
#include "../MCAL/TIMER/Timer_Init.h"
#include "../HAL/Seven_Segment/Seven_Segment.h"
#include "../HAL/LCD16/LCD_Driver.h"
#include "../HAL/KEYPAD/KEYPAD.h"
#include "../HAL/Buttons/Buttons.h"
#include "../HAL/LEDS/LEDS.h"
#include "Helper.h"

uint8 button0_State;
uint8 button1_State;
uint8 button2_State;

void TASK7_Password_Checker_LCD_KEYPAD()
{
	LCD_Init();
	KEYPAD_Init();
	uint8 x='\0';
	uint8 registered_username[4] = "1234";
	uint8 registered_password[4] = "5432";
	while(1)
	{
		uint8 username[6] = "";
		uint8 password[6] = "";
		uint8 username_counter = 0;
		uint8 password_counter = 0;
		uint8 username_check = 0;
		uint8 password_check = 0;
		LCD_Send_String("User:");
		while(username_counter <= 6)
		{
			x='\0';
			x = KEYPAD_Get_Pressed_Key();
			if(x == '\0') continue;

			
			if(x >= '0' && x <='9')
			{
				LCD_Send_Char(x);
				username[username_counter] = x;
				username_counter++;
			}
			else if(x == '*' && username_counter > 0)
			{
				LCD_Delete_Last_Written();
				username[username_counter] = '\0';
				username_counter--;
			}
			else if(x >= 'A' && x <='D')
			{
				for(int i=0;i<username_counter;i++){
					if(username[i] == registered_username[i])
					continue;
					else username_check = 1;
				}
				break;
			}
			if(username_counter > 5)
			{
				username_check = 1;break;
			}
		}
		
		LCD_Send_Clear_Screen();
		if(username_check == 1)
		{
			LCD_Send_String("Wrong User");
			_delay_ms(3000);
			LCD_Send_Clear_Screen();
		}
		else if(username_check == 0)
		{
			LCD_Send_String("Correct User");
			_delay_ms(3000);
			LCD_Send_Clear_Screen();
			LCD_Send_String("Password:");
			while(password_counter <= 6)
			{
				x='\0';
				x = KEYPAD_Get_Pressed_Key();
				if(x == '\0') continue;
				_delay_ms(50);
				if(x >= '0' && x <='9')
				{
					LCD_Send_Char(x);
					password[password_counter] = x;
					password_counter++;
				}
				else if(x == '*' && password_counter >0)
				{
					LCD_Delete_Last_Written();
					password[password_counter] = '\0';
					password_counter--;
				}
				else if(password_counter > 0 && x >= 'A' && x <='D')
				{
					for(int i = 0;i<password_counter;i++){
						if(password[i] == registered_password[i])
						continue;
						else password_check = 1;
					}
					break;
				}
				if(password_counter >4)
				{
					password_check = 1;break;
				}
			}
			LCD_Send_Clear_Screen();
			if(password_check == 1)
			{
				LCD_Send_String("Wrong Password");
				_delay_ms(3000);
				LCD_Send_Clear_Screen();
			}
			else if(password_check == 0)
			{
				LCD_Send_String("Correct Password");
				_delay_ms(3000);
				LCD_Send_String("Welcome 1234");
				_delay_ms(3000);
				LCD_Send_Clear_Screen();
			}
		}
	}
}

void TASK6_Calculator_LCD_Keypad()
{
	LCD_Init();
	KEYPAD_Init();
	uint8 x='\0';
	uint32 first_Num = 0;
	uint32 second_Num = 0;
	uint32 final_Num = 0;
	uint8 operand = '0';
	uint8 stage = 0;
	while(1)
	{
		x = '\0';
		x = KEYPAD_Get_Pressed_Key();
		_delay_ms(50);
		
		if(x=='\0') continue;
		
		///Reset Everything New Start
		if(stage == 2)
		{
			LCD_Send_Clear_Screen();
			stage=0;
			second_Num = 0;
			operand = '0';
			if ((x >= '0' && x <= '9') || (x == '*'))
			{
				first_Num = 0;
			}
			/// IF USER PRESSED OPRAND TO CONTINUE WITH THE PREVIOUS ANSWER
			else if ((x >= 'A' && x <= 'D'))
			{
				first_Num = final_Num;
				LCD_Send_String("ANS");
				stage = 1;
			}
		}


		/// ----------------------------------			OPERAND
		if((x >= 'A' && x <= 'D') && (first_Num > 0) && (second_Num == 0))
		{
			if(stage == 1 && operand != '0')
			{
				LCD_Delete_Last_Written();
			}
			switch(x)
			{
				case 'A': operand = '+';break;
				case 'B': operand = '-';break;
				case 'C': operand = '*';break;
				case 'D': operand = '/';break;
			}
			LCD_Send_Char(operand);
			stage = 1;
		}
		/// ----------------------------------			FIRST NUMBER
		else if((stage == 0) && (x >= '0' && x <= '9'))
		{
			first_Num = (first_Num * 10) + (x- '0');///55  >> 5*10 ==50 + 5 == 55
			if(first_Num > 0) LCD_Send_Char(x);
		}
		/// ----------------------------------			SECOND NUMBER
		else if((stage == 1) && (x >= '0' && x <= '9'))
		{
			second_Num = (second_Num * 10) + (x - '0');
			if(second_Num > 0) LCD_Send_Char(x);
		}
		/// ----------------------------------			EQUAL SIGN
		else if((stage == 1) && (x=='#') && (second_Num >0))
		{
			switch(operand)
			{
				case '+': final_Num = first_Num + second_Num;break;
				case '-': final_Num = first_Num - second_Num;break;
				case '*': final_Num = first_Num * second_Num;break;
				case '/':
				final_Num = (first_Num/second_Num);
				break;
				default:LCD_Send_String("Error Retry");break;
			}
			char snum[6];
			citoa(final_Num, snum, 10);
			LCD_Send_Char('=');
			LCD_Send_String(snum);
			stage = 2;
		}

		/// ----------------------------------			CLEAR ENTRY ALL CASES
		else if((x == '*') && (first_Num > 0))
		{
			LCD_Delete_Last_Written();
			///FIRST CASE ONLY THE FIRST NUMBER IS WRITTEN
			if((stage==0) && (second_Num == 0))
			{
				first_Num = first_Num / 10;
			}
			///SECOND CASE THE FIRST NUMBER IS WRITTEN AND THE OPERAND IS WRITTEN
			else if((stage==1) && (second_Num == 0))
			{
				operand = '0';
				stage = 0;
			}
			///THIRD CASE  THE FIRST NUMBER IS WRITTEN OPERAND WRITTEN AND SECOND NUMBER IS WRITTEN
			else if((stage==1) && (second_Num > 0))
			{
				second_Num = second_Num / 10;
			}
		}
		
	}
}

void TASK5_Keypad_Prints_LCD()
{
	LCD_Init();
	KEYPAD_Init();
	uint8 x='\0';
	while(1){
		x='\0';
		while(x=='\0'){
			do{
				x = KEYPAD_Get_Pressed_Key();
			}while(x=='\0');
			_delay_ms(50);
			LCD_Send_Char(x);
		}
	}
}

void TASK4_Traffic_Light()
{
	///TASK4: 3 led Traffic ,7seg number red 10s yellow 10s green 10s
	LED0_Init();
	LED1_Init();
	LED2_Init();
	SSEG_Void_Init();
	uint8 count = 9,color = 1;
	///LEDS  PC2 >> LED0 // PC7 >> LED1 // PD3 >> LED2
	DIO_Set_Pin_Output(PORTC,2,Low);DIO_Set_Pin_Output(PORTC,7,Low);DIO_Set_Pin_Output(PORTD,3,High);
	while(1){
		if(count==0){
			SSEG_Void_Diaplay(1,count);
			_delay_ms(1000);
			count = 9;
			switch(color){
				case 1:color++;DIO_Set_Pin_Output(PORTC,2,High);DIO_Set_Pin_Output(PORTC,7,Low);DIO_Set_Pin_Output(PORTD,3,Low);break;
				case 2:color++;DIO_Set_Pin_Output(PORTC,2,Low);DIO_Set_Pin_Output(PORTC,7,High);DIO_Set_Pin_Output(PORTD,3,Low);break;
				case 3:color++;DIO_Set_Pin_Output(PORTC,2,Low);DIO_Set_Pin_Output(PORTC,7,Low);DIO_Set_Pin_Output(PORTD,3,High);break;
				case 4:color = 1;break;
				default:break;
			}
		}
		while(count>0){
			SSEG_Void_Diaplay(1,count);
			_delay_ms(1000);
			count--;
		}
	}
}

void TASK3_Seven_Segment_Keypad_Numbers()
{
	SSEG_Void_Init();
	SSEG_Void_Diaplay(0,0);
	SSEG_Void_Diaplay(1,0);
	uint8 x ='\0';
	while(1){
		x = KEYPAD_Get_Pressed_Key();
		_delay_ms(50);
		if((x > 47) && (x < 58)){
			SSEG_Void_Diaplay(1, (x - 48));
		}
	}
}

void TASK2_Seven_Segment_3Buttons()
{
	///TASK2: 7seg counter 3 buttons, up down and reset to 0
	SSEG_Void_Init();
	Button_Init();
	uint8 button0_State =0;
	uint8 button1_State =0;
	uint8 button2_State =0;
	uint8 count=0;
	SSEG_Void_Diaplay(1,0);
	while(1)
	{
		SSEG_Void_Diaplay(1,count);
		Check_Button0_Clicked(& button0_State);
		Check_Button1_Clicked(& button1_State);
		Check_Button2_Clicked(& button2_State);
		if((button0_State == 10)){///Increase Button Pressed
			if(count<=9)count++;
			button0_State = 0;
		}
		if((button1_State == 10)){ ///Decrease Button Pressed
			if(count > 0) count--;
			button1_State = 0;
		}
		if((button2_State == 10)){///Reset Button Pressed
			if(count > 0) count = 0;
			button2_State = 0;
		}
	}
}

void TASK1_Seven_Segment_Timer()
{
	///TASK1: 7seg COUNTER from 0 to 9 count each second
	int i = 0;
	SSEG_Void_Init();
	while(1)
	{
		if(i<=9)
		{
			SSEG_Void_Diaplay(1,i);
			_delay_ms(1000);
			i++;
		}
		else if (i>9)
		{
			i=0;
		}
	}
}
