#ifndef __CHAR_H
#define __CHAR_H

#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>

char sampleArray[] = "Quang hai hai nam, ba Quang muoi hai mot, hai hai bon Hieu Nhan Quang";
uint8_t sizeOfArray = 0;

typedef struct {
    uint8_t lenght;
    bool status;
    uint8_t frequency;
    char* parray;
} Word;

Word* splitArray (char* sampleArraySplit);
void Display (Word arrayDisplay);
bool isEqual(Word characterOne, Word characterTwo);
void checkFrequency (Word *arrayFrequency);

#endif