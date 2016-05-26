#include "stdafx.h"
#include "ColoredInvi.h"

DWORD addrColorUnit;
DWORD addrColoredInviOriCall;
DWORD addrColoredInviFuncCall;
DWORD addrColoredInviRet;


void __declspec(naked) ColoredInviFunc()
{
	__asm
	{
		PUSHAD;

		MOV EDX, addrLocalPlayerOffset;
		MOV EDX, DWORD PTR DS:[EDX];
		XOR EAX, EAX;
		MOV AL, BYTE PTR DS:[EDX+0x28];
		MOV EDX, DWORD PTR DS:[ESI];

		PUSH 0x4;
		PUSH 0x0;
		PUSH EAX;
		MOV EAX, DWORD PTR DS:[EDX+0xFC];
		MOV ECX, ESI;
		CALL EAX;
		CMP EAX, 0x1;
		JE back;

		XOR EAX, EAX;
		MOV AL, BYTE PTR DS:[ESI+0x5F];
		CMP AL, 0x1;
		JNZ back;

		MOV ECX, ESI;
		PUSH ECX;
		MOV EAX, ESP;
		MOV DWORD PTR DS:[EAX], 0xFFFF0101;
		MOV ECX, DWORD PTR DS:[ECX+0x28];
		XOR EDX, EDX;
		CALL addrColorUnit;

back:
		POPAD;
		CALL addrColoredInviOriCall;
		JMP addrColoredInviRet;
	}
}

void ColoredInviON()
{
	addrColorUnit = GameBase + 0x4D3CA0;
	addrColoredInviOriCall = GameBase + 0x2AC170;

	addrColoredInviFuncCall= GameBase + 0x39A415;
	addrColoredInviRet = GameBase + 0x39A41A;
	PatchJMP((BYTE*)(addrColoredInviFuncCall), (BYTE*) ColoredInviFunc, 5);
}