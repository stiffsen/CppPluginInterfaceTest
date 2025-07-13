#pragma once

#include "PluginInterface.h"
#include <memory>
#include <filesystem>
#include <string>
#include <span>
#include <functional>



// A c++ wrapper for user-side PluginInterface (wraps c-style functions into fully-fledged classes and modern c++ implementations)
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


    // CppWrapper variant of simple plugin-function example
    std::string_view getName() const;

    

    // CppWrappr variant of function pair example that demonstrates allocating and deallocating a buffer
    using LinescanPtr = std::unique_ptr<std::span<unsigned char>, LinescanDeleter>;
    LinescanPtr getLinescan() const;



    // CppWrapper variant of ExampleClassPlugin
    class ExampleClass
    {
        std::shared_ptr<PluginInterface> m_pPluginInterface;
        PluginInterface::CLASSHANDLE     m_ClassHandle;
    public:

        ExampleClass(std::shared_ptr<PluginInterface> pPluginInterface, std::string_view sName);
        ~ExampleClass();

        std::string getName() const;
    };

    using ExampleClassPtr = std::unique_ptr<ExampleClass>;
    ExampleClassPtr createExampleClass(std::string_view sName) const;
};

