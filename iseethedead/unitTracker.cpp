#include "pch.h"
#include "unitTracker.h"
#include "player.h"
#include <list>
std::unordered_map<unsigned int, std::shared_ptr<W3unit>> unitTrack::allunits;
std::list<unitTrack::UnitCreationEvent> unitTrack::onUnitGenQueue;
UnitConstructor uc;
UnitDestructor ud;

void unitTrack::hook()
{
	uc = (UnitConstructor)(gameDll + 0x663810);
	ud = (UnitDestructor)(gameDll + 0x66ABB0);

	int error = DetourTransactionBegin();
	if (error == NO_ERROR)
	{
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)uc, &processUnitCreate);
		//DetourAttach(&(PVOID&)ud, &processUnitDestory);
		DetourTransactionCommit();
	}
}

unsigned int unitTrack::processUnitCreate()
{
	unsigned int unit = uc();
	__try {

		if (IsGameObjectPresent()) {
			UnitCreationEvent a;
			a.tickCount64 = GetTickCount64();
			a.unitAddr = unit;
			onUnitGenQueue.push_back(a);
		}
	}
	__except (filter(GetExceptionCode(), GetExceptionInformation())) {
		logger->warn("unitTrack::processUnitCreate crashed");
	}

	return unit;
}

void __fastcall unitTrack::processUnitDestory(unsigned int unit)
{
	allunits.erase(unit);
	ud(unit);
}

extern gamePlayerInfo* aPlayerInfo;
bool unitTrack::addNewUnit(unsigned int handle, unsigned int object) {
	unsigned int character = 0;
	if (!jass::IsUnitAlly(handle, jass::GetLocalPlayer())) {
		character += 4;
	}
	if (jass::IsUnitHero(handle)) {
		character += 1;
	}
	if (character == 1 || character == 5) {
		if (allunits.find(handle) == allunits.end()) {
			//原来没有这个单位
			allunits[handle] = std::make_shared<W3unit>(handle, object, character);
		}
		else {
			//原来有 先删除旧的
			allunits.erase(handle);
			allunits[handle] = std::make_shared<W3unit>(handle, object, character);
		}
	}
	return true;
}

void CALLBACK unitTrack::processUnitCreationEvent() {
	for (std::list<UnitCreationEvent>::iterator it = onUnitGenQueue.begin(); it != onUnitGenQueue.end();)
	{
		UnitCreationEvent a = *it;
		if (a.visitCount > 10) {
			onUnitGenQueue.erase(it++);
			continue;
		}
		else {
			a.visitCount++;
			unsigned int handle = ObjectToHandle((void*)a.unitAddr);
			if (handle && addNewUnit(handle, a.unitAddr)) {
				onUnitGenQueue.erase(it++);
			}
			else {
				it++;
			}
		}
	}
}