#ifndef _CONVERT_H
#define _CONVERT_H

#include<stdio.h>
#include<stdint.h>

enum money {
    TRAM    = 0,
    DONVI   = 1,
    NGHIN   = 1,
    CHUC    = 2,
    TRIEU   = 2,
    TY      = 3
};

enum element {
    KHONG   = '0',
    MOT     = '1',
    HAI     = '2',
    BA      = '3',
    BON     = '4',
    NAM     = '5',
    SAU     = '6',
    BAY     = '7',
    TAM     = '8',
    CHIN    = '9'
};

void readSplitNumber(char number[], char num, uint8_t i, uint8_t unit);
uint16_t strsize (char number[]);
void Convert (char number[]);

#endif