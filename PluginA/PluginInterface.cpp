#include "pch.h"
#include "../PluginInterface.h"
#include <iostream>

// Plugin-side implementation of PluginInterface


class ExampleClassImpl : public PluginInterface::ExampleClass
{
	std::string m_sName;

public:
	ExampleClassImpl(std::string_view sName)
		: m_sName(sName)
	{
		std::cout << "Plugin: Created ExampleClass with name: " << m_sName << '\n';
	}

	~ExampleClassImpl()
	{
		std::cout << "Plugin: Destroying ExampleClass with name: " << m_sName << '\n';
	}

	const std::string& getName() const override
	{
		return m_sName;
	}
};



const std::string g_sPluginName{ "PluginA" };

class PluginInterfaceImpl : public PluginInterface
{
public:

	const std::string& getName() override
	{
		return g_sPluginName;
	}


	LinescanPtr getLinescan() const override
	{
		size_t uLength = 10;
		unsigned char* pLine = new unsigned char[uLength];
		memset(pLine, 0, static_cast<size_t>(uLength));

		// Test: Dummy values
		{
			static int uCounter = 0;
			pLine[uCounter] = 1;
			uCounter = (uCounter + 1) % uLength; // Wrap around to avoid out-of-bounds access
		}

		std::cout << "Plugin: Allocated linescan\n";

		return LinescanPtr(new std::span<unsigned char>(pLine, uLength), 
			[](std::span<unsigned char>* pSpan) {
				delete[] pSpan->data();
				delete pSpan;
				std::cout << "Plugin: Freed linescan\n"; 
			});
	}


	PluginInterface::ExampleClassPtr PluginInterface::createExampleClass(std::string_view sName) const
	{
		return std::make_unique<ExampleClassImpl>(sName);
	}
};


extern "C"
PluginInterface* createPluginInterface() 
{ 
	std::cout << "Plugin: Creating PluginInterface\n";
    return new PluginInterfaceImpl(); 
}


extern "C"
void releasePluginInterface(PluginInterface* pPluginInterface)
{
	std::cout << "Plugin: Releasing PluginInterface\n";
	delete pPluginInterface;
}
