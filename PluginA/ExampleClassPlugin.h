#pragma once


#pragma once
#include <string>

class ExampleClassPlugin
{
    std::string m_sName;

public:
    ExampleClassPlugin(const char* sName);

    const std::string& getName() const;
};

