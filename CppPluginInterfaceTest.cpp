#include <iostream>
#include "PluginInterface.h"

// Testbed for Plugin Interface

int main()
{

    {
        // Load the plugin -> Check std::cout for various init/deinit messages etc.
        auto pPlugin = createPluginInterface("./Plugins/PluginA.dll");
        if (pPlugin == nullptr)
            return -1;

        auto pLinescan = pPlugin->getLinescan();
        if (pLinescan == nullptr)
            return -1;

        auto PrintLinescan = [](const decltype(pLinescan)& pLinescan)
            {
                std::cout << "Linescan:\t";
                for (int val : *pLinescan)
                    std::cout << val << '\t';
                std::cout << '\n';
            };            
        PrintLinescan(pLinescan);            

        pLinescan = pPlugin->getLinescan();
        if (pLinescan == nullptr)
            return -1;
        PrintLinescan(pLinescan);

        auto pExampleClass = pPlugin->createExampleClass("Foo");
        std::cout << "Hey: " << pExampleClass->getName() << '\n';
        pExampleClass = pPlugin->createExampleClass("Bar");
        std::cout << "Hey: " << pExampleClass->getName() << '\n';
    }

    return 0;
}

