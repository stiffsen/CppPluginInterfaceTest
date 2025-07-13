#include "pch.h"
#include "../PluginInterface.h"

#ifdef __cplusplus
extern "C" {        // export the functions with C linkage
#endif

const char* getName() { return "PluginA"; }

#ifdef __cplusplus
} // extern "C"
#endif