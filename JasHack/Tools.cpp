#include "stdafx.h"
#include "Tools.h"


void EnableDebugPriv()  
{
	HANDLE hToken;
	LUID sedebugnameValue;
	TOKEN_PRIVILEGES tkp;
	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
	LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &sedebugnameValue);
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = sedebugnameValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken, false, &tkp, sizeof tkp, NULL, NULL);
	CloseHandle(hToken);
}

void PatchJMP(BYTE* source,BYTE* destination, const int length)
{
	BYTE* jump = (BYTE*) malloc(length + 5);
	DWORD oldProtection;
	VirtualProtect(source, length, PAGE_EXECUTE_READWRITE, &oldProtection);
	memcpy(jump, source, length);
	jump[length] = 0xE9;
	*(DWORD*)(jump + length) = (DWORD)((source + length) - (jump + length)) - 5;
	source[0] = 0xE9;
	*(DWORD*)(source + 1) = (DWORD)(destination - source) - 5;
	for(int i = 5; i < length; i++)
		source[i] = 0x90;
	VirtualProtect(source, length, oldProtection, &oldProtection);
}

void PatchCALL(BYTE* source,BYTE* destination, const int length)
{
	BYTE* jump = (BYTE*) malloc(length + 5);
	DWORD oldProtection;
	VirtualProtect(source, length, PAGE_EXECUTE_READWRITE, &oldProtection);
	memcpy(jump + 3, source, length);
	jump[0] = 0x58;
	jump[1] = 0x59;
	jump[2] = 0x50;
	jump[length+3] = 0xE9;
	*(DWORD*)(jump+length+4) = (DWORD)((source+length) - (jump+length+3)) - 5;
	source[0] = 0xE8;
	*(DWORD*)(source+1) = (DWORD)(destination - (source)) - 5;
	for( int i=5; i < length; i++ )
		source[i] = 0x90;
	VirtualProtect(source, length, oldProtection, &oldProtection);
}
char *WideCharToUTF8(const wchar_t *const szWideChar)
{
	static char *pszTemp;
	int iTextLen;
	iTextLen = WideCharToMultiByte(CP_UTF8, 0, szWideChar, -1, NULL, 0, NULL, NULL);
	pszTemp = new char[iTextLen+1];
	memset(pszTemp, 0x00, sizeof(char)*(iTextLen+1));
	WideCharToMultiByte(CP_UTF8, 0, szWideChar, -1, pszTemp, iTextLen, NULL, NULL);
	return pszTemp;
}

bool SetClipBoardText(const char* text)
{
	//打开剪贴板
	if ( !::OpenClipboard(wHandle) )
		return false;
	//empties the clipboard and frees handles to data in the clipboard
	if ( !EmptyClipboard() )
	{
		CloseClipboard();
		return false;
	}
	//get text length
	int len=strlen(text);
	//After SetClipboardData is called, the system owns the object identified by the hMem parameter. 
	//The application can read the data, but must not free the handle or leave it locked. If the 
	//hMem parameter identifies a memory object, the object must have been allocated using the 
	//GlobalAlloc function with the GMEM_MOVEABLE and GMEM_DDESHARE flags. 
	HANDLE hClip=GlobalAlloc(GMEM_MOVEABLE|GMEM_DDESHARE,(len+1)*sizeof(TCHAR));
	if (hClip==NULL)
	{
		CloseClipboard();
		return false;
	}
	//locks a global memory object and returns a pointer to the first byte of the object's memory block
	TCHAR* pBuf=(TCHAR*)GlobalLock(hClip);
	if (pBuf==NULL)
	{
		GlobalFree(hClip);  
		CloseClipboard();
		return false;
	}

	memcpy(pBuf,text,len*sizeof(TCHAR));
	pBuf[len]=NULL;

	GlobalUnlock(hClip);
	if (NULL==SetClipboardData(CF_TEXT,hClip))
	{
		GlobalFree(hClip);  
		CloseClipboard();
		return false;
	}
	CloseClipboard();
	return true;
}
//打印调试信息
//output debug strings
int dbgPrintf(const char *fmt, ...)
{
	va_list args;
	char buffer[4096];
	int i;
	va_start(args, fmt);
	i=vsprintf_s(buffer,fmt,args);
	va_end(args);
	OutputDebugStringA(buffer);
	return i;
}