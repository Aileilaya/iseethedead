#pragma once
#include<memory>

namespace memedit {
	struct PatchInfo {
		unsigned int addr, size;
		const char* content;
		std::unique_ptr<char[]> backup;
	};
	
	void Patch(void* dwBaseAddress, const char* szData, size_t iSize);
	void applyPatch();
	void applyDetour();
	void rollBack();
	void showMoveSpeed();
	void showAttackSpeed();
	void getHpRegen();
	void getMpRegen();
	void hookShowHeroStatus();
	void hpBarHook();
	void colorInvisibles();
}