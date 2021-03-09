#include "pch.h"
#include "unit.h"
#include "tools.h"
#include "miniMapHack.h"
extern gamePlayerInfo* aPlayerInfo;
extern MiniMapHack* aMiniMapHack;
static float HIGHT_OFFSET = 10;
W3unit::W3unit(unsigned int handle,unsigned int object, int cha):jass_handle(handle),addr(object),character(cha)
{
	name = jass::GetUnitNameAddr(addr);
	owning_player = jass::GetOwningPlayer(jass_handle);
	owning_player_slot = jass::GetPlayerColor(owning_player);
	
	this->isTagShown = true;
	switch (character) {
	case 1:
		jStr = std::make_unique<jassString>("|cffffff00Revealed|r");
		break;
	case 5:
		jStr = std::make_unique<jassString>("NULL");
		break;
	}
	jass_tag = jass::CreateTextTag();
	jass::SetTextTagVisibility(jass_tag, true);
	jass::ChangeTexttagText(jass_tag, this->jStr->GetJassStr());
	jass::SetTextTagPosUnit(jass_tag, jass_handle, &HIGHT_OFFSET);
}

void W3unit::refreshTag()
{
	bool toggled = false;
	char buff[256];
	//logger->info("refreshing tag {0:x}", (unsigned int)this);
	if (jass::IsUnitDead(jass_handle)) {
		this->toggleTag(false);
	}
	else if(jass_tag) {
		switch (character) {
		case 1:
			for (int i = 0; i < 12; i++) {
				unsigned int hPlayer = aPlayerInfo->getPlayerHandle(i);
				if (hPlayer && aPlayerInfo->isPlayerEnemy(i) && jass::IsUnitVisible(jass_handle, hPlayer)) {
					jass::SetTextTagPosUnit(jass_tag, jass_handle, &HIGHT_OFFSET);
					this->toggleTag(true);
					toggled = true;
					break;
				}
			}
			if (false == toggled) {
				this->toggleTag(false);
			}
			break;
		case 5:
			_snprintf_s(buff, _TRUNCATE, "|cFFADFF2F%.0f|r|cFFFFFFFF/|r|cFF6495ED%.0f|r",
				jass::GetUnitState(jass_handle, 0).fl, jass::GetUnitState(jass_handle, 2).fl
			);
			this->jStr->ChangeStr(buff);
			jass::ChangeTexttagText(jass_tag, this->jStr->GetJassStr());
			jass::SetTextTagPosUnit(jass_tag, jass_handle, &HIGHT_OFFSET);
			this->toggleTag(true);
			break;
		}
	}
	else {
		jass_tag = jass::CreateTextTag();
	}
}

void W3unit::minimapIndicate()
{
	if (jass::IsUnitDead(jass_handle))	return;
	const static float DURATION = 0.33f;
	switch (character)
	{
	case 5:
		float itX = GetUnitX();
		float itY = GetUnitY();
		uint32_t playerColor = GetPlayerColorHEX(owning_player_slot);
		jass::PingMinimapEx(&itX, &itY, &DURATION, playerColor >> 16 & 0xff, playerColor >> 8 & 0xff, playerColor & 0xff, false);
		break;
	}
}

W3unit::~W3unit()
{
	//此处的2个条件为了在游戏关闭时 防止报错
	if (jass_tag != NULL && IsGameObjectPresent() && IsInGame()) {
		jass::DestroyTextTag(jass_tag);
	}
}
