#pragma once
#include "pch.h"
#include <string>

class W3unit {
public:
	W3unit(unsigned int handle, unsigned int object, int cha);
	static bool __stdcall IsUnitDetected(int unit);
	unsigned int getHandle() { return jass_handle; };
	void refreshTag();
	void minimapIndicate();
	~W3unit();
	float GetUnitX() {
		return *(float*)(this->addr + 0x284);
	};
	float GetUnitY() {
		return *(float*)(this->addr + 0x288);
	};
private:
	unsigned int jass_handle;
	unsigned int addr;
	unsigned int owning_player;
	unsigned int owning_player_slot;
	unsigned int jass_tag;
	std::string name;
	std::unique_ptr<jassString> jStr;
	int character;
	bool isTagShown = false;
	void toggleTag(bool on = true)
	{
		if (on != this->isTagShown) {
			jass::SetTextTagVisibility(this->jass_tag, on);
			this->isTagShown = on;
		}
	}
};