#ifndef SCREEN_H
#define SCREEN_H
#include <stdbool.h> //  
#include <stddef.h>  // Variable -> ptrdiff_t, size_t, wchar_t | Macros NULL, offsetof
#include <stdint.h> 


void initTerminal();
void printf(const char* key, const char* string);
void displayInteger(const uint32_t number);
#endif
