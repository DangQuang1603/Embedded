#include<stdio.h>
#include "find.h"

int main(int argc, char const *argv[])
{
    Date dt1 = { 1, 2, 2000 };
    Date dt2 = { 3, 3, 2003 };
    getNumberOfDay(dt1, dt2);
    return 0;
}