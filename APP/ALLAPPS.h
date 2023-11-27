/****************************************/
/*          Author: Kareem Atef         */
/*          Date: 10-11-2023            */
/*          Version: 1.0                */
/*          Module: App                 */
/****************************************/
#include "../MCAL/DIO/STD_Types.h"


#ifndef ALLAPPS_H_
#define ALLAPPS_H_

uint8 TASK22_RECEIVE_WITH_DIO_MICRO_RECEIVER();
void TASK21_SEND_WITH_DIO_MICRO_SENDER(uint8 character);
void TASK20_MOTOR_FASTPWM();
/***************************************/
void TASK19_TIMER_FASTPWM_LED();
void TASK18_TIMER_CTC_ADC_POTENTIOMETER();
void TASK17_TIMER_CTC_Freq();
void TASK17_ISR();
void TASK16_TIMER_SQRWAVE_NORMAL();
void TASK16_ISR();
void TASK15_TIMER_LED();
void TASK15_ISR();
/***************************************/
void TASK14_KEYPAD_LCD_INTERRUPT();
void TASK14_ISR();
void TASK13_LED_BUTTON_INTERRUPT();
void TASK13_ISR();
/***************************************/
void TASK10_ADC_Manual_Interrupt();//OK
void TASK10_ISR_ADC();//OK
void TASK11_ADC_Timer_No_Interrupt();//OK

void TASK12_ADC_Timer_With_Interrupt();//???
void TASK12_ISR_ADC_Timer();//???
/***************************************/
void TASK9_ADC_Potentiometer_Temperature_LCD();
void TASK8_ADC_Potentiometer();
/***************************************/


#endif /* ALLAPPS_H_ */