#pragma once

#ifdef BUILD_DLL
#define DLLAPI __declspec(dllexport)
#else
#define DLLAPI virtual
#endif

// TODO: Merge plugin loader into Interface.h so that we don't have to declare these methods multiple times

extern "C" 
{

    DLLAPI const char* getName();

}