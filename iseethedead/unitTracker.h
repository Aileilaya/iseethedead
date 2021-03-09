#pragma once
#include "unit.h"
#include <unordered_map>
typedef unsigned int (*UnitConstructor)();
typedef void (__fastcall *UnitDestructor)(unsigned int);

namespace unitTrack {
	struct UnitCreationEvent {
		uint64_t tickCount64 = 0;
		unsigned int unitAddr = 0;
		unsigned int visitCount = 0;
	};
	extern std::unordered_map<unsigned int, std::shared_ptr<W3unit>> allunits;
	extern std::list<unitTrack::UnitCreationEvent> onUnitGenQueue;
	void hook();
	bool addNewUnit(unsigned int handle, unsigned int object);
	unsigned int processUnitCreate();
	void __fastcall processUnitDestory(unsigned int unit);
	void __stdcall processUnitCreationEvent();
}