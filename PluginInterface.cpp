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

    typedef const char* (__cdecl* GetNameProc)(void);
    GetNameProc FuncGetName;

    typedef bool(__cdecl* GetLinescanProc)(unsigned char*& pLine, unsigned long& ulLength);
    GetLinescanProc FuncGetLinescan;

    typedef void(__cdecl* FreeLinescanProc)(unsigned char* pLine);
    FreeLinescanProc FuncFreeLinescan;
};


PluginInterface::PluginInterface(const char* sDllPath)
    : m_pMembers(new PluginInterface::MEMBERS)
{
    m_pMembers->DllHandle = LoadLibraryA(sDllPath);
    if (!m_pMembers->DllHandle)
        throw std::runtime_error(std::string("Failed to load dll: ") + sDllPath);

    m_pMembers->FuncGetName = GetFunctionFromDll<MEMBERS::GetNameProc>(
        m_pMembers->DllHandle, "getName", sDllPath);

    m_pMembers->FuncGetLinescan = GetFunctionFromDll<MEMBERS::GetLinescanProc>(
        m_pMembers->DllHandle, "getLinescan", sDllPath);

    m_pMembers->FuncFreeLinescan = GetFunctionFromDll<MEMBERS::FreeLinescanProc>(
        m_pMembers->DllHandle, "freeLinescan", sDllPath);

    // Test
    std::cout << "Successfully loaded " << sDllPath << ". Plugin name: " << getName() << ".\n";
}


PluginInterface::~PluginInterface()
{
    std::cout << "Unloading plugin: " << getName() << ".\n";

    FreeLibrary(m_pMembers->DllHandle);
    delete m_pMembers;
}


const char* PluginInterface::getName() const
{
    return m_pMembers->FuncGetName();
}


bool PluginInterface::getLinescan(unsigned char*& pLine, unsigned long& ulLength) const
{
    return m_pMembers->FuncGetLinescan(pLine, ulLength);
}


void PluginInterface::freeLinescan(unsigned char* pLine) const
{
    m_pMembers->FuncFreeLinescan(pLine);
}

