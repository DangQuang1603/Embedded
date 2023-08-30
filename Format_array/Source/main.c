#include<stdio.h>
#include"Format.h"
#include"Format.c"

char sampleString[] = "to help people around the world learn about anything. today we learn about that";

int main(int argc, char const *argv[])
{
    captureString(sampleString);
    displayString(sampleString);
    findSentence(sampleString, "help");
    replaceSentence(sampleString, "anything", "abcd");
    displayString(sampleString);
    return 0;
}