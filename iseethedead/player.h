#pragma once
#include "pch.h"
enum color {
	PLAYER_COLOR_RED = 0, PLAYER_COLOR_BLUE,
	PLAYER_COLOR_CYAN,
	PLAYER_COLOR_PURPLE,
	PLAYER_COLOR_YELLOW,
	PLAYER_COLOR_ORANGE,
	PLAYER_COLOR_GREEN,
	PLAYER_COLOR_PINK,
	PLAYER_COLOR_LIGHT_GRAY,
	PLAYER_COLOR_LIGHT_BLUE,
	PLAYER_COLOR_AQUA,
	PLAYER_COLOR_BROWN
};

namespace war3 {
	struct CPlayerWar3 {
		void** vtable;
		uint8_t				unk_04[0x2C];
		uint16_t			slot;
		uint8_t				unk_32[0x02];
		void* selection;
		uint8_t				unk_38[0x228];
		uint32_t			race;
		uint32_t			color;
		uint8_t				unk_268[0x10];
		uint32_t			team;
		uint8_t				unk_27C[0x54];
		void* techtree;
	};

	struct CGameWar3 {
		void** vtable;
		uint32_t		unk_4;
		uint32_t		jassStringId;
		uint8_t			unk_C[0x1C];
		uint16_t		localPlayerSlot;
		uint8_t			unk_2A[0x1A];
		uint32_t		maxPlayers;
		uint8_t			unk_48[0x04];
		uint32_t		activePlayers;
		uint8_t			unk_50[0x08];
		CPlayerWar3* players[16];
	};
}

int PlayerLocal();
war3::CPlayerWar3* PlayerObject(int playerId);
const char* GetPlayerColorString(int c);

typedef struct {
	bool isEnabled;
	unsigned int playerHandle;
	bool isAlly;
	bool isEnemy;
}playerInfo;

class gamePlayerInfo {
private:
	unsigned int loaclPlayerHandle = 0;
	unsigned int localPlayerSlot = 0;
	playerInfo players[12] = { 0 };
	bool ready = false;
public:
	gamePlayerInfo() {};
	~gamePlayerInfo() {};
	void fresh();
	bool isPlayerAlly(unsigned int slot)
	{
		if (slot > 12) return false;
		if (this->ready == false) return false;
		if (this->players[slot].isEnabled == false) return false;
		return this->players[slot].isAlly;
	}

	bool isPlayerEnemy(unsigned int slot)
	{
		if (slot > 12) return false;
		if (this->ready == false) return false;
		if (this->players[slot].isEnabled == false) return false;
		return this->players[slot].isEnemy;
	}

	unsigned int getLocalPlayer()
	{
		return this->loaclPlayerHandle;
	}

	unsigned int getLocalPlayerSlot()
	{
		if (this->ready == false) return 0;
		return this->localPlayerSlot;
	}

	unsigned int getPlayerHandle(unsigned int slot)
	{
		if (slot > 12) return false;
		if (this->ready == false) return 0;
		if (this->players[slot].isEnabled == false) return 0;
		return this->players[slot].playerHandle;
	}
};