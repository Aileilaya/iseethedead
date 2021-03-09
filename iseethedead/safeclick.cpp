#include "pch.h"
#include "player.h"
#include "safeclick.h"

extern gamePlayerInfo* aPlayerInfo;
static unsigned int _4EFB0, UnitArray_v;
safeClick::CUnit_IsUnitVisible_t CUnit_IsUnitVisible;

bool __stdcall safeClick::SendActionHandler(CAction* lpAction)
{
	bool ret = TRUE;
	__try {
		SelectionAction_t* sa = (SelectionAction_t*)lpAction->GetData();
		SelectionActionItem_t* sai = (SelectionActionItem_t*)lpAction->GetData();
		if (lpAction->GetData()[0] == 0x16 && sa->wCount == 1 && sa->bMode == 1) {
			CUnit* unit = (CUnit*)jass::GetUnitThroughId(sa->dwUnitIds[0][0], sa->dwUnitIds[0][1]);
			if (unit) {
				unsigned int hUnit = ObjectToHandle(unit);
				//此处需要判断是否有视野的原因是 只有先点击单位才能对其发布命令
				//如果直接返回false会导致 无法购买物品 无法A S H M 和释放任何技能 如果用来整别人到时行。。。
				if (!unit->IsVisibleToPlayer(PlayerLocal()) && !jass::GetPlayerAlliance(aPlayerInfo->getLocalPlayer(), jass::GetOwningPlayer(hUnit), 5)) {
					ret = false;
				}
			}
		}
		else if (sai->bOpCode == 0x1c && sai->bMode == 0x04) {
			ret = false;
		}
	}
	__except (filter(GetExceptionCode(), GetExceptionInformation())) {
		logger->warn("safeClick::SendActionHandler crashed");
	}
	return ret;
}

void __declspec(naked) safeClick::SendActionHook()
{
	__asm
	{
		PUSH EBX
		CALL SendActionHandler
		TEST al, al
		JZ   dontsend
		MOV  ECX, 0Dh
		CALL DWORD PTR DS : [_4EFB0]
		RET

		dontsend :
		ADD ESP, 0x4
			POP EDI
			POP ESI
			POP EBX
			MOV ESP, EBP
			POP EBP
			RET
	}
}

void safeClick::init()
{
	CUnit_IsUnitVisible = CUnit_IsUnitVisible_t(gameDll + 0x6516E0);
	UnitArray_v = gameDll + 0xBB9D88;
	_4EFB0 = gameDll + 0x4EFB0;
	//{0x30F1C2,safeClick::SendActionHook,5,nullptr}
	PlantDetourCall((BYTE*)gameDll + 0x30F1C2, (BYTE*)SendActionHook, 5);
}

bool safeClick::CUnit::IsVisibleToPlayer(int nPlayerIndex)
{
	return CUnit_IsUnitVisible(this, nPlayerIndex, 0, 4);
}
