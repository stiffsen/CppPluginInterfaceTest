#include "pch.h"
#include "ExampleClassPlugin.h"



ExampleClassPlugin::ExampleClassPlugin(const char* sName)
    : m_sName(sName)
{
}


const std::string& ExampleClassPlugin::getName() const
{
    return m_sName;
}