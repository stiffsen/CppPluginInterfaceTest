#pragma once

#ifdef BUILD_DLL
#define DLLAPI __declspec(dllexport)
#define DLLAPI_SUFFIX
#else
#define DLLAPI
#define DLLAPI_SUFFIX const
#endif


#ifdef BUILD_DLL
extern "C" 
{
#else
class PluginInterface
{
    struct MEMBERS;
    MEMBERS* m_pMembers{nullptr};
public:
    PluginInterface(const char* sPath);
    ~PluginInterface();
#endif

    DLLAPI const char* getName() DLLAPI_SUFFIX;    
    
    DLLAPI bool getLinescan(unsigned char*& pLine, unsigned long& ulLength) DLLAPI_SUFFIX;

    DLLAPI void freeLinescan(unsigned char* pLine) DLLAPI_SUFFIX;

};