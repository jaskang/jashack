#include "stdafx.h"
#include "VSPatch.h"


DWORD WarAHEAX, WarAHEBX, WarAHECX, WarAHEDX, WarAHESI, WarAHEDI, WarAHEBP, WarAHESP;

DWORD WarAHBase;
DWORD NewWarAHBase;

DWORD WarAHJMP;
DWORD WarAHBack;

void __declspec(naked) WarAHFunc()
{
	__asm
	{
		MOV WarAHEAX, EAX;
		MOV WarAHEBX, EBX;
		MOV WarAHECX, ECX;
		MOV WarAHEDX, EDX;
		MOV WarAHESI, ESI;
		MOV WarAHEDI, EDI;
		MOV WarAHEBP, EBP;
		MOV WarAHESP, ESP;
	}
	if ((WarAHECX>(GameBase + 0x01000)) && (WarAHECX<(GameBase + 0x88E000)))
	{
		WarAHECX = WarAHECX - GameBase + NewGameBase;
	}
	if ((WarAHECX>WarAHBase) && (WarAHECX<(WarAHBase + 0x00058000)))
	{
		WarAHECX = WarAHECX - WarAHBase + NewWarAHBase;
	}
	__asm
	{
		MOV EAX, WarAHEAX;
		MOV EBX, WarAHEBX;
		MOV ECX, WarAHECX;
		MOV EDX, WarAHEDX;
		MOV ESI, WarAHESI;
		MOV EDI, WarAHEDI;
		MOV EBP, WarAHEBP;
		MOV ESP, WarAHESP;
		MOVZX EDX, byte ptr ds : [ECX];
		xor eax, EDX;
		JMP WarAHBack;
	}
}
void VSPatch()
{
	WarAHBase = (DWORD)GetModuleHandleA("WarAH.dll");
	if (WarAHBase)
	{

		//WarAH.dll+0x15C7A    0FB611                          movzx edx,byte ptr ds:[ecx]
		//WarAH.dll+0x15C7D    33C2                            xor eax,edx
		//WarAH.dll+0x15C7F    8B0485 08A42500                 mov eax,dword ptr ds:[eax*4+0x25A408]
		NewWarAHBase = (DWORD)VirtualAlloc(0, 0x00058000, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		memcpy((LPVOID)NewWarAHBase, (LPVOID)WarAHBase, 0x00058000);

		WarAHJMP = WarAHBase + 0x15C7A;
		WarAHBack = WarAHBase + 0x15C7F;
		PatchJMP((BYTE*)(WarAHJMP), (BYTE*)WarAHFunc, 5);
		dbgPrintf("patchvs");
	}
}
