#pragma once

#ifdef BUILD_DLL
#define DLLAPI __declspec(dllexport)
#else
#define DLLAPI
#endif

#ifdef __cplusplus
extern "C" {        // export the functions with C linkage
#endif

DLLAPI const char* getName();

#ifdef __cplusplus
} // extern "C"
#endif