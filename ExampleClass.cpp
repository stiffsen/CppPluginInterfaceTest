#include "ExampleClass.h"
#include <stdexcept>
#include <iostream>


ExampleClass::ExampleClass(std::shared_ptr<PluginInterface> pPluginInterface, std::string_view sName)
    : m_pPluginInterface{ pPluginInterface }
    , m_ClassHandle{ pPluginInterface->ExampleClass_create(sName.data()) }
{
    if (m_ClassHandle < 0)
        throw std::runtime_error("Failed to create class.");

    std::cout << "Created ExampleClass with name: " << sName << '\n';
}


ExampleClass::~ExampleClass()
{
    std::cout << "Deleted ExampleClass with name: " << getName() << '\n';
    m_pPluginInterface->ExampleClass_free(m_ClassHandle);
}


std::string ExampleClass::getName() const
{
    const char* sName{ nullptr };
    m_pPluginInterface->ExampleClass_getName(m_ClassHandle, sName);
    return sName; // may be null if previous call fails
}