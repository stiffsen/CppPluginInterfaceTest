#pragma once

#include <string>
#include <functional>
#include <memory>
#include <span>
#include <filesystem>

#ifdef BUILD_DLL
#define DLLAPI __declspec(dllexport)
#else
#define DLLAPI
#endif


// This file is shared by Plugin and User
// - Plugin: Only C-Functions to create and release the PluginInterface
// - User: A single function that loads the DLL and returns a pointer to the created PluginInterface. The pointer manages the lifetime of both PluginInterface and loaded DLL.


class PluginInterface
{
public:
	virtual ~PluginInterface() {};

	virtual const std::string& getName() = 0;

	using LinescanDeleter = std::function<void(std::span<unsigned char>*)>;
	using LinescanPtr     = std::unique_ptr<std::span<unsigned char>, LinescanDeleter>;
	virtual LinescanPtr getLinescan() const = 0;



	class ExampleClass
	{
	public:
		virtual ~ExampleClass() {};

		virtual const std::string& getName() const = 0;
	};

	using ExampleClassPtr = std::unique_ptr<ExampleClass>;
	virtual ExampleClassPtr createExampleClass(std::string_view sName) const = 0;

};

#ifdef BUILD_DLL

extern "C" 
{

DLLAPI PluginInterface* createPluginInterface();
DLLAPI void releasePluginInterface(PluginInterface* pPluginInterface);

}
#else

using PluginInterfaceDeleter = std::function<void(PluginInterface*)>;
using PluginInterfacePtr = std::unique_ptr<PluginInterface, PluginInterfaceDeleter>;
PluginInterfacePtr createPluginInterface(const std::filesystem::path& DllPath);

#endif