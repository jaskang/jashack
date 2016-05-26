#include "stdafx.h"
#include "Jass.h"


DWORD addrLocalPlayerOffset;


DWORD addrGetPlayerName1;
DWORD addrGetPlayerName2;


DWORD addrChatUIOffset;
DWORD addrDisplayChatText;
DWORD addrWriteTextUI;
DWORD addrWriteTextToScreen;
DWORD addrChatUI;
DWORD addrDisplayRoomText;
DWORD addrClearGameText;
DWORD addrMakeStringFunc;

DWORD addrGetUnitHandle1;
DWORD addrGetUnitHandle2;
DWORD addrUnitName1;
DWORD addrUnitName2;

DWORD addrGetUnitArrayPtr;
DWORD addrGlobalClass;


DWORD addrGetItemName1;
DWORD addrGetItemName2;

DWORD addrGetItemState; 
DWORD addrGetStatePtr; 
DWORD addrGetStateEcx; 

DWORD addrGetWidgetPtr; 
DWORD addrGetItemPtr;

DWORD addrUseItemNoLoc; 
DWORD addrUseItemLoc; 

DWORD addrSendActionNoNaked; 
DWORD addrSendActionNaked; 

DWORD W3XGlobalClass;


pGetLocalPlayer				GetLocalPlayer;
pPlayer						Player;
pGetPlayerId				GetPlayerId;
pIsPlayerAlly				IsPlayerAlly;
pIsPlayerEnemy				IsPlayerEnemy;
pGetPlayerState				GetPlayerState;
pGetOwningPlayer			GetOwningPlayer;

pGetTriggerUnit				GetTriggerUnit;
pIsUnitVisible				IsUnitVisible;
pIsUnitOwnedByPlayer		IsUnitOwnedByPlayer;
pIsUnitIllusion				IsUnitIllusion;
pSelectUnit					SelectUnit;
pClearSelection				ClearSelection;
pIsUnitAlly					IsUnitAlly;
pIsUnitEnemy				IsUnitEnemy;
pGetHeroLevel				GetHeroLevel;
pGetUnitX					GetUnitX;
pGetUnitY					GetUnitY;
pGetUnitFacing				GetUnitFacing;

pGetUnitState				GetUnitState;
pGetUnitTypeId				GetUnitTypeId;

pUnitItemInSlot				UnitItemInSlot;
pGetItemTypeId				GetItemTypeId;

pPingMinimap				PingMinimap;
pPingMinimapEx				PingMinimapEx;

pCreateTextTag				CreateTextTag;
pSetTextTagText				SetTextTagText;
pSetTextTagPosUnit			SetTextTagPosUnit;
pSetTextTagColor			SetTextTagColor;
pSetTextTagVelocity			SetTextTagVelocity;
pSetTextTagFadepoint		SetTextTagFadepoint;
pSetTextTagLifespan			SetTextTagLifespan;
pSetTextTagPermanent		SetTextTagPermanent;
pSetTextTagVisibility		SetTextTagVisibility;
DWORD addrTexttagText;
DWORD addrTexttagColor;

void InitJass(DWORD gamebase)
{
	addrLocalPlayerOffset=GameBase+0xACD44C;


	addrGetPlayerName1=GameBase +0x3BDF50;
	addrGetPlayerName2=GameBase +0x40BB60;


	addrDisplayChatText=GameBase + 0x2FBF00;
	addrWriteTextUI=GameBase + 0xAE54CC;
	addrWriteTextToScreen=GameBase + 0x6050A0;
	//addrChatUI=*(DWORD*)((*(DWORD*)(*(DWORD*)(GameBase + 0xAE3A9C) + 0x184))+0x1FC);
	addrDisplayRoomText = GameBase + 0x61DD30;
	addrClearGameText=GameBase + 0x3B58E0;
	addrMakeStringFunc = GameBase + 0x012040;

	addrGetUnitHandle1 = GameBase + 0x3A8AE0;
	addrGetUnitHandle2 = GameBase + 0x4317F0;
	addrUnitName1 = GameBase + 0x3BE730;
	addrUnitName2 = GameBase + 0x32E660;


	addrGetUnitArrayPtr = GameBase + 0x39C160;
	addrGlobalClass = GameBase + 0xACBDD8;

	addrGetItemName1=GameBase+0x3BF5D0;
	addrGetItemName2=GameBase+0x32E660;

	addrGetItemState = GameBase + 0x4216B0;
	addrGetStatePtr = GameBase + 0xACD44C;
	addrGetStateEcx = GameBase + 0x3A20D0;

	addrGetWidgetPtr = GameBase + 0x3BF030;
	addrGetItemPtr = GameBase + 0x3BF5D0;

	addrUseItemNoLoc = GameBase + 0x33A6E0;
	addrUseItemLoc = GameBase + 0x33A740;

	addrSendActionNoNaked = GameBase + 0x33A7D0;
	addrSendActionNaked = GameBase + 0x33A850;

	W3XGlobalClass=GameBase+ 0xACBDD8;

	GetLocalPlayer 				= (pGetLocalPlayer)					(GameBase + 0x3BC5E0);
	Player						= (pPlayer)							(GameBase + 0x3BC5B0);
	GetPlayerId					= (pGetPlayerId)					(GameBase + 0x3CA0C0);
	IsPlayerAlly				= (pIsPlayerAlly)					(GameBase + 0x3C9FB0);
	IsPlayerEnemy				= (pIsPlayerEnemy)					(GameBase + 0x3CA000);
	GetPlayerState				= (pGetPlayerState)					(GameBase + 0x3CA580);
	GetOwningPlayer				= (pGetOwningPlayer)				(GameBase + 0x3C8C10);

	GetTriggerUnit 				= (pGetTriggerUnit)					(GameBase + 0x3BBCC0);
	IsUnitVisible 				= (pIsUnitVisible)					(GameBase + 0x3C8570);
	IsUnitOwnedByPlayer			= (pIsUnitOwnedByPlayer)			(GameBase + 0x3C84B0);
	IsUnitIllusion				= (pIsUnitIllusion)					(GameBase + 0x3C85D0);
	SelectUnit 					= (pSelectUnit)						(GameBase + 0x3C8390);
	ClearSelection 				= (pClearSelection)					(GameBase + 0x3BC520);
	IsUnitAlly					= (pIsUnitAlly)						(GameBase + 0x3C84F0);
	IsUnitEnemy					= (pIsUnitEnemy)					(GameBase + 0x3C8550);
	GetHeroLevel				= (pGetHeroLevel)					(GameBase + 0x3C7950);
	GetUnitX					= (pGetUnitX)						(GameBase + 0x3C5F90);
	GetUnitY					= (pGetUnitY)						(GameBase + 0x3C5FD0);
	GetUnitFacing				= (pGetUnitFacing)					(GameBase + 0x3C6210);
	GetUnitState				= (pGetUnitState)					(GameBase + 0x3C5E80);
	GetUnitTypeId				= (pGetUnitTypeId)					(GameBase + 0x3C6390);

	UnitItemInSlot				= (pUnitItemInSlot)					(GameBase + 0x3C81B0);
	GetItemTypeId				= (pGetItemTypeId)					(GameBase + 0x3C56E0);

	PingMinimap					= (pPingMinimap)					(GameBase + 0x3B50D0);
	PingMinimapEx				= (pPingMinimapEx)					(GameBase + 0x3B90E0);

	CreateTextTag				= (pCreateTextTag)					(GameBase + 0x3BD000);
	SetTextTagText				= (pSetTextTagText)					(GameBase + 0x3BD050);
	SetTextTagPosUnit			= (pSetTextTagPosUnit)				(GameBase + 0x3CC310);
	SetTextTagColor				= (pSetTextTagColor)				(GameBase + 0x3BD120);
	SetTextTagVelocity			= (pSetTextTagVelocity)				(GameBase + 0x3BD180);
	SetTextTagFadepoint			= (pSetTextTagFadepoint)			(GameBase + 0x3BD2D0);
	SetTextTagLifespan			= (pSetTextTagLifespan)				(GameBase + 0x3BD2A0);
	SetTextTagPermanent			= (pSetTextTagPermanent)			(GameBase + 0x3BD240);
	SetTextTagVisibility		= (pSetTextTagVisibility)			(GameBase + 0x3BD1E0);
	addrTexttagText				= GameBase +0x3BD050;
	addrTexttagColor			= GameBase +0x3BD120;
}

UINT __cdecl MakeString(char *pszStr)
{
	static DWORD _datas[3];
	static DWORD *pjstr = &_datas[0];
	UINT jstr;
	__asm
	{
		mov eax, addrMakeStringFunc;
		mov ecx, pjstr;
		push pszStr;
		call eax;
		mov jstr, eax;
		pop eax;
	}
	return jstr;
}
static void GetJassString(char *szString, CJassString *String)
{
	__asm
	{
		PUSH szString;
		MOV ECX, String;
		CALL addrMakeStringFunc;
	}
}

HPLAYER MyGetLocalPlayer ()
{
	return GetLocalPlayer();
}
HPLAYER MyPlayer(int Index)
{
	return Player(Index);
}
int MyGetPlayerId(HPLAYER hPlayer)
{
	return GetPlayerId(hPlayer);
}
bool MyIsPlayerAlly(HPLAYER hPlayer1, HPLAYER hPlayer2)
{
	return IsPlayerAlly(hPlayer1, hPlayer1);
}
bool MyIsPlayerEnemy(HPLAYER hPlayer1, HPLAYER hPlayer2)
{
	return IsPlayerEnemy(hPlayer1, hPlayer1);
}
int MyGetPlayerState(HPLAYER hPlayer, HPLAYERSTATE hPlayerState)
{
	return GetPlayerState(hPlayer, hPlayerState);
}
HPLAYER MyGetOwningPlayer(HUNIT hUnit)
{
	return GetOwningPlayer(hUnit);
}
char* MyGetPlayerName(HPLAYER hPlayer)
{
	char* retaddr = "a Player";

	__asm
	{
		mov ecx, hPlayer;
		call addrGetPlayerName1;
		test eax, eax;
		jz NOPLAYER;
		push 1;
		mov ecx, eax;
		call addrGetPlayerName2;
NOPLAYER:
		mov retaddr, eax;
	}

	return retaddr;
}



HUNIT MyGetTriggerUnit()
{
	return GetTriggerUnit();
}
bool MyIsUnitVisible(HUNIT hUnit, HPLAYER hPlayer)
{
	return IsUnitVisible(hUnit, hPlayer);
}
bool MyIsUnitOwnedByPlayer(HUNIT hUnit, HPLAYER hPlayer)
{
	return IsUnitOwnedByPlayer(hUnit, hPlayer);
}
bool MyIsUnitIllusion(HUNIT hUnit)
{
	return IsUnitIllusion(hUnit);
}
bool MyIsUnitHero(HUNIT hUnit)
{
	if (GetHeroLevel(hUnit)<=0)
	{
		return false;
	} 
	else
	{
		return true;
	}
}
void MySelectUnit(HUNIT hUnit, bool flag)
{
	SelectUnit(hUnit, flag);
}
void MyClearSelection()
{
	ClearSelection();
}
bool MyIsUnitAlly(HUNIT hUnit, HPLAYER hPlayer)
{
	return IsUnitAlly(hUnit, hPlayer);
}
bool MyIsUnitEnemy(HUNIT hUnit, HPLAYER hPlayer)
{
	return IsUnitEnemy(hUnit, hPlayer);
}
int MyGetHeroLevel(HUNIT hUnit)
{
	return GetHeroLevel(hUnit);
}
float MyGetUnitX(HUNIT hUnit)
{
	return GetUnitX(hUnit).fl;
}
float MyGetUnitY(HUNIT hUnit)
{
	return GetUnitY(hUnit).fl;
}
float MyGetUnitFacing(HUNIT hUnit)
{
	return GetUnitFacing(hUnit).fl;
}
Location MyGetUnitFaceLoc(HUNIT hUnit,float dis)
{
	float unitFacing = (float)deg2rad(MyGetUnitFacing(hUnit));
	Location ret;
	ret.X = MyGetUnitX(hUnit) + cos(unitFacing)*dis;
	ret.Y = MyGetUnitY(hUnit) + sin(unitFacing)*dis;
	return ret;
}
float MyGetUnitState(HUNIT hUnit, HUNITSTATE hUnitState)
{
	return GetUnitState(hUnit, hUnitState).fl;
}
int MyGetUnitTypeId(HUNIT hUnit)
{
	return GetUnitTypeId(hUnit);
}
char* MyGetUnitName(HUNIT hUnit)
{
	char* retaddr = "Null";
	if (hUnit==NULL)
	{
		return retaddr;
	}
	__asm
	{
		mov ecx, hUnit;
		call addrUnitName1;
		test eax, eax;
		je NoUnit;

		mov ecx, [eax + 0x30];
		xor edx, edx;
		call addrUnitName2;
		mov retaddr, eax;
NoUnit:
	}
	return retaddr;
}

//************************************
// 函数名称: MyGetUnitByOffset
// 作 成 者：JasKang
// 作成日期：2015/02/14
// 返 回 值: DWORD
// 参    数: DWORD Addr
//************************************
HUNIT MyGetUnitByOffset(DWORD addr)
{
	DWORD hand;
	_asm
	{
		pushad
			mov esi, addr
			mov ecx, addrLocalPlayerOffset
			mov ecx, [ecx]
		call addrGetUnitHandle1
			push 0
			push esi
			mov ecx, eax
			call addrGetUnitHandle2
			mov hand, eax
			popad
	}
	return hand;
}
bool MyIsUnitDead(HUNIT hUnit)
{
	return MyGetUnitState(hUnit, 0) <= 0;
}



HITEM MyUnitItemInSlot(HUNIT hUnit,int slot)
{
	return UnitItemInSlot(hUnit,slot);
}
int MyGetItemTypeId(HITEM hItem)
{
	return GetItemTypeId(hItem);
}
char* MyGetItemName(HITEM hitem)
{
	char* retaddr = "a Item";
	__asm
	{
		mov ecx, hitem;
		call addrGetItemName1;
		test eax, eax;
		je NoItem;

		mov ecx, [eax + 0x30];
		xor edx, edx;
		call addrGetItemName2;
		mov retaddr, eax;
NoItem:
	}
	return retaddr;
}


//获取Item的指针
DWORD __stdcall GetItemPtr(HITEM hitem)
{
	DWORD re = 0;
	__asm
	{
		MOV   ECX,  hitem
			MOV   EAX,  addrGetItemPtr
			CALL  EAX
			MOV   re, EAX
	}
	return re;
}
//1,0xD2(CD)	//in cool down
//2,0x00(可使用)	//can use
//3,0xD1(没魔)	// no mana
//4,0xB8(不存在) //not exist
DWORD __stdcall GetItemState(DWORD slotPos, DWORD opt, DWORD itemPtr)
{
	DWORD re = 0xD2;
	__asm
	{
		PUSH  itemPtr
			PUSH  opt
			PUSH  slotPos

			MOV   ECX,  addrGetStatePtr
			MOV   ECX,  DWORD PTR[ECX]
		MOVZX EAX,  WORD PTR[ECX+0x28]
		PUSH  EAX
			MOV   EAX,  addrGetStateEcx
			CALL  EAX

			MOV   EBX,  DWORD PTR[EAX+0x34]
		MOV   ECX,  EBX
			MOV   EAX,  addrGetItemState
			CALL  EAX
			MOV   re, EAX
	}
	return re;
}
bool MyIsItemUseable(HITEM hitem,DWORD i)//物品可否使用 物品，物品栏位置0-5
{
	if (GetItemState(i+SLOT_INDEX_START, 0, GetItemPtr(hitem))==0)
	{
		return true;
	}
	return false;
}
bool MyIsSkillUseable(DWORD skill)//技能可否使用
{
	if (GetItemState(skill, 1, 0)==0)
	{
		return true;
	}
	return false;
}




void MyPingMinimap(float x, float y, float duration)
{
	PingMinimap(&x, &y, &duration);
}
void MyPingMinimapEx(float x, float y, float duration, int color, bool extraEffects)
{
	int red=( 0xff <<16 & color ) >> 16;
	int green=( 0xff <<8 & color ) >> 8;
	int blue=0xff & color;
	PingMinimapEx(&x, &y, &duration, red, green, blue, extraEffects);
}




HTEXTTAG MyCreateTextTag()
{
	return CreateTextTag();
}
void MySetTextTagText(HTEXTTAG hTextTag, const char *Text, float height)
{
	CJassString JSTest;
	char* NewText = _strdup(Text);
	GetJassString(NewText ,&JSTest);
	SetTextTagText(hTextTag, &JSTest, &height);
}
void MySetTextTagPosUnit(HTEXTTAG hTextTag, int hUnit, float heightOffset)
{
	SetTextTagPosUnit(hTextTag, hUnit, &heightOffset);
}
void MySetTextTagColor(HTEXTTAG hTextTag, int red, int green, int blue, int alpha)
{
	SetTextTagColor(hTextTag, red, green, blue, alpha);
}
void MySetTextTagVelocity(HTEXTTAG hTextTag, float xvel, float yvel)
{
	SetTextTagVelocity(hTextTag, &xvel, &yvel);
}
void MySetTextTagFadepoint(HTEXTTAG hTextTag, float fadepoint)
{
	SetTextTagFadepoint(hTextTag, &fadepoint);
}
void MySetTextTagLifespan(HTEXTTAG hTextTag, float lifespan)
{
	SetTextTagLifespan(hTextTag, &lifespan);
}
void MySetTextTagPermanent(HTEXTTAG hTextTag, bool flag)
{
	SetTextTagPermanent(hTextTag, flag);
}
void MySetTextTagVisibility(HTEXTTAG hTextTag, bool flag)
{
	SetTextTagVisibility(hTextTag, flag);
}

void MyChangeTexttagText(
	HTEXTTAG htt,
	char* newtext,
	float size,
	DWORD color)
{
	static float rsize;
	rsize = size / 1000;
	UINT wcstr = MakeString(newtext);
	__asm
	{
		// 设置漂浮文字对象文本
		mov eax, addrTexttagText;
		lea ebx, rsize;
		push ebx;
		push wcstr;
		push htt;
		call eax;
		add esp,12;

		// 设置漂浮文字颜色
		mov eax, addrTexttagColor;
		lea edx, color;
		xor ebx, ebx;
		xor ecx, ecx;
		mov bl, byte ptr ss:[edx + 0];
		push ebx;
		mov bl, byte ptr ss:[edx + 1];
		push ebx;
		mov bl, byte ptr ss:[edx + 2];
		push ebx;
		mov bl, byte ptr ss:[edx + 3];
		push ebx;
		push htt;
		call eax;
		add esp, 20;
	}
}







//************************************
// 函数名称: JDisplayChatText 显示本地聊天文本
// 作 成 者：JasKang	
// 作成日期：2014/12/25
// 返 回 值: void
// 参    数: const char * text 内容
// 参    数: DWORD dwMsgType 消息类型
// 参    数: float fLiveTime 显示时间
//************************************
void MyDisplayChatText(const char *text,DWORD dwMsgType,float fLiveTime)
{
	DWORD nPlayerID = MyGetPlayerId(MyGetLocalPlayer());
	__asm
	{
		push fLiveTime;
		push dwMsgType;
		push text;
		push nPlayerID;
		mov eax, GameBase;
		mov eax, dword ptr ds:[eax + Chat_UI_OFFSET];
		mov ecx, eax;
		call addrDisplayChatText;
	}
}

//************************************
// 函数名称: JWriteTextToScreen 显示本地文本
// 作 成 者：JasKang
// 作成日期：2014/12/25
// 返 回 值: void
// 参    数: const char * text 内容
// 参    数: float fLiveTime 显示时间
//************************************
void MyWriteTextToScreen(const char *text, float fLiveTime)
{
	DWORD dwColor = 0xFFFFFFFF;
	LPVOID lpColor=&dwColor;
	__asm
	{
		push 0;
		push fLiveTime;
		push lpColor;
		mov eax, text;
		push eax;
		mov edi, addrWriteTextUI;
		mov edi, dword ptr ds:[edi];
		mov ecx, dword ptr ds:[edi+0x3E8]; //edi+0x3EC is the type
		call addrWriteTextToScreen;
	}
}













DWORD JGetSelectedUnitsCount()
{
	UINT32 selectedUnitList;
	UINT16 a2;
	memcpy(&selectedUnitList, (LPVOID)(addrLocalPlayerOffset), 4);
	memcpy(&a2, (LPVOID)(selectedUnitList + 0x28), sizeof(UINT16));

	UINT32 tmpAddress;
	memcpy(&tmpAddress, (LPVOID)(selectedUnitList + 0x58 + 4 * a2), 4);
	memcpy(&tmpAddress, (LPVOID)(tmpAddress + 0x34), 4);

	UINT32 listHead;
	memcpy(&listHead, (LPVOID)(tmpAddress + 0x1F0), 4);

	UINT32 listLength;
	memcpy(&listLength, (LPVOID)(tmpAddress + 0x1F8), 4);
	return listLength;
}


DWORD JGetUnitArray(DWORD& Sz)
{
	__asm
	{
		MOV EAX,DWORD PTR DS:[addrGlobalClass]
		MOV EAX,DWORD PTR DS:[EAX]
		MOV EAX, DWORD PTR DS : [EAX + 0x3BC]
		PUSH 0 // if 0 here it will just return the pointer if 1 it will update the array
		MOV ECX, EAX
		CALL addrGetUnitArrayPtr
		MOV ECX, DWORD PTR DS : [EAX + 4]
		MOV EDX, DWORD PTR DS : [Sz]
		MOV DWORD PTR DS : [EDX], ECX
		MOV EAX, DWORD PTR DS : [EAX + 8]
	}
}








float MyGetDistance(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(x1-x2, 2)+pow(y1-y2, 2)));
}
//AOE
bool MyIsCanHurtMe(float area, float x, float y)
{
	if (LocalHero)
	{
		float myX = MyGetUnitX(LocalHero);
		float myY = MyGetUnitY(LocalHero);
		float distance = MyGetDistance(myX, myY, x, y);
		if (distance<area)
		{
			return true;
		}
	}
	return false;
}



//////////////////////////////////////////////////////////////////////////
//执行基本的控制动作，比如移动(M)，停止(S)等等
//unit move / unit stop etc
void TargetOrderIssue(DWORD myhUnit,DWORD orderId, DWORD item, float x, float y, DWORD widget, DWORD option1, DWORD option2)
{
	__try
	{
		MySelectUnit(myhUnit,true);
		__asm
		{
			PUSH  option2
				PUSH  option1
				MOV  ECX, widget
				MOV  EAX, addrGetWidgetPtr
				CALL EAX
				PUSH EAX 
				MOV  EAX,  y
				PUSH EAX
				MOV  EAX,  x
				PUSH EAX
				MOV  ECX, item
				MOV  EAX,  addrGetItemPtr
				CALL EAX
				PUSH EAX 
				PUSH orderId
				MOV  EAX,  addrSendActionNaked
				CALL EAX
		}
	}
	__except(1)
	{
	}

}
//////////////////////////////////////////////////////////////////////////
//使用物品或技能（该物品或技能不需要选择一个地点使用，比如月女的跳）
//选英雄/加技能/买东西/SH/圣殿/自动释放
//use item/skill( need not to choose a location)
void UseItemWithNoLocation(DWORD myhUnit,DWORD orderId, DWORD item)
{
	__try
	{
		MySelectUnit(myhUnit,true);
		__asm
		{
			PUSH 4
				PUSH 0
				MOV  ECX, item
				MOV   EAX,  addrGetItemPtr
				CALL  EAX
				PUSH EAX
				PUSH orderId
				MOV   EAX,  addrUseItemNoLoc
				CALL  EAX
		}
	}
	__except(1)
	{
	}
}



bool MyUseItem(HUNIT myUnit,DWORD itemTypeId)
{
	for (int i=0; i<6; i++)	//遍历物品栏
	{
		DWORD tmpItem = MyUnitItemInSlot(myUnit, i);
		DWORD tmpTypeId = MyGetItemTypeId(tmpItem);
		if (tmpTypeId==itemTypeId)	//玄武
		{
			if (MyIsItemUseable(tmpItem,i)) 
			{
				UseItemWithNoLocation(myUnit,i+SLOT_INDEX_START,tmpItem);
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}

bool MyUseItemTarget(HUNIT myUnit,DWORD itemTypeId,HUNIT target)
{
	for (int i=0; i<6; i++)	//遍历物品栏
	{
		DWORD tmpItem = MyUnitItemInSlot(myUnit, i);
		DWORD tmpTypeId = MyGetItemTypeId(tmpItem);
		if (tmpTypeId==itemTypeId)	//玄武
		{
			if (MyIsItemUseable(tmpItem,i)) 
			{
				TargetOrderIssue(myUnit,i+SLOT_INDEX_START, tmpItem, MyGetUnitX(target),MyGetUnitY(target), target, 0, 4);
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}
bool MyUseItemLoc(HUNIT myUnit,DWORD itemTypeId,float x,float y)
{
	for (int i=0; i<6; i++)	//遍历物品栏
	{
		DWORD tmpItem = MyUnitItemInSlot(myUnit, i);
		DWORD tmpTypeId = MyGetItemTypeId(tmpItem);
		if (tmpTypeId==itemTypeId)	//玄武
		{
			if (MyIsItemUseable(tmpItem,i)) 
			{
				TargetOrderIssue(myUnit,i+SLOT_INDEX_START, tmpItem, x, y, 0, 0, 4);
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}



void MyUseSkill(DWORD myhUnit,DWORD cmdId)
{
	UseItemWithNoLocation(myhUnit,cmdId, 0);
}
void MyUseSkillLoc(DWORD myhUnit,DWORD cmdId, float X, float Y)
{
	__try
	{
		MySelectUnit(myhUnit,true);
		__asm
		{
			PUSH 0
				PUSH 6
				PUSH 0
				ADDR(W3XGlobalClass,ECX)
				MOV ECX, DWORD PTR DS:[ECX+0x1B4];
			PUSH Y
				PUSH X
				PUSH 0
				PUSH cmdId
				CALL addrSendActionNaked
		}
	}
	__except(1)
	{

	}
}

void MyUseSkillTarget(DWORD myhUnit,DWORD cmdId,DWORD target)
{
	__try
	{
		MySelectUnit(myhUnit,true);
		__asm
		{
			PUSH 0
				PUSH 4
				PUSH target
				PUSH 0
				PUSH cmdId
				ADDR(W3XGlobalClass,ECX)
				MOV ECX, DWORD PTR DS:[ECX+0x1B4];
			CALL addrSendActionNoNaked
		}
	}
	__except(1)
	{

	}
}



