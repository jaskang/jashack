#include "stdafx.h"





DWORD addrGreyHPFuncCall;



void __declspec(naked) GreyHPFunc()
{

	__asm
	{
		PUSHAD;

		MOV EDX, addrLocalPlayerOffset;
		MOV EDX,DWORD PTR DS:[EDX];
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
		JE visible;

		POPAD;

		MOV EAX, DWORD PTR SS:[ESP+0x4];
		OR DWORD PTR DS:[EAX], 0xDD00FF;
		MOV DL, BYTE PTR DS:[EAX+0x3];
		MOV BYTE PTR DS:[ECX+0x68], DL;
		MOV DL, BYTE PTR DS:[EAX];
		MOV BYTE PTR DS:[ECX+0x69], DL;
		MOV DL, BYTE PTR DS:[EAX+0x1];
		MOV BYTE PTR DS:[ECX+0x6A], DL;
		MOV DL, BYTE PTR DS:[EAX+0x2];
		MOV BYTE PTR DS:[ECX+0x6B], DL;

		MOV EDX, DWORD PTR DS:[ECX];
		MOV EAX, DWORD PTR DS:[EDX+0x24];
		CALL EAX;
		RET 0x4;

visible:
		POPAD;

		MOV EAX, DWORD PTR SS:[ESP+0x4];
		MOV DL, BYTE PTR DS:[EAX+0x3];
		MOV BYTE PTR DS:[ECX+0x68], DL;
		MOV DL, BYTE PTR DS:[EAX];
		MOV BYTE PTR DS:[ECX+0x69], DL;
		MOV DL, BYTE PTR DS:[EAX+0x1];
		MOV BYTE PTR DS:[ECX+0x6A], DL;
		MOV DL, BYTE PTR DS:[EAX+0x2];
		MOV BYTE PTR DS:[ECX+0x6B], DL;

		MOV EDX, DWORD PTR DS:[ECX];
		MOV EAX, DWORD PTR DS:[EDX+0x24];
		CALL EAX;
		RET 0x4;
	}

}

void GreyHPON()
{
	addrGreyHPFuncCall=GameBase+ 0x365672;
	PatchCALL((BYTE*)(addrGreyHPFuncCall), (BYTE*) GreyHPFunc, 5);
}