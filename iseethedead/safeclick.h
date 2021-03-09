#pragma once

#include "pch.h"
namespace safeClick {
	class CUnit {
		BYTE _0[0xC];
		DWORD m_dwId1;
		DWORD m_dwId2;

	public:
		DWORD GetId1() {
			return m_dwId1;
		}
		DWORD GetId2() {
			return m_dwId2;
		}

		bool IsVisibleToPlayer(int nPlayerIndex);
	};

	class CAction {
		void* vft;
		BYTE* pbData;

	public:
		BYTE* GetData() {
			return pbData;
		}
	};

	struct SelectionAction_t {
		BYTE bOpCode;
		BYTE bMode;
		WORD wCount;
		DWORD dwUnitIds[12][2];
	};

	struct SelectionActionItem_t {
		BYTE bOpCode;
		BYTE bMode;
		WORD id1;
		WORD gap;
		WORD id2;
	};

	typedef bool(__thiscall* CUnit_IsUnitVisible_t)(CUnit*, DWORD, DWORD, DWORD);

	bool __stdcall SendActionHandler(CAction* lpAction);
	void SendActionHook();
	void init();
}