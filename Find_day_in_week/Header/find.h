/*
* File: find.h
* Author: Le Dang Quang
* Date: 30/08/2023
* Description: This file declare variable, array and function name
*/
#ifndef __FIND_H
#define __FIND_H

#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct date
{
    uint8_t day;
    uint8_t month;
    uint16_t year;
} Date;

const int dom[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
bool checkDate (Date d);
uint16_t countLeapYear(Date dIn);
uint32_t CountNumberOfDay (Date d1, Date d2);
void getNumberOfDay(Date d1, Date d2);
#endif

