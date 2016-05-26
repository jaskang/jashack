#pragma once


#define GS_NOTHING 0	//主页
#define GS_LOBBY 1		//大厅
#define GS_LOADING 3	//loading
#define GS_INGAME 4		//游戏中
#define GS_PAUSEDGAME 6	//暂停

extern DWORD NowGamestate, OldGamestate;

bool ChangeLoadingBarText(char* newtext);
void GameStateInit();
