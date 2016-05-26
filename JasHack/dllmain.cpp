// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"


HMODULE DllModule;
HWND wHandle;
DWORD GameBase;
DWORD NewGameBase;
DWORD StormBase;
DWORD LocalHero;
VOID MainThread( LPVOID )
{
	while (GetModuleHandle("Game.dll") == NULL) Sleep(1000);
	wHandle=FindWindow("Warcraft III",NULL);
	GameBase = (DWORD)GetModuleHandle("Game.dll");
	StormBase = (DWORD)GetModuleHandle("Storm.dll");
	InitSafeMap();
	InitJass(GameBase);
	Sleep(1000);
	NumShowON();
	ResourceDealsON();
	GreyHPON();
	DamageNotifierON();
	ColoredInviON();
	HeroLineON();
	UnitCommandON();
	GameStateInit();
	return;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		DllModule = hModule;
		DisableThreadLibraryCalls(hModule);
		EnableDebugPriv();
		_beginthread(MainThread,0, NULL);
		//CloseHandle(mainThread);
	}else if (ul_reason_for_call == DLL_THREAD_ATTACH)
	{

	}else if (ul_reason_for_call == DLL_THREAD_DETACH)
	{

	}else if (ul_reason_for_call == DLL_PROCESS_DETACH)
	{
		KillTimer(wHandle,6666) ;
	}
	return TRUE;
}

