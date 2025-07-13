#pragma once
#include <windows.h>

class PluginLoader
{
public:
    PluginLoader(const char* sDllPath);
    ~PluginLoader();

    typedef const char* (__cdecl* getNameProc)(void);
    getNameProc getName;

private:
    HINSTANCE m_DllHandle{0};
};

