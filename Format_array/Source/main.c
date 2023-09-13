#include<stdio.h>
#include"format.h"

int main(int argc, char const *argv[])
{
    char sampleString[] = "remember that people like you keep the world turning, so you should keep moving";
    // captureString(sampleString);
    // displayString(sampleString);
    // findSentence(sampleString, "help");
    // replaceSentence(sampleString, "hi", "hello");
    insert(sampleString, "hi", "hello");
    displayString(sampleString);
    insert(sampleString, "you", "me");
    displayString(sampleString);
    
    return 0;
}