#include "PluginCppWrapper.h"
#include <iostream>


PluginCppWrapper::PluginCppWrapper(const std::filesystem::path& DllPath)
    : m_pPluginInterface(std::make_shared<PluginInterface>(DllPath.string().c_str()))
{
    m_LinescanDeleter = 
        [pPluginInterface = m_pPluginInterface](std::span<unsigned char>* pDel)
        {
            if (pDel == nullptr)
                return;
            pPluginInterface->freeLinescan(pDel->data());
            delete pDel;
            std::cout << "Linescan buffered freed.\n";
        };
}


std::unique_ptr<PluginCppWrapper> PluginCppWrapper::create(const std::filesystem::path& DllPath)
{
    try
    {
        return std::unique_ptr<PluginCppWrapper>(new PluginCppWrapper(DllPath));
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



PluginCppWrapper::LinescanPtr PluginCppWrapper::getLinescan() const
{
    unsigned char* pBuffer{ nullptr };
    unsigned long  ulLength{ 0 };
    if (!m_pPluginInterface->getLinescan(pBuffer, ulLength))
        return nullptr;

    LinescanPtr pResult(
        new std::span<unsigned char>(pBuffer, static_cast<size_t>(ulLength)),
        m_LinescanDeleter);

    std::cout << "Linescan retrieved\n";

    return pResult;
}






PluginCppWrapper::ExampleClass::ExampleClass(std::shared_ptr<PluginInterface> pPluginInterface, std::string_view sName)
    : m_pPluginInterface{ pPluginInterface }
    , m_ClassHandle{ pPluginInterface->ExampleClass_create(sName.data()) }
{
    if (m_ClassHandle < 0)
        throw std::runtime_error("Failed to create class.");

    std::cout << "Created ExampleClass with name: " << sName << '\n';
}


PluginCppWrapper::ExampleClass::~ExampleClass()
{
    std::cout << "Deleted ExampleClass with name: " << getName() << '\n';
    m_pPluginInterface->ExampleClass_free(m_ClassHandle);
}


std::string PluginCppWrapper::ExampleClass::getName() const
{
    const char* sName{ nullptr };
    m_pPluginInterface->ExampleClass_getName(m_ClassHandle, sName);
    return sName; // may be null if previous call fails
}



std::unique_ptr<PluginCppWrapper::ExampleClass> PluginCppWrapper::createExampleClass(std::string_view sName) const
{
    return std::make_unique<ExampleClass>(m_pPluginInterface, sName);
}