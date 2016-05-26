#pragma once

struct sCreateHotKey
{
	int ID;
	UINT Mods;
	UINT vk;
	int FreeHandle;
};


extern HMODULE DllModule;
extern HWND wHandle;
extern DWORD GameBase;
extern DWORD NewGameBase;
extern DWORD StormBase;

extern DWORD LocalHero;