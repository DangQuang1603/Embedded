/*
* File: char.c
* Author: Le Quang
* Date: 27/08/2023
* Description: This is a function file for display,
split array and check frequency of element in array
*/

#include "char.h"

Word* splitArray (char* sampleArraySplit){

    char* countArray = sampleArraySplit;
    uint8_t sizeOfSplit = 0;
    uint8_t index = 0;
    uint8_t i = 0;

    while (*countArray != '\0'){
        if(*countArray == ' '){
            sizeOfArray++;
        }
        countArray++;
    }
    sizeOfArray++;
    
    Word *arraySplit = (Word*) malloc (sizeof(Word)*sizeOfArray);
    arraySplit[index].parray = sampleArraySplit;
    while (sampleArraySplit[i] != '\0'){
       if(sampleArraySplit[i] == ' '){
            arraySplit[index].lenght = sizeOfSplit;
            sizeOfSplit = 0;
            arraySplit[++index].parray   = sampleArraySplit+i+1;
       } else if(sampleArraySplit[i] == ','){
        sizeOfSplit = sizeOfSplit;
       }else sizeOfSplit++;
       i++;
    }
    arraySplit[index].lenght = sizeOfSplit;
    return arraySplit;
}

void Display (Word arrayDisplay){
    for (uint8_t i = 0; i < arrayDisplay.lenght; i++){
        printf ("%c", arrayDisplay.parray[i]);
    }
}

bool isEqual(Word characterOne, Word characterTwo){

    if (characterOne.lenght != characterTwo.lenght){
        return false;
    }else{
        for(uint8_t i = 0; i < characterOne.lenght; i++){
            if (characterOne.parray[i] != characterTwo.parray[i]){
                return false;
                break;
            }
            return 1;
        }
    }
}

void checkFrequency (Word *arrayFrequency){
    for (uint8_t i = 0; i < sizeOfArray; i++){
        bool check_repeat_string;
        for (uint8_t k = 0; k < i; k++){
            if (isEqual(arrayFrequency[i],arrayFrequency[k]) == 1){
                check_repeat_string = 1;
                break;
            }
        }

        if (check_repeat_string == 1){
            check_repeat_string = 0;
            continue;
        }

        uint8_t countFrequency = 1;
        for (uint8_t j = i+1; j < sizeOfArray; j++){
            bool equal = isEqual(arrayFrequency[i],arrayFrequency[j]);
            if (equal == 1){
                countFrequency++;
            }
        }
        printf("Phan tu ");
        Display (arrayFrequency[i]);
        printf(" xuat hien %d lan\n", countFrequency);
        
    }
}