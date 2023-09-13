#ifndef _SOFTALPHABET_H
#define _SOFTALPHABET_H

#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct 
{
    uint8_t lenght;
    char* parr;
} MEMBER;

uint8_t strSize(char string[]);
void print (MEMBER str[], uint8_t size);
MEMBER* splitString(char string[]);
bool compare (const char arrayOne[], const char arrayTwo[]);
void softAlphabet (MEMBER str[], uint8_t size);
#endif