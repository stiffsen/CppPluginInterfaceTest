#include "PluginLoader.h"
#include <windows.h>
#include <string>
#include <stdexcept>


template <class T>
T FindFunctionInDll(HINSTANCE dll, const char* sName, const char* sDllPath)
{
    T Func = (T)GetProcAddress(dll, sName);
    if (Func == nullptr)
        throw std::runtime_error(std::string("Could not find function \"") + sName + "\" in Dll: " + sDllPath);
    return Func;
}

PluginLoader::PluginLoader(const char* sDllPath)
{
    m_DllHandle = LoadLibraryA(sDllPath);
    if (!m_DllHandle)
        throw std::runtime_error(std::string("Failed to load dll: ") + sDllPath);

    getName = FindFunctionInDll<getNameProc>(m_DllHandle, "getName", sDllPath);
}

PluginLoader::~PluginLoader()
{
    FreeLibrary(m_DllHandle);
}

