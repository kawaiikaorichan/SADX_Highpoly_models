#include "SADXModLoader.h"
#include <stdio.h>
#include "IniFile.hpp"

//Macros
#define ReplacePVM(a, b) helperFunctions.ReplaceFile("system\\" a ".PVM", "system\\" b ".PVM");

//Options
enum SuperSText { Dreamcast, Upgraded };

static int SSText = Upgraded;

extern "C"
{
	__declspec(dllexport) __declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
	//Disable morphs
		WriteData<3>((void*)0x45BB60, 0x90u);
		WriteData<3>((void*)0x45B821, 0x90u);
		WriteData<3>((void*)0x45BB74, 0x90u);
		WriteData<3>((void*)0x45B821, 0x90u);
		WriteData<3>((void*)0x45BED3, 0x90u);
		WriteData<3>((void*)0x45DAB1, 0x90u);
		WriteData<3>((void*)0x461389, 0x90u);
		WriteData<3>((void*)0x461325, 0x90u);
		WriteData<3>((void*)0x45BEE7, 0x90u);
		WriteData<3>((void*)0x45DACA, 0x90u);
		WriteData<3>((void*)0x4613A1, 0x90u);
		WriteData<3>((void*)0x461339, 0x90u);
		WriteData<3>((void*)0x473FB2, 0x90u);
		WriteData<3>((void*)0x473CC1, 0x90u);
		WriteData<3>((void*)0x473FC7, 0x90u);
		WriteData<3>((void*)0x473CD5, 0x90u);

	//Functions
	const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
	std::string SSText_String = "Upgraded";
	SSText_String = config->getString("Textures", "SS", "Upgraded");
	if (SSText_String == "Dreamcast") SSText = Dreamcast;
	if (SSText_String == "Upgraded") SSText = Upgraded;

	//Replace textures
	ReplacePVM("sonic", "sonicnm");
	ReplacePVM("Miles", "Milesnm")
	ReplacePVM("knuckles", "knucklesnm")
	ReplacePVM("amy", "amynm")

	if (SSText == Dreamcast)
	{
		ReplacePVM("supersonic", "supersonicnmc")
	}

	if (SSText == Upgraded)
	{
		ReplacePVM("supersonic", "supersonicnm")
	}
	}
	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}