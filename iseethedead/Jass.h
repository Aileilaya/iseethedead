#pragma once
union Float
{
	float fl;
	DWORD dw;
};
#define ALLIANCE_SHARED_VISION 5
#define UNIT_TYPE_SUMMONED 10
namespace jass {
	const int PLAYER_SLOT_STATE_EMPTY = 0;
	const int PLAYER_SLOT_STATE_PLAYING = 1;
	const int PLAYER_SLOT_STATE_LEFT = 2;

	typedef int(__fastcall* pGetAddrByHandle)				(unsigned int hUnit);
	extern pGetAddrByHandle GetAddrByHandle;

	typedef int(__cdecl* pGetHeroLevel)				(unsigned int hUnit);
	extern pGetHeroLevel GetHeroLevel;
	
	typedef int(__cdecl* pGetUnitLevel)				(unsigned int hUnit);
	extern pGetUnitLevel GetUnitLevel;

	typedef Float(__cdecl* pGetUnitState)			(unsigned int hUnit, unsigned int hUnitState);
	extern pGetUnitState GetUnitState;

	const unsigned int PLAYER_STATE_RESOURCE_GOLD = 1;
	typedef int(__cdecl* pGetPlayerState)			(unsigned int hPlayer, unsigned int whichstate);
	extern pGetPlayerState GetPlayerState;

	typedef bool(__cdecl* pIsUnitEnemy)				(unsigned int hUnit, unsigned int hPlayer);
	extern pIsUnitEnemy	IsUnitEnemy;
	
	typedef bool(__cdecl* pIsUnitAlly)				(unsigned int hUnit, unsigned int hPlayer);
	extern pIsUnitAlly	IsUnitAlly;

	typedef bool(__cdecl* pIsUnitType)				(unsigned int hUnit, unsigned int unittype);
	extern pIsUnitType IsUnitType;

	typedef Float(__cdecl* pGetUnitMoveSpeed)		(unsigned int hUnit);
	extern pGetUnitMoveSpeed GetUnitMoveSpeed;

	typedef bool(__cdecl* pIsUnitIllusion)			(unsigned int hUnit);
	extern pIsUnitIllusion IsUnitIllusion;

	typedef unsigned int(__cdecl* pGetLocalPlayer)		();
	extern pGetLocalPlayer	GetLocalPlayer;

	typedef unsigned int(__cdecl* pPlayer)				(unsigned int slot);
	extern pPlayer Player;

	typedef bool(__cdecl* pIsPlayerEnemy)			(unsigned int hPlayer, unsigned int otherplayer);
	extern pIsPlayerEnemy IsPlayerEnemy;

	typedef bool(__cdecl* pIsPlayerAlly)			(unsigned int hPlayer, unsigned int otherplayer);
	extern pIsPlayerAlly IsPlayerAlly;

	typedef unsigned int(__cdecl* pGetOwningPlayer)		(unsigned int unit);
	extern pGetOwningPlayer GetOwningPlayer;

	typedef unsigned int(__cdecl* pGetPlayerColor)		(unsigned int hPlayer);
	extern pGetPlayerColor GetPlayerColor;

	typedef void(__cdecl* pDestroyTextTag)			(unsigned int hTextTag);
	extern pDestroyTextTag	DestroyTextTag;

	typedef Float(__cdecl* pGetUnitX)				(unsigned int hUnit);
	extern pGetUnitX	GetUnitX;

	typedef Float(__cdecl* pGetUnitY)				(unsigned int hUnit);
	extern pGetUnitY	GetUnitY;

	typedef Float(__cdecl* pGetItemX)				(unsigned int hUnit);
	extern pGetItemX	GetItemX;

	typedef Float(__cdecl* pGetItemY)				(unsigned int hUnit);
	extern pGetItemY	GetItemY;

	typedef void(__cdecl* pPingMinimapEx)			(const float* x, const float* y, const float* duration, const int red, const int green, const int blue, bool extraEffects);
	extern pPingMinimapEx	PingMinimapEx;

	typedef void(__cdecl* pUnitAddIndicator)		(unsigned int hUnit, int red, int green, int blue, int alpha);
	extern pUnitAddIndicator	UnitAddIndicator;

	typedef void(__cdecl* pAddIndicator)		(unsigned int hUnit, int red, int green, int blue, int alpha);
	extern pAddIndicator	AddIndicator;

	typedef unsigned int(__cdecl* pCreateTextTag)		();
	extern pCreateTextTag CreateTextTag;

	typedef void(__cdecl* pSetTextTagPermanent)		(unsigned int hTextTag, bool flag);
	extern pSetTextTagPermanent	SetTextTagPermanent;

	typedef void(__cdecl* pSetTextTagText)			(unsigned int hTextTag, CJassString* Text, float* height);
	extern pSetTextTagText	SetTextTagText;

	typedef void(__cdecl* pSetTextTagColor)			(unsigned int hTextTag, unsigned int color);
	extern pSetTextTagColor	SetTextTagColor;

	typedef int(__cdecl* pSetTextTagPos)(unsigned int t, float* x, float* y, float* heightOffset);
	extern pSetTextTagPos	SetTextTagPos;

	typedef int(__cdecl* pSetTextTagPosUnit)		(unsigned int hTextTag, int hUnit, float* heightOffset);
	extern pSetTextTagPosUnit SetTextTagPosUnit;

	typedef bool(__cdecl* pIsUnitVisible)			(unsigned int hUnit, unsigned int hPlayer);
	extern pIsUnitVisible IsUnitVisible;

	typedef void(__cdecl* pSetTextTagVisibility)	(unsigned int hTextTag, bool flag);
	extern pSetTextTagVisibility SetTextTagVisibility;

	typedef bool(__cdecl* pIsUnitVisible)			(unsigned int hUnit, unsigned int hPlayer);
	extern pIsUnitVisible IsUnitVisible;

	typedef void(__cdecl* pSetTextTagVisibility)	(unsigned int hTextTag, bool flag);
	extern pSetTextTagVisibility SetTextTagVisibility;

	typedef int(__cdecl* pGetPlayerController)(unsigned int whichPlayer);
	extern pGetPlayerController GetPlayerController;

	typedef int(__cdecl* pGetPlayerSlotState)(unsigned int whichPlayer);
	extern pGetPlayerSlotState GetPlayerSlotState;

	typedef bool(__cdecl* pIsFoggedToPlayer)(float* x, float* y, unsigned int whichPlayer);
	extern pIsFoggedToPlayer IsFoggedToPlayer;

	typedef bool(__cdecl* pIsVisibleToPlayer)(float* x, float* y, unsigned int whichPlayer);
	extern pIsVisibleToPlayer IsVisibleToPlayer;
	
	typedef bool(__cdecl* pIsUnitSelected)(unsigned int unit,unsigned int player);
	extern pIsUnitSelected IsUnitSelected;

	typedef unsigned int(__cdecl* pGetSpellAbilityUnit)();
	extern pGetSpellAbilityUnit GetSpellAbilityUnit;

	typedef Float(__cdecl* pGetWidgetLife)				(unsigned int hUnit);
	extern pGetWidgetLife	GetWidgetLife;

	typedef bool(__cdecl* pIsItemOwned)				(unsigned int hUnit);
	extern pIsItemOwned		IsItemOwned;

	typedef bool(__cdecl* pGetPlayerAlliance)		(unsigned int hPlayer1, unsigned int hPlayer2, unsigned int type);
	extern pGetPlayerAlliance	GetPlayerAlliance;

	typedef Float(__cdecl* pGetUnitFacing)			(unsigned int hUnit);
	extern pGetUnitFacing	GetUnitFacing;

	typedef unsigned int(__fastcall* pGetUnitByIDs)(unsigned int, unsigned int);

	typedef char* (__cdecl* pGetObjectName)(unsigned int hObject);
	extern pGetObjectName	GetObjectName;

	typedef Float(__cdecl* pGetCameraBoundMinX)();
	extern pGetCameraBoundMinX	GetCameraBoundMinX;

	typedef Float(__cdecl* pGetCameraBoundMaxX)();
	extern pGetCameraBoundMaxX	GetCameraBoundMaxX;

	typedef Float(__cdecl* pGetCameraBoundMinY)();
	extern pGetCameraBoundMinY	GetCameraBoundMinY;

	typedef Float(__cdecl* pGetCameraBoundMaxY)();
	extern pGetCameraBoundMaxY	GetCameraBoundMaxY;

#define RACE_HUMAN		1
#define RACE_ORC		2
#define RACE_UNDEAD		3
#define RACE_NIGHTELF	4
#define RACE_DEMON		5
#define RACE_OTHER		7
#define RACE_UNK		8
	typedef unsigned int(__cdecl* pGetUnitRace)			(unsigned int hUnit);
	extern pGetUnitRace GetUnitRace;

	typedef int(__fastcall* pGetTypeInfo)(int unit_item_code, int unused);
	extern pGetTypeInfo GetTypeInfo;

	void init();
	bool IsUnitDead(unsigned int hUnit);
	bool IsUnitHero(unsigned int hUnit);
	bool IsUnitWard(unsigned int hUnit);
	int GetObjectClassID(int unit_or_item_addr);
	const char* GetObjectNameByID(int clid);
	char* GetUnitName(unsigned int hUnit);
	char* GetItemName(unsigned int hItem);
	char* GetPlayerName(unsigned int hPlayer);
	unsigned int GetPlayerBySlot(int slot);
	void* GetUnitThroughId(unsigned int d1, unsigned int d2);
	__declspec(noinline) int GetRandomInt(int min, int max);
	char* GetUnitNameAddr(unsigned int Unit);
	void ChangeTexttagText(unsigned int tag, CJassString* str);
}
