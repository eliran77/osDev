#include "../include/screen.h"
#include "../include/string.h"
/*
	* The size of each address in RAM is 8bits (or 1byte).
	* After booing the kernel by grub the system start in text mode.
	* In text mode the system can access to area of memory that control a screen.
	* The screen split to 80 wide and 25 high that each square represent char.
	* Each character represent by 16bits (or 2byte).
	* So we need 2byte in the memory(not ram) to represent character. 
	
	To sum up in the screen the max chacacter that we can represent is 2000 characters! (80*25=2000) 
*/

#define VIDEO_ADDRESS 0xB8000
#define HIGH 25   
#define WIDE 80   
#define DEFAULT_CHAR ' '
#define DEFAULT_COLOR COLOR_CYAN // 
#define MAX_INDEX HIGH * WIDE * 2// Can desplay only 2000 characters -> (2000 * 2(byte) = 4000)

uint16_t index_video = 0;
unsigned char *video = (unsigned char*)VIDEO_ADDRESS; // video = 0xB8000

enum color_number {
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_PURPLE = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15,
};

void putc(const char character)
{
	if (character == '\n' && !(index_video % 159 == 0))
	{
		index_video = ((index_video / 160) + 1) * 160;
	}
	else 
	{
		video[index_video++] = character;
		video[index_video++] = COLOR_GREEN;
	}
	if (index_video == MAX_INDEX)
	{
		index_video = 0;	
	}
}

void puts(const char* string)
{
	int i = 0;
	while(string[i])
    {
		putc(string[i]);
		i++;
 	}
}
/*
	This function ... with " "
*/
void initTerminal()
{
	int16_t index = 0;
	for (index = 0; index < MAX_INDEX; index++) // [0 ... 3999]
	{
		if(!(index % 2 == 0))
		{
			video[index-1] = DEFAULT_CHAR;
			video[index] = DEFAULT_COLOR;
		}
	}
}

void printf(const char* key, const char* string)
{
	if (key ==  "%s")
	{
		puts(string);
	}	
	else if (key == "%c")
	{
		putc(string[0]);
	}
	/*
	else if (key == "%d")
	{
		displayInteger(atoi(string));
	}
	*/
}



void displayInteger(const uint32_t number)
{
	if (number != 0)
	{
		displayInteger(number / 10);
		putc(48 + number % 10);
	} 
}