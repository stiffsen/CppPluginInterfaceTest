#include "PluginCppWrapper.h"
#include <iostream>

PluginCppWrapper::PluginCppWrapper(const char* sDllPath)
    : m_pPluginInterface(std::make_shared<PluginInterface>(sDllPath))
{
}

PluginCppWrapper::~PluginCppWrapper()
{
    std::cout << "Unloading plugin: " << m_pPluginInterface->getName() << '\n';
}

std::unique_ptr<PluginCppWrapper> PluginCppWrapper::create(const char* sDllPath)
{
    try
    {
        auto pWrapper = std::unique_ptr<PluginCppWrapper>(new PluginCppWrapper(sDllPath));
        std::cout << "Successfully loaded " << sDllPath << ".\n";
        return pWrapper;
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Failed to load " << sDllPath << ". Reason: " << e.what() << '\n';
        return std::unique_ptr<PluginCppWrapper>();
    }    
}

std::string_view PluginCppWrapper::getName() const
{
    return m_pPluginInterface->getName();
}