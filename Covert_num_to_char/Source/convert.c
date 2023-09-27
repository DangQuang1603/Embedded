#include"convert.h"

void readSplitNumber(char number[], char num, uint8_t i, uint8_t unit){
    switch (num)
    {
    case KHONG:
        if (unit == TRAM) printf("Khong ");
        else if (unit == CHUC && number[i+1] != '0') printf("Le ");
        break;
    case MOT:
        if (unit == CHUC) printf("Muoif ");
        else if (unit == DONVI && number[i-1] != '0' && number[i-1] != '1' && i!= 0 ) printf("Mots ");
        else printf("Mot ");
        break;
    case HAI:
        printf("Hai ");
        break;
    case BA:
        printf("Ba ");
        break;
    case BON:
        if (unit == DONVI && number[i-1] != '0' && number[i-1] != '1') printf ("Tu ");
        else printf("Bon ");
        break;
    case NAM:
        if (unit == DONVI && number[i-1] != '0' && number[i-1] != '1') printf ("Lam ");
        else printf("Nam ");
        break;
    case SAU:
        printf("Sau ");
        break;
    case BAY:
        printf("Bay ");
        break;
    case TAM:
        printf("Tam ");
        break;
    case CHIN:
        printf("Chin ");
        break;
    default:
        break;
    }
}

uint16_t strsize (char number[]){
    uint8_t index = 0;
    while (number[index] != '\0'){
        index++;
    }
    return index;
}

void Convert (char number[]){
    uint8_t strlenght = strsize(number);
    uint8_t unit = 0;
    for (uint8_t i = 0; i < strlenght; i++){
        unit = (strlenght - i) % 3;
        readSplitNumber(number, number[i], i, unit);
        uint8_t loca = (strlenght - (i + 1))/3;
        uint8_t endFlag = 0;
            uint8_t j = i+1;
        switch (unit)
        {
        case CHUC:
            if(number[i] != '0' && number[i] != '1') printf("Muoi ");
            break;
        case TRAM:
            printf("Tram ");
            break;
        case DONVI:
            
            switch (loca)
            {
            case TY:
                printf("Ty ");
                break;
            case TRIEU:
                printf("Trieu ");
                break;
            case NGHIN:
                printf("Nghin ");
                break;
            default:
                break;
            }

            while (number[j] != '\0')
            {
                if(number[j] != '0'){
                    endFlag++;
                }
                j++;
            }
            if(endFlag == 0){
                printf("Dong ");
                return;
            }
            break;
        default:
            break;
        }
    }
}

