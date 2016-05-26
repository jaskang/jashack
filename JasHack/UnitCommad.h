#pragma once


struct Command
{
	DWORD _6F942254;
	DWORD IDUNCARE[8];
	DWORD CommandId;
	DWORD UNK[8];
	float X;
	DWORD UNK1;
	float Y;
};

enum Cmd
{
	MOVE=0xD0003,	//移动
	ATTACK=0xD000F,	//攻击
	HOLD=0xD0019,	//停止 H
	STOP=0xD0004,	//停止 S
	Action_T=0xD009F, //张飞典韦T
	ITEM1=0xD0028, //物品1
	ITEM2=0xD0029, //物品2
	ITEM3=0xD002A, //物品3
	ITEM4=0xD002B, //物品4
	ITEM5=0xD002C, //物品5
	ITEM6=0xD002D, //物品6
	Action_41_E=0xD024B,	//司马E
	Action_ZG_E=0xD0270,	//ZG E
	Action_ZF_V=0xD0076,	//张飞 天神
	Action_CR_E=0xD0103,	//曹仁 睡
	Action_CR_G=0xD0270,	//曹仁 鬼神
	Action_XUN_W=0xD0218,	//荀彧 蛇形结界
	Action_GJ_C=0xD024B,	//郭嘉 冰河爆裂破
	Action_GY_X=0xD0107,	//关羽 十字斩
	Action_GY_D=0xD0079,	//关羽 D
	Action_GY_B=0xD00A0,	//关羽 B
};

#define HERO_ID_ZG	0x48303038  //诸葛
#define HERO_ID_ZF	0x4F303032	//张飞
#define HERO_ID_GY	0x4F303033	//关于

#define HERO_ID_DW	0x48303036  //典韦
#define HERO_ID_CR	0x55303037  //CR
#define HERO_ID_XUN	0x55303049  //荀彧
#define HERO_ID_GJ	0x55303030  //郭嘉

#define ITEM_XX		0x64657363	//飞鞋
#define ITEM_XW		0x49303243	//玄武
#define ITEM_FX		0x49303150	//风行
#define ITEM_FZ		0x736E6567  //风暴之杖
#define ITEM_YZ		0x7373616E  //羊杖


void UnitCommandON();
