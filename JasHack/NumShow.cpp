#include "stdafx.h"

static map<DWORD, DWORD> units;

void CALLBACK NumShowProc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)
{
	if (NowGamestate==GS_INGAME)
	{
		DWORD len = 0;
		DWORD arr = JGetUnitArray(len);

		for (DWORD i = 0; i < len; i++)
		{
			Unit* unt = (Unit*)*(DWORD*)(arr + i * 4);
			DWORD handle = MyGetUnitByOffset((DWORD)unt);
			if (!MyIsUnitIllusion(handle) && MyIsUnitHero(handle))
			{
				map<DWORD, DWORD>::iterator iter = units.find(handle);
				if (units.end() == iter)
				{
					if (MyIsUnitOwnedByPlayer(handle, MyGetLocalPlayer()))
					{
						//lua_tinker::set(L, "LocalHero", handle);
						LocalHero=handle;
					}
					units.insert(make_pair(handle, 0));
				}
			}
		}

		map<DWORD, DWORD>::iterator it=units.begin();   
		for(;it!=units.end();++it){
			if (it->second==0)
			{
				it->second=MyCreateTextTag();
				MySetTextTagColor(it->second, 255, 255, 255, 255);
				MySetTextTagPermanent(it->second, true);
				MySetTextTagVisibility(it->second, true);
			}
			else
			{
				char NumShoweMsg[200];
				sprintf_s(NumShoweMsg,"|cFF00FF00%d|r|cFFFFFFFF/|r|cFF00FFFF%d|r",
					(int)MyGetUnitState(it->first,0),(int)MyGetUnitState(it->first,2)
					);
				MyChangeTexttagText(it->second,NumShoweMsg,25,0);
				MySetTextTagPosUnit(it->second,it->first,15);
			}
		} 
	} 
		
	
}
void NumShowClear()
{
	units.clear();
}
void NumShowON(){
	SetTimer(wHandle, 6666, 50, (TIMERPROC)NumShowProc);
}