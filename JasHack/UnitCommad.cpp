#include "stdafx.h"
#include "UnitCommad.h"


DWORD addrCmdHookConst;
DWORD addrUnitCmdHook;
DWORD addrUnitCmdHookJMP;

char CommadMsg[200];
void ZSGWS_ITEM(DWORD hUnit,int slot,float x,float y)
{
	DWORD tmpItem = MyUnitItemInSlot(hUnit, slot);
	DWORD tmpTypeId = MyGetItemTypeId(tmpItem);
}


void ZSGWS_T(DWORD hUnit,float x,float y)
{
	if (MyUseItem(LocalHero,ITEM_XW))
	{
		MyWriteTextToScreen(WideCharToUTF8(L"[|cFFFF9900JasHack|r]|cFF999999:|r触发|cFFCE0005[玄武]|r躲技能!!!"));
		return;
	}
	Location loc=MyGetUnitFaceLoc(LocalHero,700);
	if (MyUseItemLoc(LocalHero,ITEM_XX,loc.X,loc.Y))
	{
		MyWriteTextToScreen(WideCharToUTF8(L"[|cFFFF9900JasHack|r]|cFF999999:|r触发|cFFCE0005[翔靴]|r躲技能!!!"));
		return;
	}
	if (MyUseItem(LocalHero,ITEM_FX)){
		MyWriteTextToScreen(WideCharToUTF8(L"[|cFFFF9900JasHack|r]|cFF999999:|r触发|cFFCE0005[风行]|r躲技能!!!"));
		return;
	}
	if (MyUseItemTarget(LocalHero,ITEM_YZ,hUnit))
	{
		MyWriteTextToScreen(WideCharToUTF8(L"[|cFFFF9900JasHack|r]|cFF999999:|r触发|cFFCE0005[羊帐]|r躲技能!!!"));
		return;
	}
	if (MyUseItemTarget(LocalHero,ITEM_FZ,hUnit))
	{
		MyWriteTextToScreen(WideCharToUTF8(L"[|cFFFF9900JasHack|r]|cFF999999:|r触发|cFFCE0005[风帐]|r躲技能!!!"));
		return;
	}
	if (MyGetUnitTypeId(LocalHero)==HERO_ID_CR)
	{
		MyUseSkillTarget(LocalHero,Action_CR_E,hUnit);
		return;
	}
	if (MyGetUnitTypeId(LocalHero)==HERO_ID_XUN)
	{
		MyUseSkillTarget(LocalHero,Action_XUN_W,hUnit);
		return;
	}

}



void ProcessGameCmd(Unit* unit, Command* CommandData, DWORD targetUint)
{
	DWORD handle = MyGetUnitByOffset((DWORD)unit);
	switch (CommandData->CommandId)
	{
	case MOVE:
	case ATTACK:
		{
			Location loc;
			loc.X = CommandData->X;
			loc.Y = CommandData->Y;
			if ((A2I((DWORD)unit + 0x1EC) != NULL) && !MyIsUnitIllusion(handle))
			{
				AddHeroLine(unit, loc);
			}
		}
		break;
	case STOP:
	case HOLD:
		{
			if ((A2I((DWORD)unit + 0x1EC) != NULL) && !MyIsUnitIllusion(handle))
			{
				RemoveHeroLine(unit);
			}
		}
		break;
	case Action_T:
		{
			if (MyIsUnitEnemy(handle,MyGetLocalPlayer()))
			{
				if (unit->dwClassId==HERO_ID_ZF || unit->dwClassId==HERO_ID_DW)
				{
					float ax=MyGetUnitX(handle);
					float ay=MyGetUnitY(handle);
					if (MyIsCanHurtMe(350, ax, ay))
					{
						ZSGWS_T(handle,ax,ay);
					}
				}
			}
		}
		break;
	case ITEM1:
		{
			DWORD tmpItem = MyUnitItemInSlot(handle, 0);
			DWORD tmpTypeId = MyGetItemTypeId(tmpItem);
			
		}
		break;
	case ITEM2:
		break;
	case ITEM3:
		break;
	case ITEM4:
		break;
	case ITEM5:
		break;
	case ITEM6:
		break;
	default:
		break;
	}
}

void _declspec(naked) UnitCommandHook()
{
	__asm
	{
		PUSH EBP;
		MOV EBP,ESP;
		SUB ESP,0x38;
		PUSHAD;
	}
	Unit* unt;
	Command* CommandData;
	DWORD targetUint;
	__asm
	{
		MOV EAX,DWORD PTR DS:[EBP+0xC];
		mov unt,EAX;
		MOV EAX,DWORD PTR DS:[EBP+0x10];
		mov CommandData,EAX;
		MOV EAX, DWORD PTR DS : [EBP + 0x80];
		mov targetUint, EAX;
	}
	ProcessGameCmd(unt, CommandData,targetUint);
	__asm
	{
		POPAD;
		MOV ESP,EBP;
		POP EBP;
		PUSH addrCmdHookConst;
		JMP addrUnitCmdHookJMP;
	}
}


void UnitCommandON()
{
	addrCmdHookConst=GameBase+0x82AD40;
	addrUnitCmdHook=GameBase+0x2CB262;
	addrUnitCmdHookJMP=GameBase+0x2CB267;
	PatchJMP((BYTE*)(addrUnitCmdHook),(BYTE*)UnitCommandHook,5);
}