/****************************************/
/*          Author: Kareem Atef		    */
/*          Date: 24-11-2023		    */
/*          Version: 1.0				*/
/*          Module : Helper             */
/****************************************/
#include "../MCAL/DIO/STD_Types.h"
void reverse(char str[], int length)
{
	int start = 0;
	int end = length - 1;
	while (start < end) {
		char temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		end--;
		start++;
	}
}
char* citoa(int num, char* str, int base)
{
	int i = 0;
	uint8 isNegative = 0;
	if (num == 0) {
		str[i++] = '0';
		str[i] = '\0';
		return str;
	}
	if (num < 0 && base == 10) {
		isNegative = 1;
		num = -num;
	}
	while (num != 0) {
		int rem = num % base;
		str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		num = num / base;
	}
	if (isNegative)
	str[i++] = '-';
	str[i] = '\0'; // Append string terminator
	// Reverse the string
	reverse(str, i);
	return str;
}
