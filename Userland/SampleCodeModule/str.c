#include <stdint.h>

uint8_t isWhitespace(char c) {
	return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' ;
}

uint64_t strlen(const char * s) {
    int i;
    for (i = 0; s[i] != 0; i++);
    return i;
}

uint8_t isNumber(char c) {
	return c >= '0' && c <= '9';
}

int8_t strcmp(const char* str1, const char* str2) {
    while(*str1 != 0 && *str2 != 0 && *str1 == *str2) {
        str1++; str2++;
    }

    return *str1 - *str2;
}

// copies string until from ends or until the first whitespace
uint64_t strncpy(char * to, const char * from, int n) {
    int i;
    for (i = 0; from[i] != 0 && !isWhitespace(from[i]) && i < n; i++)
    {
        to[i] = from[i];
    }
	to[i++] = 0;
    return i;
}

uint64_t strcpy(char * to, const char * from) {
	int i;
    for (i = 0; from[i] != 0; i++)
    {
        to[i] = from[i];
    }
    return i;
}

uint8_t toUpper(uint8_t c) {
	return c >= 'a' && c <= 'z'? c - 'a' + 'A' : c;
}

uint32_t uintToBase(uint32_t value, char * buffer, uint32_t base)
{
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}

// devuelve la cantidad de caracteres leidos
int64_t strToIntBase(const char * s, int len, uint32_t base, int * result, int unsign) {
	int sign = 1;
	uint8_t aux = 0;
	uint32_t num = 0;
	int i;
	if (!unsign && s[0] == '-') {
        s++;
    	sign = -1;
    }
    for (i = 0; s[i] != 0 && ((len < 0)? 1 : i < len) ; i++)
    {	
        if (s[i] <= '9') {
			aux = s[i] - '0';
		}
		else 
			aux = toUpper(s[i]) + 10 - 'A';

		if (aux >= base)
		{
			break;
		}

		num *= base;
		num += aux;
	}   
	num *= sign;
	if (i != 0)
	{
		*result = num;
	}
	return sign == 1? i : i + 1;
}

uint32_t floatToStr(double value, char * buffer, uint32_t decimals) {
	uint32_t digits = 0;

	if (value < 0)
	{
		buffer[digits++] = '-';
		value *= -1;
	}

	int intpart = value;

	digits += uintToBase(intpart, &buffer[digits], 10);

	if (decimals == 0)
		return digits;
	
	buffer[digits++] = '.';
	value -= intpart;
	
	int number = 0;
	while (decimals-- != 0) {
		value*=10;
		if ((int) value != 0 || decimals == 0)
			number = 1;
		
		if (!number && (int) value == 0)
		{
			buffer[digits++] = '0';
		}	
	}
	
	int decpart = value;

	digits =+ uintToBase(decpart,&buffer[digits],10);
	return digits;
}

int64_t strToFloat(const char * s, int len, double * result) {	
	int sign = 1;
	if (s[0] == '-') {
        s++;
    	sign = -1;
    }

	int i;
	int zero = 0;
	if (s[0] == '.')
	{
		s++;
		i = 0;
		zero = 1;
	}
	else {

		int intpart;
		i = strToIntBase(s,len,10,&intpart,1);

		if (i == 0 ) 
			return i;

		intpart *= sign;
	
		*result = (double) intpart;

		if (i == len || s[i] != '.')
			return i;
		i++;
	}

	int decpart;
	int j = i;
	j += strToIntBase(&s[i],len - i,10, &decpart,1);

	if (j == i)
		return i;

	double number = decpart;

	if (zero)
		*result = 0;

	while (i++ != j)
		number/=10;

	*result += number*sign;

	if (zero) j++;

	return sign == 1? j : j + 1;
}
