#include<stdio.h>
#include "char.h"

int main(int argc, char const *argv[])
{
    Word* psplitArray = splitArray(sampleArray);
    checkFrequency(psplitArray);
    return 0;
}