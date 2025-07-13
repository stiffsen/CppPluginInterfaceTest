// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "../PluginInterface.h"

extern "C" DLLAPI BOOL APIENTRY DllMain(HINSTANCE inst, DWORD reason, LPVOID reserved) 
{
    switch (reason) {
    case DLL_PROCESS_ATTACH:
        // attach to process
        // return FALSE to fail DLL load
        break;

    case DLL_PROCESS_DETACH:
        // detach from process
        break;

    case DLL_THREAD_ATTACH:
        // attach to thread
        break;

    case DLL_THREAD_DETACH:
        // detach from thread
        break;
    }
    return TRUE; // succesful
}
