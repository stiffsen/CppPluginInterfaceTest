#pragma once

#include "PluginInterface.h"
#include <memory>
#include <filesystem>
#include <string>


class PluginCppWrapper
{
private:
    PluginCppWrapper(const std::filesystem::path& DllPath);
    std::shared_ptr<PluginInterface> m_pPluginInterface;
public:
    ~PluginCppWrapper();

    static std::unique_ptr<PluginCppWrapper> create(const std::filesystem::path& DllPath);

    std::string_view getName() const;
};

