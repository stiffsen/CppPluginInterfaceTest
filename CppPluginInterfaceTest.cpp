// CppPluginInterfaceTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "PluginCppWrapper.h"

int main()
{
    {
        PluginCppWrapper::LinescanPtr pLinescan;
        {
            auto pPlugin = PluginCppWrapper::create("./Plugins/PluginA.dll");
            if (pPlugin == nullptr)
                return -1;

            pLinescan = pPlugin->getLinescan();

            // Test code
            if ((*pLinescan)[0] != 1)
            {
                std::cerr << "Unexpected linescan result...\n";
                return -1;
            }
            //

            pLinescan = pPlugin->getLinescan();

            // Test code
            if ((*pLinescan)[1] != 1)
            {
                std::cerr << "Unexpected linescan result...\n";
                return -1;
            }
            //
        }
    }

    return 0;
}

