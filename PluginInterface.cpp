#include "PluginInterface.h"
#include <windows.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include "PluginCppWrapper.h"


// User-side implementation of PluginInterface


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

    typedef bool(__cdecl* GetLinescanProc)(unsigned char*&, unsigned long&);
    GetLinescanProc FuncGetLinescan;

    typedef void(__cdecl* FreeLinescanProc)(unsigned char*);
    FreeLinescanProc FuncFreeLinescan;

    typedef CLASSHANDLE(__cdecl* ExampleClass_createProc)(const char*);
    ExampleClass_createProc FuncExampleClass_create;

    typedef bool(__cdecl* ExampleClass_freeProc)(CLASSHANDLE);
    ExampleClass_freeProc FuncExampleClass_free;

    typedef bool(__cdecl* ExampleClass_getNameProc)(CLASSHANDLE, const char*&);
    ExampleClass_getNameProc FuncExampleClass_getName;
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



    m_pMembers->FuncExampleClass_create = GetFunctionFromDll<MEMBERS::ExampleClass_createProc>(
        m_pMembers->DllHandle, "ExampleClass_create", sDllPath);

    m_pMembers->FuncExampleClass_free = GetFunctionFromDll<MEMBERS::ExampleClass_freeProc>(
        m_pMembers->DllHandle, "ExampleClass_free", sDllPath);

    m_pMembers->FuncExampleClass_getName = GetFunctionFromDll<MEMBERS::ExampleClass_getNameProc>(
        m_pMembers->DllHandle, "ExampleClass_getName", sDllPath);

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



PluginInterface::CLASSHANDLE PluginInterface::ExampleClass_create(const char* sName) const
{
    return m_pMembers->FuncExampleClass_create(sName);
}

bool PluginInterface::ExampleClass_free(CLASSHANDLE Index) const
{
    return m_pMembers->FuncExampleClass_free(Index);
}

bool PluginInterface::ExampleClass_getName(CLASSHANDLE Index, const char*& sName) const
{
    return m_pMembers->FuncExampleClass_getName(Index, sName);
}