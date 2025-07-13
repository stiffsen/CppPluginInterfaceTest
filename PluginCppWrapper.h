#pragma once

#include "PluginInterface.h"
#include <memory>
#include <filesystem>
#include <string>
#include <span>
#include <functional>


class PluginCppWrapper
{
private:
    PluginCppWrapper(const std::filesystem::path& DllPath);
    std::shared_ptr<PluginInterface> m_pPluginInterface;
    
    using LinescanDeleter = std::function<void(std::span<unsigned char>*)>;
    LinescanDeleter m_LinescanDeleter;

public:
    ~PluginCppWrapper() = default;

    static std::unique_ptr<PluginCppWrapper> create(const std::filesystem::path& DllPath);

    std::string_view getName() const;
    
    using LinescanPtr = std::unique_ptr<std::span<unsigned char>, LinescanDeleter>;
    LinescanPtr getLinescan() const;
};

