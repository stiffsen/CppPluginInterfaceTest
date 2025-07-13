#pragma once

#ifdef BUILD_DLL
#define DLLAPI __declspec(dllexport)
#define DLLAPI_SUFFIX
#else
#define DLLAPI
#define DLLAPI_SUFFIX const
#endif

// This file is shared by Plugin and User
// - Plugin: Only C-Functions
// - User: A class managing the lifetime of the loaded DLL and providing access to all plugin functions

#ifdef BUILD_DLL
extern "C" 
{
#else
class PluginInterface
{
    struct MEMBERS; // basically PIMPL-idiom, but only holds function pointers and DLL handle
    MEMBERS* m_pMembers{nullptr};
public:
    PluginInterface(const char* sPath);
    ~PluginInterface();
#endif


    // Example for a simple plugin-function
    DLLAPI const char* getName() DLLAPI_SUFFIX;    

    
    // Function pair that demonstrates allocating and deallocating a buffer
    DLLAPI bool getLinescan(unsigned char*& pLine, unsigned long& ulLength) DLLAPI_SUFFIX;
    DLLAPI void freeLinescan(unsigned char* pLine) DLLAPI_SUFFIX;


    // Example for a class wrapped by a c-interface
    // -> Class is instanciated inside the plugin and we only get a handle to that class. All interaction with that class is performed through that handle.
    typedef long CLASSHANDLE;
    DLLAPI CLASSHANDLE ExampleClass_create(const char* sName) DLLAPI_SUFFIX;
    DLLAPI bool ExampleClass_free(CLASSHANDLE Index) DLLAPI_SUFFIX;
    DLLAPI bool ExampleClass_getName(CLASSHANDLE Index, const char*& sName) DLLAPI_SUFFIX;
};