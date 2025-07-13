// CppPluginInterfaceTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "PluginLoader.h"

int main()
{
    PluginLoader Plugin("./Plugins/PluginA.dll");
    std::cout << Plugin.getName() << '\n';

    return 0;
}

