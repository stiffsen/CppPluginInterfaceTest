#include <iostream>
#include "PluginCppWrapper.h"

// Testbed for Plugin Interface

int main()
{
    {
        // Some data declared outside of scope of pPlugin to test whether plugin is unloaded when these go out of scope
        PluginCppWrapper::LinescanPtr     pLinescan;
        PluginCppWrapper::ExampleClassPtr pExampleClass;

        {
            // Load the plugin -> Check std::cout for various init/deinit messages etc.
            auto pPlugin = PluginCppWrapper::create("./Plugins/PluginA.dll");
            if (pPlugin == nullptr)
                return -1;

            pLinescan = pPlugin->getLinescan();
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


            pExampleClass = pPlugin->createExampleClass("Foo");
            std::cout << "Hey: " << pExampleClass->getName() << '\n';
            pExampleClass = pPlugin->createExampleClass("Bar");
            std::cout << "Hey: " << pExampleClass->getName() << '\n';

            // NOTE: We should not see logging for unloading PluginA here, because pLinescan and pExampleClass still hold a reference to the plugin!
        }
    }

    return 0;
}

