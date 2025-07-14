#include "PluginInterface.h"
#include <windows.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include <mutex>


// User-side implementation of PluginInterface

class LibraryLoader
{
	const HINSTANCE   m_DllHandle;
	const std::string m_sFilename;

public:
	LibraryLoader(const std::filesystem::path& DllPath)
		: m_DllHandle(LoadLibrary(DllPath.c_str()))
		, m_sFilename(DllPath.filename().string())
	{
		if (!m_DllHandle)
			throw std::runtime_error(std::string("Failed to load dll: ") + m_sFilename);
		std::cout << "Successfully loaded " << m_sFilename << ".\n";
	}

	~LibraryLoader()
	{
		std::cout << "Unloading " << m_sFilename << ".\n";
		FreeLibrary(m_DllHandle);
	}

	template <class T>
	T GetFunctionFromDll(const char* sName)
	{
		T Func = (T)GetProcAddress(m_DllHandle, sName);
		if (Func == nullptr)
			throw std::runtime_error(std::string("Could not find function \"") + sName + "\" in Dll: " + m_sFilename);
		return Func;
	}
};

std::mutex                   g_LibraryLoaderMutex;
std::weak_ptr<LibraryLoader> g_LibraryLoader;



PluginInterfacePtr createPluginInterface(const std::filesystem::path& DllPath)
{
	std::shared_ptr<LibraryLoader> pLibrary;
	{ 
		std::scoped_lock lock{g_LibraryLoaderMutex};
		pLibrary = g_LibraryLoader.lock();
		if (!pLibrary)
			g_LibraryLoader = pLibrary = std::make_shared<LibraryLoader>(DllPath);
	}


	typedef PluginInterface* (__cdecl* createPluginInterfaceProc)(void);
	createPluginInterfaceProc FuncCreate = 
		pLibrary->GetFunctionFromDll<createPluginInterfaceProc>("createPluginInterface");

	typedef void(__cdecl* releasePluginInterfaceProc)(PluginInterface*);
	releasePluginInterfaceProc FuncRelease = 
		pLibrary->GetFunctionFromDll<releasePluginInterfaceProc>("releasePluginInterface");


	PluginInterfacePtr pPluginInterface(FuncCreate(), 
		[pLibrary, FuncRelease](PluginInterface* pPluginInterface) // We bind pLibrary to the lambda to ensure it is not destroyed before the PluginInterface
		{
			std::cout << "Releasing PluginInterface: " << pPluginInterface->getName() << ".\n";
			FuncRelease(pPluginInterface);
		});

	std::cout << "Created PluginInterface: " << pPluginInterface->getName() << ".\n";

	return pPluginInterface;
}
