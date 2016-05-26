#pragma once

extern DWORD NewGameBase;

#define PATCH(des,ori) WriteCodeTo((void*)((UINT)des + GameBase), (void*)ori, sizeof(ori)-1)
#define PATCHSafeMap(des,ori) WriteCodeTo((void*)((UINT)des + NewGameBase), (void*)ori, sizeof(ori)-1)

void WriteCodeTo(void* addrDest, void* addrNewCode, UINT size);
DWORD AllowMemoryOperate(void* addr, UINT size, BOOL AllowExecute = FALSE);

void HackOn();
void HackOff();

void InitSafeMap();

