#include "stdafx.h"
#include "DamageNotifier.h"

DWORD addrDamageNotifierFuncCall;

float height       = 0.03f,
	heightOffset = 0.0f,
	xvel         = 0.0f,
	yvel         = 0.1f,
	fadepoint    = 0.1f,
	lifespan     = 0.95f;

float fDamageValue;
DWORD dwReturnAddress;
char  szDamageValue[16];
DWORD hTextTag;

void __declspec(naked) DamageNotifierFunc()
{
	__asm
	{
		MOV fDamageValue, EAX
			MOV EAX, [ESP+4]
		MOV dwReturnAddress, EAX
	}

	if ((dwReturnAddress < GameBase) || (dwReturnAddress > (GameBase + 0x0086C000)))
		goto RETN;

	if (fDamageValue < 1.0f)
		goto RETN;

	/*if (!MyIsUnitOwnedByPlayer(MyGetTriggerUnit(), MyGetLocalPlayer()))
	goto RETN;*/

	if (!MyIsUnitHero(MyGetTriggerUnit()))
		goto RETN;
	
	sprintf_s(szDamageValue, "%d", (int)fDamageValue);

	hTextTag = MyCreateTextTag();
	MySetTextTagText(hTextTag, szDamageValue, height);
	MySetTextTagPosUnit(hTextTag, MyGetTriggerUnit(), heightOffset);
	MySetTextTagColor(hTextTag, 255, 0, 0, 255);
	MySetTextTagVelocity(hTextTag, xvel, yvel);
	MySetTextTagFadepoint(hTextTag, fadepoint);
	MySetTextTagLifespan(hTextTag, lifespan);
	MySetTextTagPermanent(hTextTag, false);
	MySetTextTagVisibility(hTextTag, true);

RETN:
	__asm
	{
		MOV EAX, fDamageValue
			JMP dwReturnAddress
	}
}
void DamageNotifierON()
{
	addrDamageNotifierFuncCall=GameBase+ 0x3C46D8;
	PatchCALL((BYTE *)addrDamageNotifierFuncCall, (BYTE *)DamageNotifierFunc, 5);
}