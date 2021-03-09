#include "pch.h"
#include "tools.h"

int filter(unsigned int code, struct _EXCEPTION_POINTERS* ep)
{
	logger->error("error {0:x} at {1:x} hIsee {2:x} gamedll {3:x}", code, ep->ContextRecord->Eip, hIsee, (unsigned int)GetModuleHandle(L"Game.dll"));
	//puts("in filter.");
	//if (code == EXCEPTION_ACCESS_VIOLATION)
	//{
	//	puts("caught AV as expected.");
	//	return EXCEPTION_EXECUTE_HANDLER;
	//}
	//else
	//{
	//	puts("didn't catch AV, unexpected.");
	//	return EXCEPTION_CONTINUE_SEARCH;
	//};
	return EXCEPTION_EXECUTE_HANDLER;
}

unsigned int WarcraftVersion()
{
	DWORD dwHandle;
	DWORD dwLen = GetFileVersionInfoSize(L"Game.dll", &dwHandle);
	std::unique_ptr<char[]> lpData(new char[dwLen]);
	GetFileVersionInfo(L"Game.dll", dwHandle, dwLen, lpData.get());
	LPBYTE lpBuffer = NULL;
	UINT   uLen = NULL;
	VerQueryValue(lpData.get(), L"\\", (LPVOID*)&lpBuffer, &uLen);
	VS_FIXEDFILEINFO* Version = (VS_FIXEDFILEINFO*)lpBuffer;
	DWORD ret = Version->dwFileVersionLS;
	return LOWORD(ret);
}

bool IsGameObjectPresent()
{
	unsigned int* GameGlobalObject = (unsigned int*)(gameDll + 0xBE4238);
	bool ret = (*GameGlobalObject != NULL);
	return ret;
}

unsigned int ObjectToHandle(void* pObj) {
	if (!pObj) return 0;
	unsigned int result;
	unsigned int GameGlobalObject = gameDll + 0xBE4238;
	unsigned int GameHandleFromObject = gameDll + 0x2651D0;
	unsigned int GameStateGet = gameDll + 0x1C3200;
	__asm {
		mov ecx, GameGlobalObject
		mov ecx, [ecx]
		call GameStateGet
		mov ecx, eax
		push 0
		push pObj
		call GameHandleFromObject
		mov result, eax
	}
	return result;
};

void PlantDetourCall(BYTE* bSource, BYTE* bDestination, size_t iLength) {
	DWORD dwOldProtection = NULL;
	VirtualProtect(bSource, iLength, PAGE_EXECUTE_READWRITE, &dwOldProtection);
	bSource[0] = 0xE8;
	*(DWORD*)(bSource + 1) = (DWORD)(bDestination - bSource) - 5;
	for (size_t i = 5; i < iLength; i++)
		bSource[i] = 0x90;
	VirtualProtect(bSource, iLength, dwOldProtection, NULL);
}

bool IsInGame()
{
	/*
				NOGAME INGAME
		+B6653C 8	   1
		+B684C8 1	   0
		+BEDFFC 1	   0
		+BEE090 3	   0
	*/
	//return *(unsigned int*)(dwGameDll + 0xB684C8) == 0 || *(unsigned int*)(dwGameDll + 0xBE5F78) == 1;
	return *(unsigned int*)(gameDll + 0xBEDFFC) == 0;
}

void DisplayText(const char* szText, float fDuration) {
	if (IsInGame())
	{
		void* GameGlobalUI = (void*)(0xBE6350 + gameDll);
		unsigned int PrintTextCall = gameDll + 0x3577B0;
		__asm
		{
			PUSH	0xFFFFFFFF;
			PUSH	fDuration;
			PUSH	szText;
			MOV		ECX, [GameGlobalUI];
			MOV		ECX, [ECX];
			MOV		EAX, PrintTextCall;
			CALL	EAX;
		}
	}
};

static char ConvertOrderIdBuff[64];
const char* ConvertOrderId(unsigned int orderId)
{
	switch (orderId)
	{
	case 0xD000F:
		return "attack";
	case 0xD0002:
	case 0xD0003:
		return "smart";
	case 0xD0012:
		return "move";
	case 0xD0016:
		return "patrol";
	case 0xD0019:
		return "hold";
	case 0xD001A:
		return "build";
	case 0xD0022:
	case 0xD0023:
	case 0xD0024:
	case 0xD0025:
	case 0xD0026:
	case 0xD0027:
		return "put item(ingore)";
	case 0xD0028:
	case 0xD0029:
	case 0xD002a:
	case 0xD002b:
	case 0xD002c:
	case 0xD002d:
		return "use item";
	case 0xD0021:
		return "drop item";
	default:
		_snprintf_s(ConvertOrderIdBuff, _TRUNCATE, "%x", orderId);
		return ConvertOrderIdBuff;
	}
}

bool FilterOrderId(unsigned int orderId)
{
	switch (orderId)
	{
	case 0xD0022:
	case 0xD0023:
	case 0xD0024:
	case 0xD0025:
	case 0xD0026:
	case 0xD0027:
		//return "put item(ingore)";
	case 0xD0028:
	case 0xD0029:
	case 0xD002a:
	case 0xD002b:
	case 0xD002c:
	case 0xD002d:
		//use item
		return false;
	default:
		return true;
	}
}

uint32_t PlayerColorsHEX[12]{
	0xffff0303,
	0xff0042ff,
	0xff1ce6b9,
	0xff540081,
	0xfffffc01,
	0xfffe8000,
	0xff20c000,
	0xffe55bb0,
	0xff959697,
	0xff7ebff1,
	0xff106246,
	0xff4e2a04
};

uint32_t GetPlayerColorHEX(unsigned int c)
{
	uint32_t ret;
	if (c > 12) {
		ret = 0xffffffff;
	}
	else {
		ret = PlayerColorsHEX[c];
	}
	return ret;
}

void HideLDRTable(HMODULE module)
{
	DWORD* PEB = NULL;
	DWORD* Ldr = NULL;
	DWORD* Flink = NULL;
	DWORD* p = NULL;
	DWORD* BaseAddress = NULL;
	DWORD* FullDllName = NULL;

	//Localization of PEB
	__asm
	{
		//The location of the FS save TEB
		//fs:[0x30]The location to save the PEB
		mov eax, fs: [0x30]
		mov PEB, eax
	}

	HMODULE hMod = module;

	//Get LDR
	Ldr = *((DWORD**)((unsigned char*)PEB + 0x0c));
	//The second list
	Flink = *((DWORD**)((unsigned char*)Ldr + 0x0c));
	p = Flink;

	do
	{
		BaseAddress = *((DWORD**)((unsigned char*)p + 0x18));
		FullDllName = *((DWORD**)((unsigned char*)p + 0x28));

		if ((DWORD*)hMod == BaseAddress)
		{
			**((DWORD**)(p + 1)) = (DWORD) * ((DWORD**)p);
			*(*((DWORD**)p) + 1) = (DWORD) * ((DWORD**)(p + 1));
			break;
		}

		p = *((DWORD**)p);
	} while (Flink != p);

	Flink = *((DWORD**)((unsigned char*)Ldr + 0x14));
	p = Flink;
	do
	{
		BaseAddress = *((DWORD**)((unsigned char*)p + 0x10));
		FullDllName = *((DWORD**)((unsigned char*)p + 0x20));
		if (BaseAddress == (DWORD*)hMod)
		{
			**((DWORD**)(p + 1)) = (DWORD) * ((DWORD**)p);
			*(*((DWORD**)p) + 1) = (DWORD) * ((DWORD**)(p + 1));
			break;
		}
		p = *((DWORD**)p);
	} while (Flink != p);

	Flink = *((DWORD**)((unsigned char*)Ldr + 0x1c));
	p = Flink;
	do
	{
		BaseAddress = *((DWORD**)((unsigned char*)p + 0x8));
		FullDllName = *((DWORD**)((unsigned char*)p + 0x18));
		if (BaseAddress == (DWORD*)hMod)
		{
			**((DWORD**)(p + 1)) = (DWORD) * ((DWORD**)p);
			*(*((DWORD**)p) + 1) = (DWORD) * ((DWORD**)(p + 1));
			break;
		}
		p = *((DWORD**)p);
	} while (Flink != p);
}

void DisplayChatMessage(const char* msg, float duration, unsigned int PlayerSlot, unsigned int chattype) {
	unsigned int GameGlobalUI = *(unsigned int*)(0xBE6350 + gameDll);
	void* DisplayPlayerChatMessageCall = (void*)(0x355CF0 + gameDll);
	if (GameGlobalUI) {
		_asm {
			PUSH duration
			PUSH chattype
			PUSH msg
			PUSH PlayerSlot
			MOV ECX, GameGlobalUI
			CALL DisplayPlayerChatMessageCall
		}
	}
}

bool PostChatMessage(const char* msg, float duration, unsigned int PlayerSlot, unsigned int chattype) {
	unsigned int hischatUI = 0, GameGlobalUI = *(unsigned int*)(0xBE6350 + gameDll);
	void* PostPlayerChatMessageCall = (void*)(0x38D030 + gameDll);
	if (GameGlobalUI) {
		hischatUI = *(unsigned int*)((unsigned int)GameGlobalUI + 0x23c);
		if (hischatUI) { 
			hischatUI = *(unsigned int*)((unsigned int)hischatUI + 0xc);
			if (hischatUI) {
				_asm {
					PUSH duration
					PUSH chattype
					PUSH msg
					PUSH PlayerSlot
					MOV ECX, hischatUI
					CALL PostPlayerChatMessageCall
				}
				return true;
			}
		}
	}
	return false;
}