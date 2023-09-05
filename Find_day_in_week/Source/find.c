/*
* File: find.c
* Author: Le Dang Quang
* Date: 30/08/2023
* Description: This file include details function for formating string in file main.c
*/
#include<stdio.h>
#include"find.h"

bool checkDate (Date d){
    if (d.month < 0 || d.month > 12){
        return 0;
    }else if (d.day > 0 || d.day <= dom[d.month - 1]){
        return 1;
    }
}

uint16_t countLeapYear(Date dIn){
    uint16_t year = dIn.year;
    if(dIn.month <= 2) {
        year--;
    }
    return year/4 - year/100 + year/400;
}

uint32_t CountNumberOfDay (Date d1, Date d2){
    if (!checkDate(d1)){
        printf("Wrong date 1!\n");
        exit(0);
    }else if(!checkDate(d2)){
        printf("Wrong date 2!\n");
        exit(0);
    }
    
    uint32_t numOfDay1 = d1.year * 365 + d1.day;
    numOfDay1 += countLeapYear(d1);
    for (uint8_t i = 1; i <= d1.month; i++){
        numOfDay1 += dom[i];
    }

    uint32_t numOfDay2 = d2.year * 365 + d2.day;
    numOfDay2 += countLeapYear(d2);
    for (uint8_t i = 1; i <= d2.month; i++){
        numOfDay2 += dom[i];
    }

    return numOfDay2 - numOfDay1;
}

void getNumberOfDay(Date d1, Date d2){
    uint32_t countDay = CountNumberOfDay(d1, d2);
    uint8_t checkDay = countDay % 7;
    const char *dayOfWeek[] = {"Sunday","Monday","Tuesday","WenesDay","Thursday","Friday","Satuday"};
    printf ("%d/%d/%d is %s\n",d2.day, d2.month, d2.year, dayOfWeek[checkDay]);
}