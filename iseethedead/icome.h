#pragma once

namespace icome {
	extern bool isHackOn;
	void updateTag();
	bool firstBOOT();
	void ToggleMaphack(bool enable);
	void CALLBACK timer(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
	void icome();
	inline void traverseUnits();
}