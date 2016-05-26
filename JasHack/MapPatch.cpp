#include "stdafx.h"
#include "MapPatch.h"
#include "VSPatch.h"


void WriteCodeTo(void* addrDest, void* addrNewCode, UINT size)
{
	AllowMemoryOperate(addrDest, size);
	memcpy(addrDest, addrNewCode, size);
}
DWORD AllowMemoryOperate(void* addr, UINT size, BOOL AllowExecute)
{
	DWORD dwOldProtectState;
	VirtualProtect(addr, size, AllowExecute ? PAGE_EXECUTE : PAGE_EXECUTE_READWRITE, &dwOldProtectState);
	return dwOldProtectState;
}

void MH124B_ON()
{
	DWORD oldpro;
	VirtualProtect((LPVOID)(GameBase + 0x01000), 0x87E000, PAGE_EXECUTE_READWRITE, &oldpro);
	////////////////////////////////////////////////////大地图显示单位
	PATCH(0x3A201D, "\xEB");
	////////////////////////////////////////////////////////大地图显示隐形
	PATCH(0x3622D1, "\x3B");
	PATCH(0x3622D4, "\x85");
	PATCH(0x39A45B, "\x90\x90\x90\x90\x90\x90");
	PATCH(0x39A46E, "\x90\x90\x90\x90\x90\x90\x90\x90\x33\xC0\x40");
	/////////////////////////////////////////////////////分辨幻影
	PATCH(0x28351C, "\x40\xC3");
	/////////////////////////////////////////////////////显示神符
	PATCH(0x4076CA, "\x90\x90");
	PATCH(0x3A1F5B, "\xEB");
	/////////////////////////////////////////////////////小地图显示单位
	PATCH(0x361EAB, "\x90\x90\x39\x5E\x10\x90\x90\xB8\x00\x00\x00\x00\xEB\x07");
	///////////////////////////////////////////////////////小地图显示隐形
	PATCH(0x361EBC, "\x00");
	//////////////////////////////////////////////////////敌方信号
	PATCH(0x43F956, "\x3B");
	PATCH(0x43F959, "\x85");
	PATCH(0x43F969, "\x3B");
	PATCH(0x43F96C, "\x85");
	////////////////////////////////////////////////////////他人提示
	PATCH(0x334529, "\x39\xC0\x0F\x85");
	///////////////////////////////////////////////////////敌人头像
	//PATCH(0x371640,"\xE8\x3B\x28\x03\x00\x85\xC0\x0F\x85\x8F\x02\x00\x00\xEB\xC9\x90\x90\x90\x90");
	//////////////////////////////////////////////////////资源面板
	PATCH(0x3604CA, "\x90\x90");
	/*PATCH(0x150981,"\xEB\x02");
	PATCH(0x1509FE,"\xEB\x02");
	PATCH(0x151597,"\xEB\x02");
	PATCH(0x151647,"\xEB\x02");
	PATCH(0x151748,"\xEB\x02");
	PATCH(0x1BED19,"\xEB\x02");
	PATCH(0x314A9E,"\xEB\x02");
	PATCH(0x21EAD4,"\xEB");
	PATCH(0x21EAE8,"\x03");*/
	//顶显资源
	PATCH(0x359A2D, "\xEB\x02");
	PATCH(0x35A11F, "\xEB\x02");
	PATCH(0x35A1DF, "\xEB\x02");
	PATCH(0x35A310, "\xEB\x02");
	PATCH(0x28EA8A, "\xEB\x02");
	//建显资源
	PATCH(0x3604C4, "\xEB");//恢复： 75
	///////////////////////////////////////////////////////允许交易
	PATCH(0x34E822, "\xB8\xE0\x03\x00");
	PATCH(0x34E827, "\x90");
	PATCH(0x34E82A, "\xB8\x32\x00\x00");
	PATCH(0x34E82F, "\x90");
	//////////////////////////////////////////////////////查看技能
	PATCH(0x20318C, "\x90\x90\x90\x90\x90\x90");
	PATCH(0x34FD28, "\x90\x90");
	PATCH(0x28EC8E, "\xEB");
	PATCH(0x34FD69, "\x00");
	////////////////////////////////////////////////////////视野外点击
	PATCH(0x285C4C, "\x90\x90");
	PATCH(0x285C62, "\xEB");
	/////////////////////////////////////////////////////////////无限取消
	PATCH(0x57B9FC, "\xEB");
	PATCH(0x5B2CC7, "\x03");
	PATCH(0x5B2CDB, "\x03");
	////////////////////////////////////////////////////////过-MH
	//PATCH(0x3C8407,"\xEB\x11");
	//PATCH(0x3C8427,"\xEB\x11");
	//PATCH(0x3B51C0,"\xC3\x90");
	//////////////////////////////////////////////////////////反-AH
	//PATCH(0x3C6E1C,"\xB8\xFF\x00\x00\x00\xEB");
	//PATCH(0x3CC2F2,"\xEB");
	///////////////////////////////////////////////////////////////////
	VirtualProtect((LPVOID)(GameBase + 0x01000), 0x87E000, oldpro, &oldpro);

}


void MH124E_ON()
{

	DWORD oldpro;
	VirtualProtect((LPVOID)(GameBase + 0x01000), 0x87E000, PAGE_EXECUTE_READWRITE, &oldpro);
	////////////////////////////大地图显示单位
	PATCH(0x39EBBC, "\x75");
	PATCH(0x3A2030, "\x90\x90");
	PATCH(0x3A20DB, "\x90\x90");
	//s大地图显示隐形
	PATCH(0x28357C, "\x40\xC3");
	PATCH(0x39A51B, "\x90\x90\x90\x90\x90\x90");
	PATCH(0x39A52E, "\x90\x90\x90\x90\x90\x90\x90\x90\x33\xC0\x40");
	PATCH(0x3A201B, "\xEB");
	//大地图显示幻象
	PATCH(0x28357C, "\x40");
	PATCH(0x28357D, "\xC3");
	//大地图显示神符
	PATCH(0x3A201B, "\xEB");
	PATCH(0x40A864, "\x90");
	PATCH(0x40A865, "\x90");
	//小地图  显示单位 
	PATCH(0x361F82, "\x33\xC0");
	/////////////////////////////////////////////小地图显示隐形

	/////////////////////////////////////////////敌方信号
	PATCH(0x43F9A6, "\x3B");
	PATCH(0x43F9A9, "\x85");
	PATCH(0x43F9B9, "\x3B");
	PATCH(0x43F9BC, "\x85");
	/////////////////////////////////////////////他人提示
	PATCH(0x3345E9, "\x39\xC0\x0F\x85");
	//敌人英雄图标
	// PATCH(0x371700,"\xE8\x3B\x28\x03\x00\x85\xC0\x0F\x85\x8F\x02\x00\x00\xEB\xC9\x90\x90\x90\x90");
	//显示资源
	PATCH(0x36058A, "\x90");
	PATCH(0x36058B, "\x90");
	//顶显资源
	PATCH(0x359AED, "\xEB\x02");
	PATCH(0x35A1DF, "\xEB\x02");
	PATCH(0x35A29F, "\xEB\x02");
	PATCH(0x35A3D0, "\xEB\x02");
	PATCH(0x28EAFA, "\xEB\x02");
	//建显资源
	PATCH(0x360584, "\xEB");//恢复： 75
	//允许交易
	PATCH(0x34E8E2, "\xB8");
	PATCH(0x34E8E3, "\xC8");
	PATCH(0x34E8E4, "\x00");
	PATCH(0x34E8E5, "\x00");
	PATCH(0x34E8E7, "\x90");
	PATCH(0x34E8EA, "\xB8");
	PATCH(0x34E8EB, "\x32");
	PATCH(0x34E8EC, "\x00");
	PATCH(0x34E8ED, "\x00");
	PATCH(0x34E8EE, "\x00");
	PATCH(0x34E8EF, "\x90");
	//技能
	PATCH(0x2031EC, "\x90\x90\x90\x90\x90\x90");
	PATCH(0x34FDE8, "\x90\x90");
	//CD
	PATCH(0x28ECFE, "\xEB");
	PATCH(0x34FE29, "\x00");
	//野外点击
	PATCH(0x285CBC, "\x90");
	PATCH(0x285CBD, "\x90");
	PATCH(0x285CD2, "\xEB");
	//////////////////////////////////////////////////无限取消
	PATCH(0x57BA7C, "\xEB");
	PATCH(0x5B2D77, "\x03");
	PATCH(0x5B2D8B, "\x03");
	/////////////////////////////////////////////////////过信长
	//
	//PATCH(0x3b5280,"\xC3\x90");
	//PATCH(0x3c84c7,"\xEB\x11");
	//PATCH(0x3c84E7,"\xEB\x11");
	//PATCH(0x3b43c0,"\xC3\x90");
	//	
	/////////////////////////////////////////////////////过-MH
	//
	//	PATCH(0x3C84C7,"\xEB\x11");
	//	PATCH(0x3C84E7,"\xEB\x11");
	//	PATCH(0x3B5280,"\xC3\x90");
	//			
	//////////////////////////////////////////////////////反-AH
	//
	//	PATCH(0x3C6EDC,"\xB8\xFF\x00\x00\x00\xEB");
	//	PATCH(0x3CC3B2,"\xEB");
	//
	VirtualProtect((LPVOID)(GameBase + 0x01000), 0x87E000, oldpro, &oldpro);

}
void MH124B_OFF()
{

	DWORD oldpro;
	VirtualProtect((LPVOID)(GameBase + 0x01000), 0x87E000, PAGE_EXECUTE_READWRITE, &oldpro);
	PATCH(0x00F556, "\x74\x09");
	PATCH(0x20318C, "\x0F\x84\x5F\x01\x00\x00");
	PATCH(0x28351C, "\xC3\xCC");
	PATCH(0x285C4C, "\x74\x2A");
	PATCH(0x285C62, "\x75");
	PATCH(0x28EC8E, "\x75");
	PATCH(0x334529, "\x85");
	PATCH(0x33452C, "\x84");
	PATCH(0x339B94, "\x57\x8D\x4C\x24\x18");
	PATCH(0x339D34, "\x57\x8D");
	PATCH(0x339D37, "\x24\x18");
	PATCH(0x34E822, "\x8B\x87\x6C\x01");
	PATCH(0x34E827, "\x00");
	PATCH(0x34E82A, "\x8B\x87\x68\x01");
	PATCH(0x34E82F, "\x00");
	PATCH(0x34FD28, "\x74\x08");
	PATCH(0x34FD66, "\x85\xC0\x74\x08");
	PATCH(0x356FA5, "\x88\x01");
	PATCH(0x3604CA, "\xEB\x08");
	PATCH(0x361EAB, "\x75\x0C");
	PATCH(0x361EB0, "\x75\x07\xB9\x01");
	PATCH(0x361EB8, "\x02");
	PATCH(0x361EBC, "\x01");
	PATCH(0x3622D1, "\x85");
	PATCH(0x3622D4, "\x84");
	PATCH(0x371641, "\xFB\x29");
	PATCH(0x371648, "\x84");
	PATCH(0x37164D, "\x8B\x85\x80\x01\x00\x00");
	PATCH(0x37A564, "\x2A\x17\x37\x00");
	PATCH(0x39A45B, "\x8B\x97\x98\x01\x00\x00");
	PATCH(0x39A46E, "\x0F\xB7\x00\x55\x50\x56\xE8\xF7\x7B\x00\x00");
	PATCH(0x37A969, "\xA3\xD5\xF4\xFF");
	PATCH(0x3A1F5B, "\x75");
	PATCH(0x3A201D, "\x75");
	PATCH(0x3B51C0, "\x33\xD2");
	PATCH(0x3C6E1C, "\x3D");
	PATCH(0x3C6E21, "\x76");
	PATCH(0x3C8407, "\x6A\x00");
	PATCH(0x3C8427, "\x6A\x00");
	PATCH(0x3CC2F2, "\x74");
	PATCH(0x4076CA, "\x75\x0A");
	PATCH(0x43F956, "\x85");
	PATCH(0x43F959, "\x84");
	PATCH(0x43F969, "\x85");
	PATCH(0x43F96C, "\x84");
	PATCH(0x57B9FC, "\x7A");
	PATCH(0x5B2CC7, "\x00");
	PATCH(0x5B2CDB, "\x01");
	PATCH(0x74D103, "\x88\x14");
	PATCH(0x74D106, "\x83\xC6\x01");
	PATCH(0x87E9A3, "\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC");
	PATCH(0x87E9B0, "\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xC3\xCC\xCC\xCC\xCC");
	PATCH(0xAB7E6D, "\xFF\x80");

	VirtualProtect((LPVOID)(GameBase + 0x01000), 0x87E000, oldpro, &oldpro);


}
void MH124E_OFF()
{

	DWORD oldpro;

	VirtualProtect((LPVOID)(GameBase + 0x01000), 0x87E000, PAGE_EXECUTE_READWRITE, &oldpro);

	PATCH(0x2031EC, "\x0F\x84\x5F\x01\x00\x00");
	PATCH(0x28357C, "\xC3\xCC");
	PATCH(0x285CBC, "\x74\x2A");
	PATCH(0x285CD2, "\x75");
	PATCH(0x28ECFE, "\x75");
	PATCH(0x3345E9, "\x85");
	PATCH(0x3345EC, "\x84");
	PATCH(0x339C54, "\x57\x8D\x4C\x24\x18");
	PATCH(0x339DF4, "\x57\x8D");
	PATCH(0x339DF7, "\x24\x18");
	PATCH(0x34E8E2, "\x8B\x87\x6C\x01");
	PATCH(0x34E8E7, "\x00");
	PATCH(0x34E8EA, "\x8B\x87\x68\x01");
	PATCH(0x34E8EF, "\x00");
	PATCH(0x34FDE8, "\x74\x08");
	PATCH(0x34FE26, "\x85\xC0\x74\x08");
	PATCH(0x356FFE, "\x66\x85\xC0");
	PATCH(0x357065, "\x88\x01");
	PATCH(0x36058A, "\xEB\x08");
	//PATCH(0x361F7C,"\x01"); //
	PATCH(0x361F82, "\x3B\xC3");
	PATCH(0x362391, "\x85");
	PATCH(0x362394, "\x84");
	PATCH(0x371701, "\xFB\x29");
	PATCH(0x371708, "\x84");
	PATCH(0x37170D, "\x8B\x85\x80\x01\x00\x00");
	PATCH(0x39A51B, "\x8B\x97\x98\x01\x00\x00");
	PATCH(0x39A52E, "\x0F\xB7\x00\x55\x50\x56\xE8\xF7\x7B\x00\x00");
	PATCH(0x39EBBC, "\x74");
	PATCH(0x3A201B, "\x75");
	PATCH(0x3A201D, "\x39\x97\xC0\x03\x00\x00");
	PATCH(0x3A20ED, "\xE8\xEE\xD3\xC6\xFF\x8B\xD0\xC1\xEA\x02\x83\xE2\x01");
	PATCH(0x3A2030, "\xEB\x09");
	PATCH(0x3A20DB, "\x23\xCA");//
	PATCH(0x3B5280, "\x33\xD2");
	PATCH(0x3C6EDC, "\x3D");
	PATCH(0x3C6EE1, "\x76");
	PATCH(0x3C84C7, "\x6A\x00");
	PATCH(0x3C84E7, "\x6A\x00");
	PATCH(0x3CC3B2, "\x74");
	PATCH(0x40A864, "\x75\x0A");
	PATCH(0x43F9A6, "\x85");
	PATCH(0x43F9A9, "\x84");
	PATCH(0x43F9B9, "\x85");
	PATCH(0x43F9BC, "\x84");
	PATCH(0x57BA7C, "\x7A");
	PATCH(0x5B2D77, "\x00");
	PATCH(0x5B2D8B, "\x01");
	PATCH(0x74D1B9, "\x8A\x90");
	DWORD tmp = 0xAB7E6C + GameBase;
	memcpy(LPVOID(GameBase + 0x74D1BB), &tmp, 4);
	PATCH(0x87EA63, "\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC");
	PATCH(0x87EA70, "\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xC3\xCC\xCC\xCC\xCC");

	PATCH(0xAB7E6D, "\xFF\x80");
	VirtualProtect((LPVOID)(GameBase + 0x01000), 0x87E000, oldpro, &oldpro);
}






void HackOn()
{
	MH124B_ON();
	//MH124E_ON();
}
void HackOff()
{
	MH124B_OFF();
	//MH124E_OFF();
}

void InitSafeMap()
{
	
	NewGameBase=(DWORD)VirtualAlloc(0,0x00BD4000,MEM_COMMIT,PAGE_EXECUTE_READWRITE);
	memcpy((LPVOID)NewGameBase,(LPVOID)GameBase,0x00BD4000);

	VSPatch();
	HackOn();
}
