#pragma once

void EnableDebugPriv();
void PatchJMP(BYTE* source,BYTE* destination, const int length);
void PatchCALL(BYTE* source,BYTE* destination, const int length);
void PlantDetourCALL(BYTE* source, const BYTE* destination, const int length);
char *WideCharToUTF8(const wchar_t *const szWideChar);
bool SetClipBoardText(const char* text);
int dbgPrintf(const char *fmt, ...);