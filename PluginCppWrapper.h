#pragma once

#include "PluginInterface.h"
#include <memory>
#include <filesystem>
#include <string>

class PluginCppWrapper
{
private:
    PluginCppWrapper(const char* sDllPath);
    std::shared_ptr<PluginInterface> m_pPluginInterface;
public:
    ~PluginCppWrapper();

    static std::unique_ptr<PluginCppWrapper> create(const char* sDllPath);

    std::string_view getName() const;
};

