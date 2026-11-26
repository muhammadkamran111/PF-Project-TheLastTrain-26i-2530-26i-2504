#include "util.h"
#include <iostream>
using namespace std;

//If a function value is less than minimum value then this function will set that to minimum: Same for maximum value
int clampInt(int val,int minVal,int maxVal)
{
    if (val < minVal) return minVal;
    if (val > maxVal) return maxVal;
    return val;
}

//This function will remove the whitespace from the start and end of the string
void trimWhitespace(char* str)
{
    if (str == nullptr) return;
    int len = 0;
    int start = 0;
    int count = 0;
    while (str[len] != '\0') 
    {
        len++;
    }

    while (start < len && (str[start] == ' ' || str[start] == '\t'  || str[start] == '\r' || str[start] == '\n'  ))
    {
        start++;
    }

    int end = len - 1;

    while (end >= start && (str[end] == ' ' || str[end] == '\t'  || str[end] == '\r' || str[end] == '\n'  ))
    {
        --end;
    }
    
    for (int a = start; a <= end; a++)
    {
        str[count] = str[a];
        count++;
    }

    str[count] = '\0';  
}

bool stringEquals(const char* a, const char* b)
{   int c = 0;
    if (a == nullptr || b == nullptr) return false;
    while (a[c] != '\0' && b[c] != '\0') 
    {
        if (a[c] != b[c]) return false;
        c++;
    }
    return (a[c] == '\0' && b[c] == '\0' );
}   

void printHeader(const char* title) {
    cout << "\n=============================================\n";
    cout << "  " << title << "\n";
    cout << "=============================================\n";
}


void clearScreen() {
    cout << "\n";
}