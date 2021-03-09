#include "pch.h"
#include "player.h"

int PlayerLocal() {
	war3::CGameWar3* globalGame = *(war3::CGameWar3**)(gameDll + 0xBE4238);
	if (globalGame) {
		return (int)globalGame->localPlayerSlot;
	}
	return -1;
}

war3::CPlayerWar3* PlayerObject(int playerId) {
	if (playerId >= 0 && playerId <= 15) {
		war3::CGameWar3* gameObj = *(war3::CGameWar3**)(gameDll + 0xBE4238);
		return gameObj->players[playerId];
	}
	return NULL;
}

const char* GetPlayerColorString(int c)
{
	const char* ret;
	switch (c) {
	case PLAYER_COLOR_RED:
		ret = "|cffFF0202";
		break;
	case PLAYER_COLOR_BLUE:
		ret = "|cff0041FF";
		break;
	case PLAYER_COLOR_CYAN:
		ret = "|cff1BE5B8";
		break;
	case PLAYER_COLOR_PURPLE:
		ret = "|cff530080";
		break;
	case PLAYER_COLOR_YELLOW:
		ret = "|cffFFFC00";
		break;
	case PLAYER_COLOR_ORANGE:
		ret = "|cffFE890D";
		break;
	case PLAYER_COLOR_GREEN:
		ret = "|cff1FBF00";
		break;
	case PLAYER_COLOR_PINK:
		ret = "|cffE45AAF";
		break;
	case PLAYER_COLOR_LIGHT_GRAY:
		ret = "|cff949596";
		break;
	case PLAYER_COLOR_LIGHT_BLUE:
		ret = "|cff7DBEF1";
		break;
	case PLAYER_COLOR_AQUA:
		ret = "|cff0F6145";
		break;
	case PLAYER_COLOR_BROWN:
		ret = "|cff4D2903";
		break;
	default:
		ret = "|cffFFFFFF";
		break;
	}
	return ret;
}

void gamePlayerInfo::fresh()
{
	if (IsInGame()) {
		this->loaclPlayerHandle = jass::Player(PlayerLocal());
		for (int i = 0; i < 12; i++) {
			unsigned int hPlayer = jass::Player(i);
			if (hPlayer == this->loaclPlayerHandle) {
				this->localPlayerSlot = i;
				this->players[i].isEnabled = true;
				this->players[i].playerHandle = hPlayer;
				this->players[i].isEnemy = false;
				this->players[i].isAlly = true;
			}
			else if (hPlayer &&
				jass::GetPlayerSlotState(hPlayer) == jass::PLAYER_SLOT_STATE_PLAYING //&& jass::GetPlayerController(hPlayer) != NULL
				) {
				this->players[i].isEnabled = true;
				this->players[i].playerHandle = hPlayer;
				this->players[i].isEnemy = jass::IsPlayerEnemy(this->loaclPlayerHandle, hPlayer);
				this->players[i].isAlly = jass::IsPlayerAlly(this->loaclPlayerHandle, hPlayer);
			}
			else {
				this->players[i].isEnabled = false;
			}
		}
		this->ready = true;
	}
	else {
		this->ready = false;
	}
}
