#pragma once

#define At *(UINT*)
#define A2I(a) At (a)
#define LocalPlayer_OFFSET 0xAE54CC
#define Chat_UI_OFFSET 0xACBDD8
#define SLOT_INDEX_START  0xD0028

struct CJassStringData {
	DWORD vtable;
	DWORD refCount;
	DWORD dwUnk1;
	DWORD pUnk2;
	DWORD pUnk3;
	DWORD pUnk4;
	DWORD pUnk5;
	char *data;
};

struct CJassString {
	DWORD vtable;
	DWORD dw0;
	CJassStringData *data;
	DWORD dw1;
};

union DWFP
{
	DWORD dw;
	float fl;
};


struct MmapLoc
{
	DWORD X;
	DWORD Y;
};
struct Location
{
	float X;
	float Y;
	float Z;
};

struct Unit
{
	DWORD dwDummy[3];
	DWORD dwID1;
	DWORD dwID2;
	BYTE _1[0x1C];
	DWORD dwClassId;
	BYTE _2[0x1C];
	DWORD HealthBar;
	DWORD UNK;
	DWORD dwOwnerSlot;
};


union Float
{
	float fl;
	DWORD dw;
};

typedef DWORD HPLAYER;
typedef DWORD HPLAYERSTATE;
typedef DWORD HUNIT;
typedef DWORD HUNITSTATE;
typedef DWORD HUNITTYPE;
typedef DWORD HITEM;
typedef DWORD HTEXTTAG;
typedef DWORD HBUTTON;



extern DWORD addrLocalPlayerOffset;


typedef HPLAYER 	(__cdecl *pGetLocalPlayer)					();
extern pGetLocalPlayer	GetLocalPlayer;
typedef HPLAYER 	(__cdecl *pPlayer)							(int Index);
extern pPlayer	Player;
typedef int 	(__cdecl *pGetPlayerId)							(HPLAYER hPlayer);
extern pGetPlayerId	GetPlayerId;
typedef bool 	(__cdecl *pIsPlayerAlly)						(HPLAYER hPlayer1, HPLAYER hPlayer2);
extern pIsPlayerAlly	IsPlayerAlly;
typedef bool 	(__cdecl *pIsPlayerEnemy)						(HPLAYER hPlayer1, HPLAYER hPlayer2);
extern pIsPlayerEnemy	IsPlayerEnemy;
typedef int 	(__cdecl *pGetPlayerState)						(HPLAYER hPlayer, HPLAYERSTATE hPlayerState);
extern pGetPlayerState	GetPlayerState;
typedef HPLAYER 	(__cdecl *pGetOwningPlayer)					(HUNIT hUnit);
extern pGetOwningPlayer	GetOwningPlayer;

// GetTriggerUnit
typedef HUNIT (__cdecl *pGetTriggerUnit)(void);
extern pGetTriggerUnit	GetTriggerUnit;
typedef bool 	(__cdecl *pIsUnitVisible)						(HUNIT hUnit, HPLAYER hPlayer);
extern pIsUnitVisible	IsUnitVisible;
typedef bool	(__cdecl *pIsUnitOwnedByPlayer)				(HUNIT hUnit, HPLAYER hPlayer);
extern pIsUnitOwnedByPlayer	IsUnitOwnedByPlayer;
typedef bool 	(__cdecl *pIsUnitIllusion)						(HUNIT hUnit);
extern pIsUnitIllusion	IsUnitIllusion;
typedef void 	(__cdecl *pSelectUnit)							(HUNIT hUnit, bool flag);
extern pSelectUnit	SelectUnit;
typedef void 	(__cdecl *pClearSelection)						();
extern pClearSelection	ClearSelection;
typedef bool 	(__cdecl *pIsUnitAlly)							(HUNIT hUnit, HPLAYER hPlayer);
extern pIsUnitAlly	IsUnitAlly;
typedef bool 	(__cdecl *pIsUnitEnemy)							(HUNIT hUnit, HPLAYER hPlayer);
extern pIsUnitEnemy	IsUnitEnemy;
typedef int 	(__cdecl *pGetHeroLevel)						(HUNIT hUnit);
extern pGetHeroLevel	GetHeroLevel;
typedef Float 	(__cdecl *pGetUnitX)							(HUNIT hUnit);
extern pGetUnitX	GetUnitX;
typedef Float	(__cdecl *pGetUnitY)							(HUNIT hUnit);
extern pGetUnitY	GetUnitY;
typedef Float	(__cdecl *pGetUnitFacing)							(HUNIT hUnit);
extern pGetUnitFacing	GetUnitFacing;
typedef Float 	(__cdecl *pGetUnitState)						(HUNIT hUnit, HUNITSTATE hUnitState);
extern pGetUnitState	GetUnitState;
typedef int 	(__cdecl *pGetUnitTypeId)						(HUNIT hUnit);
extern pGetUnitTypeId	GetUnitTypeId;

typedef HITEM 	(__cdecl *pUnitItemInSlot)						(HUNIT hUnit,int slot);
extern pUnitItemInSlot	UnitItemInSlot;
typedef int 	(__cdecl *pGetItemTypeId)						(HITEM hItem);
extern pGetItemTypeId	GetItemTypeId;


typedef void 	(__cdecl *pPingMinimap)							(float* x, float* y, float* duration);
extern pPingMinimap	PingMinimap;
typedef void 	(__cdecl *pPingMinimapEx)						(float* x, float* y, float* duration, int red, int green, int blue, bool extraEffects);
extern pPingMinimapEx	PingMinimapEx;

typedef HTEXTTAG 	(__cdecl *pCreateTextTag)					();
extern pCreateTextTag	CreateTextTag;
typedef void	(__cdecl *pSetTextTagText)						(HTEXTTAG hTextTag, CJassString* Text, float *height);
extern pSetTextTagText	SetTextTagText;
typedef void	(__cdecl *pSetTextTagPosUnit)					(HTEXTTAG hTextTag, int hUnit, float *heightOffset);
extern pSetTextTagPosUnit	SetTextTagPosUnit;
typedef void	(__cdecl *pSetTextTagColor)						(HTEXTTAG hTextTag, int red, int green, int blue, int alpha);
extern pSetTextTagColor	SetTextTagColor;
typedef void	(__cdecl *pSetTextTagVelocity)					(HTEXTTAG hTextTag, float *xvel, float *yvel);
extern pSetTextTagVelocity	SetTextTagVelocity;
typedef void	(__cdecl *pSetTextTagFadepoint)					(HTEXTTAG hTextTag, float *fadepoint);
extern pSetTextTagFadepoint	SetTextTagFadepoint;
typedef void	(__cdecl *pSetTextTagLifespan)					(HTEXTTAG hTextTag, float *lifespan);
extern pSetTextTagLifespan	SetTextTagLifespan;
typedef void	(__cdecl *pSetTextTagPermanent)					(HTEXTTAG hTextTag, bool flag);
extern pSetTextTagPermanent	SetTextTagPermanent;
typedef void	(__cdecl *pSetTextTagVisibility)				(HTEXTTAG hTextTag, bool flag);
extern pSetTextTagVisibility	SetTextTagVisibility;


void InitJass(DWORD gamebase);


HPLAYER MyGetLocalPlayer ();
HPLAYER MyPlayer(int Index);
int MyGetPlayerId(HPLAYER hPlayer);
bool MyIsPlayerAlly(HPLAYER hPlayer1, HPLAYER hPlayer2);
bool MyIsPlayerEnemy(HPLAYER hPlayer1, HPLAYER hPlayer2);
int MyGetPlayerState(HPLAYER hPlayer, HPLAYERSTATE hPlayerState);
HPLAYER MyGetOwningPlayer(HUNIT hUnit);
char* MyGetPlayerName(HPLAYER hPlayer);

HUNIT MyGetTriggerUnit();
bool MyIsUnitVisible(HUNIT hUnit, HPLAYER hPlayer);
bool MyIsUnitOwnedByPlayer(HUNIT hUnit, HPLAYER hPlayer);
bool MyIsUnitIllusion(HUNIT hUnit);
bool MyIsUnitHero(HUNIT hUnit);
void MySelectUnit(HUNIT hUnit, bool flag);
void MyClearSelection();
bool MyIsUnitAlly(HUNIT hUnit, HPLAYER hPlayer);
bool MyIsUnitEnemy(HUNIT hUnit, HPLAYER hPlayer);
int MyGetHeroLevel(HUNIT hUnit);
float MyGetUnitX(HUNIT hUnit);
float MyGetUnitY(HUNIT hUnit);
float MyGetUnitFacing(HUNIT hUnit);
Location MyGetUnitFaceLoc(HUNIT hUnit,float dis);
float MyGetUnitState(HUNIT hUnit, HUNITSTATE hUnitState);
int MyGetUnitTypeId(HUNIT hUnit);
char* MyGetUnitName(HUNIT hUnit);
HUNIT MyGetUnitByOffset(DWORD addr);
bool MyIsUnitDead(HUNIT hUnit);

HITEM MyUnitItemInSlot(HUNIT hUnit,int slot);
int MyGetItemTypeId(HITEM hItem);
char* MyGetItemName(HITEM hitem);
bool MyIsItemUseable(HITEM hitem,DWORD i);
bool MyIsSkillUseable(DWORD skill);

void MyPingMinimap(float x, float y, float duration);
void MyPingMinimapEx(float x, float y, float duration, int color, bool extraEffects);

HTEXTTAG MyCreateTextTag();
void MySetTextTagText(HTEXTTAG hTextTag, const char *Text, float height);
void MySetTextTagPosUnit(HTEXTTAG hTextTag, int hUnit, float heightOffset);
void MySetTextTagColor(HTEXTTAG hTextTag, int red, int green, int blue, int alpha);
void MySetTextTagVelocity(HTEXTTAG hTextTag, float xvel, float yvel);
void MySetTextTagFadepoint(HTEXTTAG hTextTag, float fadepoint);
void MySetTextTagLifespan(HTEXTTAG hTextTag, float lifespan);
void MySetTextTagPermanent(HTEXTTAG hTextTag, bool flag);
void MySetTextTagVisibility(HTEXTTAG hTextTag, bool flag);
void MyChangeTexttagText(
	HTEXTTAG htt,
	char* newtext,
	float size,
	DWORD color);



void MyDisplayChatText(const char *text,DWORD dwMsgType,float fLiveTime=10.0);
void MyWriteTextToScreen(const char *text, float fLiveTime=5.0);


DWORD JGetSelectedUnitsCount();
DWORD JGetUnitArray(DWORD& Sz);


float MyGetDistance(float x1, float y1, float x2, float y2);
bool MyIsCanHurtMe(float area, float x, float y);

bool MyUseItem(HUNIT myUnit,DWORD itemTypeId);
bool MyUseItemTarget(HUNIT myUnit,DWORD itemTypeId,HUNIT target);
bool MyUseItemLoc(HUNIT myUnit,DWORD itemTypeId,float x,float y);

void MyUseSkill(DWORD myhUnit,DWORD cmdId);
void MyUseSkillLoc(DWORD myhUnit,DWORD cmdId, float X, float Y);
void MyUseSkillTarget(DWORD myhUnit,DWORD cmdId,DWORD target);






