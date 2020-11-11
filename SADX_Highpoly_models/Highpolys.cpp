#include "SADXModLoader.h"
#include <stdio.h>

//Macros
#define ReplacePVM(a, b) helperFunctions.ReplaceFile("system\\" a ".PVM", "system\\" b ".PVM");

extern "C"
{
	__declspec(dllexport) __declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
	ReplacePVM("sonic", "sonicnm");
	ReplacePVM("supersonic", "supersonicnm")
	ReplacePVM("Miles", "Milesnm")
	}
	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}