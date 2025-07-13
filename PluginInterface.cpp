#include "PluginInterface.h"
#include <windows.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include "PluginCppWrapper.h"


template <class T>
T GetFunctionFromDll(HINSTANCE dll, const char* sName, const char* sDllPath)
{
    T Func = (T)GetProcAddress(dll, sName);
    if (Func == nullptr)
        throw std::runtime_error(std::string("Could not find function \"") + sName + "\" in Dll: " + sDllPath);
    return Func;
}


struct PluginInterface::MEMBERS
{
    HINSTANCE DllHandle;

    typedef const char* (__cdecl* getNameProc)(void);
    getNameProc FuncGetName;
};


PluginInterface::PluginInterface(const char* sDllPath)
    : m_pMembers(new PluginInterface::MEMBERS)
{
    m_pMembers->DllHandle = LoadLibraryA(sDllPath);
    if (!m_pMembers->DllHandle)
        throw std::runtime_error(std::string("Failed to load dll: ") + sDllPath);

    m_pMembers->FuncGetName = GetFunctionFromDll<MEMBERS::getNameProc>(
        m_pMembers->DllHandle, "getName", sDllPath);
}


PluginInterface::~PluginInterface()
{
    FreeLibrary(m_pMembers->DllHandle);
    delete m_pMembers;
}


const char* PluginInterface::getName() const
{
    return m_pMembers->FuncGetName();
}

