#pragma once
#include "pch.h"
struct UnitSelectionModifyObjects {
	unsigned int ObjectID1;
	unsigned int ObjectID2;
};

struct UnitSelectionModify {
	unsigned int vtable;
	uint8_t unk_1[17];
	uint8_t playerNumber;
	uint8_t unk_2[2];
	uint8_t type;  //1 = select 2 = deselect
	uint8_t unk_3[3];
	unsigned int unitCount[2];
	UnitSelectionModifyObjects* selectedUnits;
};

struct SelectableSelectionModify {
	unsigned int vtable;
	uint8_t unk_1[17];
	uint8_t playerNumber;
	uint8_t unk_2[2];
	uint8_t type;                         // always 4
	uint8_t unk_3[3];
	UnitSelectionModifyObjects selectedSelectable;
};

struct ObjectId {
	unsigned int ObjectID1;
	unsigned int ObjectID2;
};

struct ddd {
	unsigned int unk0[3];
	ObjectId unknown1;
	unsigned int unk1[4];
	unsigned int orderId;
	unsigned int playerId;
	unsigned int unk2[7];
	float x;
	unsigned int unk3;
	float y;
	unsigned int unk4;
	ObjectId targetObject;
};

namespace mhDetect {
	typedef  void(__fastcall* OnDispatchUnitSelectionModify)(UnitSelectionModify* command);
	typedef  void(__fastcall* OnDispatchSelectableSelectionModify)(SelectableSelectionModify* command);
	typedef  void(__fastcall* OnPlayerOrder)(void* triggerUnit, ddd* d, unsigned int dwZero1, unsigned int dwZero2);

	inline float GetUnitX(void* unit);
	inline float GetUnitY(void* unit);
	void testSelection(unsigned int objId1, unsigned int objId2, UnitSelectionModify* command);
	void __fastcall HookOnDispatchUnitSelectionModify(UnitSelectionModify* command);
	void __fastcall HookOnDispatchSelectableSelectionModify(SelectableSelectionModify* command);

	void DetectImpossibleOrder(ddd* d, uint32_t targetObject, unsigned int eventOwner);
	void __fastcall HookOnPlayerOrder(void* triggerUnit, ddd* d, unsigned int dwZero1, unsigned int dwZero2);
	void init();

	enum Cmd
	{
		SMART = 0xD0002,
		MOVE = 0xD0003,	//移动
		ATTACK = 0xD000F,	//攻击
		HOLD = 0xD0019,	//停止 H
		STOP = 0xD0004,	//停止 S
		ITEM1 = 0xD0028, //物品1
		ITEM2 = 0xD0029, //物品2
		ITEM3 = 0xD002A, //物品3
		ITEM4 = 0xD002B, //物品4
		ITEM5 = 0xD002C, //物品5
		ITEM6 = 0xD002D, //物品6
		PATROL = 0xD0016 //巡逻
	};
}