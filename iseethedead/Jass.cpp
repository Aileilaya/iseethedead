#include "pch.h"
namespace jass {
	pGetHeroLevel			GetHeroLevel;
	pGetUnitLevel			GetUnitLevel;
	pGetUnitState			GetUnitState;
	pIsUnitEnemy			IsUnitEnemy;
	pIsUnitType				IsUnitType;
	pGetUnitMoveSpeed		GetUnitMoveSpeed;
	pIsUnitIllusion			IsUnitIllusion;
	pGetLocalPlayer			GetLocalPlayer;
	pPlayer					Player;
	pIsPlayerEnemy			IsPlayerEnemy;
	pIsPlayerAlly			IsPlayerAlly;
	pGetOwningPlayer		GetOwningPlayer;
	pGetPlayerColor			GetPlayerColor;
	pDestroyTextTag			DestroyTextTag;
	pGetUnitX				GetUnitX;
	pGetUnitY				GetUnitY;
	pGetItemX				GetItemX;
	pGetItemY				GetItemY;
	pPingMinimapEx			PingMinimapEx;
	pUnitAddIndicator		UnitAddIndicator;
	pCreateTextTag			CreateTextTag;
	pSetTextTagPermanent	SetTextTagPermanent;
	pSetTextTagText			SetTextTagText;
	pSetTextTagColor		SetTextTagColor;
	pSetTextTagPosUnit		SetTextTagPosUnit;
	pIsUnitVisible			IsUnitVisible;
	pSetTextTagVisibility	SetTextTagVisibility;
	pGetUnitRace			GetUnitRace;
	pGetPlayerState			GetPlayerState;
	pIsUnitAlly				IsUnitAlly;
	pGetPlayerController	GetPlayerController;
	pGetPlayerSlotState		GetPlayerSlotState;
	pIsFoggedToPlayer		IsFoggedToPlayer;
	pIsVisibleToPlayer		IsVisibleToPlayer;
	pIsUnitSelected			IsUnitSelected;
	pGetSpellAbilityUnit	GetSpellAbilityUnit;
	pGetObjectName			GetObjectName;
	pGetTypeInfo			GetTypeInfo;
	pAddIndicator			AddIndicator;
	pGetWidgetLife			GetWidgetLife;
	pIsItemOwned			IsItemOwned;
	pGetPlayerAlliance		GetPlayerAlliance;
	pGetAddrByHandle		GetAddrByHandle;
	pGetUnitFacing			GetUnitFacing;
	pGetUnitByIDs			GetUnitByIDs;
	pGetCameraBoundMinX	GetCameraBoundMinX;
	pGetCameraBoundMinY	GetCameraBoundMinY;
	pGetCameraBoundMaxX	GetCameraBoundMaxX;
	pGetCameraBoundMaxY	GetCameraBoundMaxY;
	static unsigned int addrUnitName1, addrUnitName2;
	static unsigned int addrItemName1, addrItemName2;
	static unsigned int addrGetPlayerName1, addrGetPlayerName2;
	static const char* nullString = "(null)";
	void init() {
		GetAddrByHandle = (pGetAddrByHandle)(gameDll + 0x1D1550);
		addrUnitName1 = (gameDll + 0x1D1550);
		addrUnitName2 = (gameDll + 0x326BA0);
		addrItemName1 = (gameDll + 0x1CFC50);
		addrItemName2 = (gameDll + 0x326BA0);
		addrGetPlayerName1 = gameDll + 0x1D03D0;
		addrGetPlayerName2 = gameDll + 0x24A890;
		GetHeroLevel = (pGetHeroLevel)(gameDll + 0x1E2870);
		GetUnitLevel = (pGetUnitLevel)(gameDll + 0x1E6210);
		GetUnitState = (pGetUnitState)(gameDll + 0x1E6600);
		IsUnitEnemy = (pIsUnitEnemy)(gameDll + 0x1E85C0);
		IsUnitType = (pIsUnitType)(gameDll + 0x1E8CC0);
		GetUnitMoveSpeed = (pGetUnitMoveSpeed)(gameDll + 0x1E62E0);
		IsUnitIllusion = (pIsUnitIllusion)(gameDll + 0x1E88C0);
		GetLocalPlayer = (pGetLocalPlayer)(gameDll + 0x1E3150);
		Player = (pPlayer)(gameDll + 0x1F1E70);
		IsPlayerEnemy = (pIsPlayerEnemy)(gameDll + 0x1E8090);
		IsPlayerAlly = (pIsPlayerAlly)(gameDll + 0x1E8040);
		GetOwningPlayer = (pGetOwningPlayer)(gameDll + 0x1E3BA0);
		GetPlayerColor = (pGetPlayerColor)(gameDll + 0x1E3CA0);
		DestroyTextTag = (pDestroyTextTag)(gameDll + 0x1DF760);
		GetUnitX = (pGetUnitX)(gameDll + 0x1E66B0);
		GetUnitY = (pGetUnitY)(gameDll + 0x1E66F0);
		GetItemX = (pGetItemX)(gameDll + 0x1E2D00);
		GetItemY = (pGetItemY)(gameDll + 0x1E2D40);
		PingMinimapEx = (pPingMinimapEx)(gameDll + 0x1F1C30);
		UnitAddIndicator = (pUnitAddIndicator)(gameDll + 0x1FA580);
		CreateTextTag = (pCreateTextTag)(gameDll + 0x1DEA90);
		SetTextTagPermanent = (pSetTextTagPermanent)(gameDll + 0x1F6E00);
		SetTextTagText = (pSetTextTagText)(gameDll + 0x1F6F70);
		SetTextTagColor = (pSetTextTagColor)(gameDll + 0x1F6D30);
		SetTextTagPosUnit = (pSetTextTagPosUnit)(gameDll + 0x1F6ED0);
		IsUnitVisible = (pIsUnitVisible)(gameDll + 0x1E8E80);
		SetTextTagVisibility = (pSetTextTagVisibility)(gameDll + 0x1F7020);
		GetUnitRace = (pGetUnitRace)(gameDll + 0x1E63D0);
		GetPlayerState = (pGetPlayerState)(gameDll + 0x1E4080);
		IsUnitAlly = (pIsUnitAlly)(gameDll + 0x1E8520);
		GetPlayerController = (pGetPlayerController)(gameDll + 0x1E3CC0);
		GetPlayerSlotState = (pGetPlayerSlotState)(gameDll + 0x1E3FE0);
		IsFoggedToPlayer = (pIsFoggedToPlayer)(gameDll + 0x1E7A10);
		IsVisibleToPlayer = (pIsVisibleToPlayer)(gameDll + 0x1E8F50);
		IsUnitSelected = (pIsUnitSelected)(gameDll + 0x1E8C40);
		GetSpellAbilityUnit = (pGetSpellAbilityUnit)(gameDll + 0x1E4E40);
		GetObjectName = (pGetObjectName)(gameDll + 0x1E34A0);
		GetTypeInfo = (pGetTypeInfo)(gameDll + 0x327020);
		AddIndicator = (pAddIndicator)(gameDll + 0x1D9E10);
		GetWidgetLife = (pGetWidgetLife)(gameDll + 0x1E6730);
		IsItemOwned = (pIsItemOwned)(gameDll + 0x1E7C30);
		GetPlayerAlliance = (pGetPlayerAlliance)(gameDll + 0x1E3C50);
		GetUnitFacing = (pGetUnitFacing)(gameDll + 0x1E6130);
		GetUnitByIDs = (pGetUnitByIDs)(gameDll + 0x37350);

		GetCameraBoundMinX = (pGetCameraBoundMinX)(gameDll + 0x1E1870);
		GetCameraBoundMinY = (pGetCameraBoundMinY)(gameDll + 0x1E18A0);
		GetCameraBoundMaxX = (pGetCameraBoundMaxX)(gameDll + 0x1E1810);
		GetCameraBoundMaxY = (pGetCameraBoundMaxY)(gameDll + 0x1E1840);
	}
	char* GetUnitName(unsigned int hUnit)
	{
		char* retaddr = NULL;
		__asm
		{
			mov ecx, hUnit;
			CALL DWORD PTR DS : [addrUnitName1]
			test eax, eax;
			je NoUnit;
			mov ecx, [eax + 0x30];
			xor edx, edx;
			CALL DWORD PTR DS : [addrUnitName2]
			mov retaddr, eax;
		NoUnit:
		}
		return retaddr;
	}

	char* GetUnitNameAddr(unsigned int Unit)
	{
		char* retaddr = NULL;
		__asm
		{
			mov eax, Unit;
			mov ecx, [eax + 0x30];
			xor edx, edx;
			CALL DWORD PTR DS : [addrUnitName2]
			mov retaddr, eax;
		}
		return retaddr;
	}

	char* GetPlayerName(unsigned int hPlayer)
	{
		char* retaddr = NULL;
		__asm
		{
			mov ecx, hPlayer;
			CALL DWORD PTR DS : [addrGetPlayerName1]
				test eax, eax;
			jz NOPLAYER;
			push 1;
			mov ecx, eax;
			CALL DWORD PTR DS : [addrGetPlayerName2]
				NOPLAYER :
				mov retaddr, eax;
		}
		return retaddr;
	}

	char* GetItemName(unsigned int hItem)
	{
		char* retaddr = NULL;
		__asm
		{
			mov ecx, hItem;
			CALL DWORD PTR DS : [addrItemName1]
				test eax, eax;
			je NoUnit;
			mov ecx, [eax + 0x30];
			xor edx, edx;
			CALL DWORD PTR DS : [addrItemName2]
				mov retaddr, eax;
		NoUnit:
		}
		return retaddr;
	}

	bool IsUnitDead(unsigned int hUnit)
	{
		bool ret = false;
		if (GetUnitState(hUnit, 0).fl <= 0) {
			ret = true;
		}
		return ret;
	}

	bool IsUnitHero(unsigned int hUnit)
	{
		bool ret = true;
		if ((GetHeroLevel(hUnit) <= 0) || IsUnitIllusion(hUnit)) {
			ret = false;
		}
		return ret;
	}

	bool IsUnitWard(unsigned int hUnit)
	{
		//bool isSummoned = IsUnitType(hUnit, UNIT_TYPE_SUMMONED);
		bool isNotMove = (GetUnitMoveSpeed(hUnit).fl <= 30.0f);
		return isNotMove;
	}

	int GetObjectClassID(int unit_or_item_addr)
	{
		if (unit_or_item_addr)
			return *(int*)(unit_or_item_addr + 0x30);
		return 0;
	}

	const char* GetObjectNameByID(int clid)
	{
		if (clid > 0)
		{
			int v3 = GetTypeInfo(clid, 0);
			int v4, v5;
			if (v3 && (v4 = *(int*)(v3 + 40)) != 0)
			{
				v5 = v4 - 1;
				if (v5 >= (unsigned int)0)
					v5 = 0;
				return (char*)*(int*)(*(int*)(v3 + 44) + 4 * v5);
			}
			else
			{
				return nullString;
			}
		}
		return nullString;
	}

	unsigned int GetPlayerBySlot(int slot)
	{
		unsigned int GlobalPlayerData = *(unsigned int*)(0xBE4238 + gameDll);
		unsigned int result = NULL;
		result = *(unsigned int*)(GlobalPlayerData + 0x58 + (slot * 4));
		return result;
	}

	void ChangeTexttagText(unsigned int tag, CJassString* str)
	{
		static float rsize = 0.020f;
		SetTextTagText(tag, str, &rsize);
		//SetTextTagColor(tag, 0);
	}
}

void* jass::GetUnitThroughId(unsigned int d1, unsigned int d2)
{
	unsigned int result = jass::GetUnitByIDs(d1, d2);
	void* ret = nullptr;
	if (result) { 	// && *(unsigned int*)(result + 0xC) == 0x2B61676C
		ret = (void*)*(unsigned int*)(result + 0x54);
	}
	return ret;
}

int jass::GetRandomInt(int min, int max) {
	int ans = 0;
	if (min > max) return min;
	else {
		int len = 1 + max - min;
		unsigned int* pseed = (unsigned int*)(gameDll + 0xBC5FB0);
		pseed = (unsigned int*)*pseed;
		unsigned int addrRandInt = (gameDll + 0x199400);
		unsigned int seed[2];
		seed[0] = *(pseed); seed[1] = *(pseed + 1);
		pseed = &seed[0];
		_asm {
			push esi
			mov edi, min
			mov esi, len
			mov ecx, pseed
			call addrRandInt
			mul esi
			pop esi
			lea eax, dword ptr ds:[edi + edx]
			mov ans, eax
		}
		return ans;
	}
}