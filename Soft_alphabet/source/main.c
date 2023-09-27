#include"softalphabet.h"

int main(int argc, char const *argv[])
{
    char string[] ="anh hoang nga my trung anh hoang quang ngoc";
    MEMBER* pstring = splitString(string);
    print (pstring, strSize(string));
    softAlphabet(pstring, strSize(string));
    print (pstring, strSize(string));
    return 0;
}