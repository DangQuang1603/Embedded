#include"softalphabet.h"

uint8_t strSize(char string[]){
    uint8_t countChar = 1;
    while(*string != '\0'){
        if (*string == ' '){
            countChar++;
        }
        string++;
    }
    return countChar;
}

void print (MEMBER str[], uint8_t size){
    for (uint8_t i = 0; i < size; i++){
        for (uint8_t j  = 0; j < str[i].lenght; j++){
            printf ("%c", str[i].parr[j]);
        }
        printf(" ");
    }

    printf("\n");
}

MEMBER* splitString(char string[]){
    uint8_t numOfChar = strSize(string);
    MEMBER* pstring = (MEMBER*)malloc(sizeof(MEMBER)*numOfChar);

    uint8_t index = 0;
    uint8_t count = 0;

    pstring[index].parr = string;
    
    while (*string != '\0')
    {
        if (*string == ' '){
            pstring[index].lenght = count;
            count = 0;
            pstring[++index].parr = ++string;
        }else{
            string++;
            count++;
        }
    }
    pstring[index].lenght = count;
    return pstring; 
}

bool compare (const char arrayOne[], const char arrayTwo[]){
    uint8_t i = 0;
    while (arrayOne[i] != ' ' && arrayTwo[i] != ' ')
    {
        if (arrayOne[i] > arrayTwo[i]){
            return 1;
        }else if(arrayOne[i] < arrayTwo[i]){
            return 0;
        }
        i++;
    }
    return 0;
}

void softAlphabet (MEMBER str[], uint8_t size){
    for(uint8_t i = 0; i < size; i++){
        MEMBER temp = str[i];
        uint8_t index = i;
        for(uint8_t j = i+1; j < size; j++){
            if (compare(temp.parr,str[j].parr)){
                temp = str[j];
                index = j;
            }
        }
        str[index] = str[i];
        str[i] = temp;
    }
}   