#include "../include/string.h"
#include "../include/screen.h"



int32_t atoi(char* str)
{
	int32_t result = 0;
	int32_t puiss = 1;

	while (('-' == (*str)) || ((*str) == '+'))
	{
		if (*str == '-')
		puiss = puiss * -1;
		str++;
	}
	while ((*str >= '0') && (*str <= '9'))
	{
		result = (result * 10) + ((*str) - '0');
		str++;
	}
	return (result * puiss);
}
