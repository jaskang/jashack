#include "stdafx.h"
#include "func.h"


//************************************
// 函数名称: FChat 发送聊天文本 
// 作 成 者：JasKang
// 作成日期：2014/12/25
// 返 回 值: void 
// 参    数: const char * text 聊天内容
// 参    数: bool isall 是否对所有人发送
//************************************
void FChat(const char* text,bool isall)
{
	SetClipBoardText(text);
	if (isall)
	{
		SendMessage(wHandle,WM_KEYDOWN,VK_SHIFT,0);
		SendMessage(wHandle,WM_KEYDOWN,VK_RETURN,0);
		SendMessage(wHandle,WM_KEYUP,VK_RETURN,0);
		SendMessage(wHandle,WM_KEYUP,VK_SHIFT,0);
		SendMessage(wHandle,WM_KEYDOWN,VK_CONTROL,0);
		SendMessage(wHandle,WM_KEYDOWN,0x56,0);
		SendMessage(wHandle,WM_KEYUP,0x56,0);
		SendMessage(wHandle,WM_KEYUP,VK_CONTROL,0);
		SendMessage(wHandle,WM_KEYDOWN,VK_RETURN,0);
		SendMessage(wHandle,WM_KEYUP,VK_RETURN,0);
	} 
	else
	{
		SendMessage(wHandle,WM_KEYDOWN,VK_RETURN,0);
		SendMessage(wHandle,WM_KEYUP,VK_RETURN,0);
		SendMessage(wHandle,WM_KEYDOWN,VK_CONTROL,0);
		SendMessage(wHandle,WM_KEYDOWN,0x56,0);
		SendMessage(wHandle,WM_KEYUP,0x56,0);
		SendMessage(wHandle,WM_KEYUP,VK_CONTROL,0);
		SendMessage(wHandle,WM_KEYDOWN,VK_RETURN,0);
		SendMessage(wHandle,WM_KEYUP,VK_RETURN,0);
	}
}


