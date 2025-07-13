// CppPluginInterfaceTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "PluginCppWrapper.h"

int main()
{
    {
        auto pPlugin = PluginCppWrapper::create("./Plugins/PluginA.dll");
        if (pPlugin == nullptr)
            return -1;
    }

    return 0;
}

