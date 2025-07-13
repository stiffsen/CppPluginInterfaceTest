#include "pch.h"
#include "../PluginInterface.h"
#include <algorithm>
#include <iostream>

// Plugin-side implementation of PluginInterface


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

    std::cout << "Plugin: Allocated linescan\n";

    return true;
}

extern "C"
void freeLinescan(unsigned char* pLine)
{
    delete[] pLine;
    std::cout << "Plugin: Freed linescan\n";
}




#include <vector>
#include <mutex>
#include <memory>
#include "ExampleClassPlugin.h"

std::mutex mtxExampleClass;
std::vector<std::unique_ptr<ExampleClassPlugin>> vecExampleClass;

extern "C"
CLASSHANDLE ExampleClass_create(const char* sName)
{
    CLASSHANDLE ret = -1;
    {
        std::scoped_lock lock{ mtxExampleClass };
        vecExampleClass.push_back(std::make_unique<ExampleClassPlugin>(sName));
        ret = static_cast<long>(vecExampleClass.size() - 1);
    }
    std::cout << "Plugin: Istanciated ExampleClass\n";
    return ret;
}

extern "C"
bool ExampleClass_free(CLASSHANDLE Index)
{
    if (Index < 0)
        return false;

    std::scoped_lock lock{ mtxExampleClass };

    const size_t uIndex = static_cast<size_t>(Index);
    if (uIndex >= vecExampleClass.size())
        return false;

    vecExampleClass[uIndex].reset();

    std::cout << "Plugin: Freed ExampleClass\n";
    return true;
}

extern "C"
bool ExampleClass_getName(CLASSHANDLE Index, const char*& sName)
{
    if (Index < 0)
        return false;
    const size_t uIndex = static_cast<size_t>(Index);

    std::scoped_lock lock{ mtxExampleClass };
    if (uIndex >= vecExampleClass.size())
        return false;
    const auto& pInstance = vecExampleClass[uIndex];
    if (pInstance == nullptr)
        return false;

    sName = pInstance->getName().data();
    return true;
}