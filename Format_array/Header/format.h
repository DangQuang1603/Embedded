#ifndef __FORMAT_H
#define __FORMAT_H

#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<stdlib.h>

uint8_t lenghtOfString (char* sampleString);
void displayString (char* sampleString);
void copStr (char* string, char* copString);
char* findSubString(char* sampleString, char* sampleSentence);
uint8_t findSentence (char* sampleString, char* sampleSentence);
void replaceSentence (char* string, char* sampleSentence, char* sentenceRepalce);
void captureString (char* string);
void insert (char* string, char* sampleSentence, char* sentenceRepalce);
#endif