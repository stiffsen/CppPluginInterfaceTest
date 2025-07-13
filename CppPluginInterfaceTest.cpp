// CppPluginInterfaceTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "PluginInterface.h"

int main()
{
    PluginInterface Plugin("./Plugins/PluginA.dll");
    std::cout << Plugin.getName() << '\n';

    return 0;
}

