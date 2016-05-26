#include "stdafx.h"
#include "Gamestate.h"


DWORD NowGamestate, OldGamestate;

DWORD TlsValue;

DWORD _W3XTlsIndex;
DWORD _LoadingBarPtr;
DWORD _ChangeLBText;

DWORD GetW3TlsForIndex(DWORD index)
{
	DWORD pid = GetCurrentProcessId();
	THREADENTRY32 te32;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, pid);
	te32.dwSize = sizeof(THREADENTRY32);
	if (Thread32First(hSnap, &te32))
	{
		do
		{
			if (te32.th32OwnerProcessID == pid)
			{
				HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, false, te32.th32ThreadID);
				CONTEXT ctx = { CONTEXT_SEGMENTS };
				LDT_ENTRY ldt;
				GetThreadContext(hThread, &ctx);
				GetThreadSelectorEntry(hThread, ctx.SegFs, &ldt);
				DWORD dwThreadBase = ldt.BaseLow | (ldt.HighWord.Bytes.BaseMid <<
					16) | (ldt.HighWord.Bytes.BaseHi << 24);
				CloseHandle(hThread);
				if (dwThreadBase == NULL)
					continue;
				DWORD* dwTLS = *(DWORD**)(dwThreadBase + 0xE10 + 4 * index);
				if (dwTLS == NULL)
					continue;
				return (DWORD)dwTLS;
			}
		} while (Thread32Next(hSnap, &te32));
	}

	return NULL;
}

DWORD GetIndex()
{
	return *(DWORD*)(_W3XTlsIndex);
}
void GetTlsValue()
{
	DWORD TlsIndex = GetIndex();
	LPVOID tls = (LPVOID)GetW3TlsForIndex(TlsIndex);
	TlsSetValue(TlsIndex, tls);
	TlsValue = (DWORD)tls;
}

DWORD GetGameStateValue()
{
	DWORD rt;
	if (!ReadProcessMemory(GetCurrentProcess(), (LPVOID)(TlsValue + 4 * 0x0D), (LPVOID)&rt, 4, NULL))
		return -1;
	if (!ReadProcessMemory(GetCurrentProcess(), (LPVOID)(rt + 0x10), (LPVOID)&rt, 4, NULL))
		return -1;
	if (!ReadProcessMemory(GetCurrentProcess(), (LPVOID)(rt + 0x8), (LPVOID)&rt, 4, NULL))
		return -1;
	if (!ReadProcessMemory(GetCurrentProcess(), (LPVOID)(rt + 0x278), (LPVOID)&rt, 4, NULL))
		return -1;
	return rt;
}
bool GameStateUpdate(DWORD Value)
{
	if (Value != NowGamestate)
	{
		if (NowGamestate==GS_INGAME)
		{
			NumShowClear();
			LocalHero=NULL;
			//lua_tinker::call<void>(L, "GameOver");
		}
		OldGamestate = NowGamestate;
		NowGamestate = Value;
		return true;
	}
	return false;
}

void HandleGameStateChange(DWORD newstate)
{
	switch (newstate)
	{
	case GS_NOTHING:
		break;
	case GS_LOBBY:
		break;
	case GS_LOADING:
		char Text[200];
		sprintf_s(Text,"L O A D I N G : [ JasHack ] By JasKang");
		ChangeLoadingBarText(Text);
		break;
	case GS_INGAME:
		//lua_tinker::call<void>(L, "GameStateChange",newstate);
		//lua_tinker::call<void>(L, "GameBegin");

		break;
	case GS_PAUSEDGAME:
		break;
	default:
		break;
	}
	OldGamestate = newstate;
}

void GameStateThread()
{
	while (true)
	{
		DWORD p = GetGameStateValue();
		if (p == -1)
			continue;
		if (GameStateUpdate(p))
			HandleGameStateChange(p);
		Sleep(10);
	}
}

bool ChangeLoadingBarText(char* newtext)
{
	__asm
	{
looplbl:
		MOV EAX,DWORD PTR DS:[_LoadingBarPtr]
		MOV EAX,DWORD PTR DS:[EAX]
		TEST EAX, EAX;
		JE looplbl;
		MOV ECX, DWORD PTR DS : [EAX + 0x190];
		TEST ECX, ECX;
		JE endlbl;
		MOV EAX, newtext;
		PUSH EAX;
		CALL _ChangeLBText;
	}
	return true;
endlbl:
	return false;
}

void GameStateInit()
{
	LocalHero=NULL;
	//_124B
	_W3XTlsIndex = GameBase + 0xACEA4C;
	_LoadingBarPtr = GameBase + 0xAE3BC4;
	_ChangeLBText = GameBase + 0x612430;

	//_124E
// 	_W3XTlsIndex = War3.GameBase + 0xACEA4C;
// 	_LoadingBarPtr = War3.GameBase + 0xAE3BC4;
// 	_ChangeLBText = War3.GameBase + 0x6124E0;

	//_126A
// 	_W3XTlsIndex = War3.GameBase + 0xAB7BF4;
// 	_LoadingBarPtr = War3.GameBase + 0xACCD6C;
// 	_ChangeLBText = War3.GameBase + 0x611D40;
	GetTlsValue();		//ÓÎÏ·×´Ì¬
	GameStateThread();
}
