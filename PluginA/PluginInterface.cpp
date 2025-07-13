#include "pch.h"
#include "../PluginInterface.h"
#include <algorithm>


extern "C"
const char* getName() 
{ 
    return "PluginA"; 
}


extern "C"
bool getLinescan(unsigned char*& pLine, unsigned long& ulLength)
{
    ulLength = 10;
    pLine = new unsigned char[ulLength];
    memset(pLine, 0, static_cast<size_t>(ulLength));

    // Test: Dummy values
    static int uCounter = 0;
    pLine[uCounter++] = 1;

    return true;
}


extern "C"
void freeLinescan(unsigned char* pLine)
{
    delete[] pLine;
}
