#include "stdafx.h"

DWORD resEAX, resEBX, resECX, resEDX, resESI, resEDI, resEBP, resESP;
DWORD addrResourceDealsJmp;
DWORD addrResourceDealsBack;
DWORD ResourceGold;
DWORD ResourceWood;

char ResourceMsg[200];

void __declspec(naked) ResourceDealsFunc()
{
	__asm
	{
		MOV resEAX, EAX;
		MOV resEBX, EBX;
		MOV resECX, ECX;
		MOV resEDX, EDX;
		MOV resESI, ESI;
		MOV resEDI, EDI;
		MOV resEBP, EBP;
		MOV resESP, ESP;
	}
	memcpy(&ResourceGold,(LPVOID)(resESP+0x1C),4);
	memcpy(&ResourceWood,(LPVOID)(resESP+0x20),4);
	sprintf_s(ResourceMsg,WideCharToUTF8(L"发现资源交易：|cFFFF0000%s|r |cFFDDDDDD给|r |cFFFF0000%s|r |cFFFFFF00%d|r|cFFDDDDDD[金]|r |cFF00FF00%d|r|cFFDDDDDD[木]|r "),
		MyGetPlayerName(MyPlayer(resEDX)),
		MyGetPlayerName(MyPlayer(resEDI)),
		ResourceGold,ResourceWood);
	MyWriteTextToScreen(ResourceMsg,5.0f);
	if (MyIsPlayerEnemy(MyGetLocalPlayer(),MyPlayer(resEDX)))
	{
		sprintf_s(ResourceMsg,WideCharToUTF8(L"反挂助手提示大家：%s 给 %s %d[金] %d[木] "),
			MyGetPlayerName(MyPlayer(resEDX)),
			MyGetPlayerName(MyPlayer(resEDI)),
			ResourceGold,ResourceWood);
		FChat(ResourceMsg,true);
	}
	__asm
	{
		MOV EAX, resEAX;
		MOV EBX, resEBX;
		MOV ECX, resECX;
		MOV EDX, resEDX;
		MOV ESI, resESI;
		MOV EDI, resEDI;
		MOV EBP, resEBP;
		MOV ESP, resESP;
		MOV EDX,dword ptr ds:[ESI+0x30]
		MOV EAX,dword ptr ds:[EDX+0x38]
		JMP addrResourceDealsBack;
	}
}
void ResourceDealsON()
{
	addrResourceDealsJmp=GameBase +0x43F6C0;
	addrResourceDealsBack=GameBase +0x43F6C6;
	PatchJMP((BYTE*)(addrResourceDealsJmp), (BYTE*) ResourceDealsFunc, 6);
}
