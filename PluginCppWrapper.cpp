#include "PluginCppWrapper.h"
#include <iostream>

PluginCppWrapper::PluginCppWrapper(const std::filesystem::path& DllPath)
    : m_pPluginInterface(std::make_shared<PluginInterface>(DllPath.string().c_str()))
{
}

PluginCppWrapper::~PluginCppWrapper()
{
    std::cout << "Unloading plugin: " << m_pPluginInterface->getName() << '\n';
}

std::unique_ptr<PluginCppWrapper> PluginCppWrapper::create(const std::filesystem::path& DllPath)
{
    try
    {
        auto pWrapper = std::unique_ptr<PluginCppWrapper>(new PluginCppWrapper(DllPath));
        std::cout << "Successfully loaded " << DllPath.filename().string() << ". Plugin name: " << pWrapper->getName() << ".\n";
        return pWrapper;
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Failed to load " << DllPath.filename().string() << ". Reason: " << e.what() << '\n';
        return std::unique_ptr<PluginCppWrapper>();
    }    
}

std::string_view PluginCppWrapper::getName() const
{
    return m_pPluginInterface->getName();
}