/*
* File: format.c
* Author: Le Dang Quang
* Date: 30/08/2023
* Description: This file include details function for formating string in file main.c
*/
#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<stdlib.h>
#include"Format.h"



/*
Function: lenghtOfString
Description: this function mersure and return the lenght of string input
Input: A address of string
Output: lenght of string input
*/
uint8_t lenghtOfString (char* sampleString){
    uint8_t lenght = 0;
    while (*sampleString != '\0'){
        lenght++;
        sampleString++;
    }
    return lenght;
}

/*
Function: displayString
Description: print all of element of string input
Input: A address of string
Output: none
*/
void displayString (char* sampleString){
    for (uint8_t i = 0; i < lenghtOfString(sampleString); i++){
        printf ("%c", sampleString[i]);
    }
    printf("\n");
}


/*
Function: copStr
Description: Coppy a substring into mainstring
Input: A address of mainstring and sbustring
Output: none
*/
void copStr (char* string, char* copString){
    uint8_t checkLenght = 0;
    while (checkLenght <= (lenghtOfString(copString)+1)){
        *string = *copString;
        string++;
        copString++;
        checkLenght++;
    }
    *string = *copString;
}

/*
Function: findSubString
Description: find substring in mainstring, if exist return the start adress of substring in mainstring
Input: A address of mainstring and sbustring
Output: the start adress of substring in mainstring
*/
char* findSubString(char* sampleString, char* sampleSentence){
    uint8_t checkCount = 0;
    uint8_t find_flag = 0;
    char* location = sampleString;
    while (*sampleString != '\0'){
        if(*sampleString == sampleSentence[checkCount] || *sampleString == (sampleSentence[checkCount] - 32)){
            checkCount++;
            if(checkCount == lenghtOfString(sampleSentence)){
                find_flag = 1;
                break;
            }
        }else{
            checkCount = 0;
            location = sampleString+1;
        }
        sampleString++;
    }

    if(find_flag){
        return location;
    }else{
        return 0;
    }
}

/*
Function: captureString
Description: capture all character after "." character
Input: A address of string
Output: none
*/
void captureString (char* string){
    uint8_t captureFlag = 0;
    while (*string != '\0'){
        if (!captureFlag){
            if (*string == '.'){
            captureFlag = 1;
        }
        }else{
            if (*string != ' '){
                *string -= 32;
            }
        }
        string++;
    }
    
}


/*
Function: findSubString
Description: find substring in mainstring, if exist print Yes and return the start position of substring in mainstring
Input: A address of mainstring and sbustring
Output: none
*/
void findSentence (char* sampleString, char* sampleSentence){
    uint8_t checkCount = 0;
    uint8_t find_flag = 0;
    for (uint8_t i = 0; i < lenghtOfString(sampleString); i++){
        if(sampleString[i] == sampleSentence[checkCount]){
            checkCount++;
            if(checkCount == lenghtOfString(sampleSentence)){
                find_flag = 1;
                break;
            }
        }else{
            checkCount = 0;
        }
    }
    if(find_flag){
        printf("Find sample sentence in string!\n");
        printf ("Location of sentence: %d\n", checkCount);
    }else{
        printf("Can't find sample sentence in string!\n");
    }

}


/*
Function: replaceSentence
Description: find substring in mainstring, if exist replace this substring by new string
Input: A address of mainstring and sbustring and replacestring
Output: none
*/
void replaceSentence (char* string, char* sampleSentence, char* sentenceRepalce){
    uint8_t count = 0, i = 0, j = 0;
    uint8_t lenstring = lenghtOfString(string);
    uint8_t lensample = lenghtOfString(sampleSentence);
    uint8_t lenreplace = lenghtOfString(sentenceRepalce);
    char* result = (char*) malloc(sizeof(char)*(lenstring + (count*(lenreplace - lensample)) + 1));

    for (i =  0; string[i] != '\0';){
        if (findSubString(&string[i], sampleSentence) == &string[i]){
            copStr(&result[j],sentenceRepalce);
            i += lensample;
            j += lenreplace;
        }else{
            result[j++] = string[i++];

        }
    }
    result[j] = '\0';
    for(i = 0; result[i] != '\0'; i++){
        string[i] = result[i];
    }
    string[i] = '\0';
}
