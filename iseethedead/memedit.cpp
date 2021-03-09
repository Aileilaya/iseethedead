#include "pch.h"
#include "memedit.h"
#include "icome.h"
#include "player.h"
#include "unit.h"
/*
Game.dll + 0x1BFF01 mainmap show model
Game.dll + 0x1C0053 item
Game.dll + 0x1F7C23 ? SetUnitVertexColor
Game.dll + 0x1FB323 ?
Game.dll + 0x2339B3 ?
Game.dll + 0x251268 ping
Game.dll + 0x370A36 inv
Game.dll + 0x392818 skill
Game.dll + 0x392858 skill
Game.dll + 0x3A5835 Resource
Game.dll + 0x3A9940 trade?
Game.dll + 0x3AA9F6 ?
Game.dll + 0x3AAA23 Resource
Game.dll + 0x3B8C42 minimap
Game.dll + 0x3B947A minimap share vision
Game.dll + 0x3BD7C2 Minimap
Game.dll + 0x40BFFB ?
Game.dll + 0x47EE5E SKILL
Game.dll + 0x5E179D skill
Game.dll + 0x65168B Click
Game.dll + 0x651694 Minimap?
Game.dll + 0x66E44B Illusions1
Game.dll + 0x66E71E SKILL
Game.dll + 0x740420 fog
*/
memedit::PatchInfo p[] = {
	//MainMap
	{0x1BFEE5,1,"\xEB",nullptr},
	//{0x3709F8,3,"\xFE\xC0\x90",nullptr},
	//{0x1BFF01,1,"\xEB",nullptr},
	//Invisible
	{0x370AD3,1,"\xEB",nullptr},
	//Minimap
	/*
		3BDC35 special icon for heroes
	*/
	//{0x3BDBED,1,"\xE7",nullptr},
	{0x3BD7E5,2,"\x33\xC0",nullptr},
	//3BDBBD units 3BDC0A bulidings
	//
	/*
	{0x329B30,3,"\x33\xC0\xC3",nullptr},
	{0x335620,1,"\x00",nullptr},
	{0x335640,1,"\x00",nullptr},
	*/
	//Click unit
	{0x6516A3,1,"\xEB",nullptr},
	//Click item
	{0x1C0144,1,"\xEB",nullptr},
	//Items
	{0x1C0053,1,"\xEB",nullptr},
	//ping
	{0x251274,1,"\xFC",nullptr},
	{0x251287,1,"\xFC",nullptr},
	//Illusions
	{0x66E457,2,"\x40\xC3",nullptr},
	{0x5E20D1,1,"\xCC",nullptr},
	{0x47EE5E,1,"\x8C",nullptr},
	{0x66E71E,1,"\xEB",nullptr},
	{0x392818,2,"\x90\x90",nullptr},
	{0x392858,2,"\x90\x90",nullptr},
	//Resource Trade
	{0x3A5835,6,"\xB8\xC8\x00\x00\x00\x90",nullptr},
	{0x3A583D,6,"\xB8\xC8\x00\x00\x00\x90",nullptr},
	{0x3AAA23,2,"\x90\x90",nullptr},
	//Rescource View
	{0x3BEC40,2,"\x90\x90",nullptr},
	{0x3B0E33,2,"\x90\x90",nullptr},
	{0x3B1593,2,"\x90\x90",nullptr},
	{0x3B3993,2,"\x90\x90",nullptr},
	{0x67A599,2,"\x90\x90",nullptr},
	{0x3AAA17,1,"\xEB",nullptr},
#ifndef LIMITED
	//fps
	{0x3A49AC,2,"\x90\x90",nullptr},
	//Show Missile
	{0x36F670,2,"\x90\x90",nullptr},
	//Select Circle
	/*
		select		+73dddc
		deselect	+73ddf2
		refresh		+738dad
	*/
	{0x26FA72,1,"\xEB",nullptr},
	{0x26FA82,2,"\xEB\x02",nullptr},
	{0x26FA92,2,"\xEB\x02",nullptr},
	{0x67A450,12,"\x8B\x4D\x18\xE8\x48\xC2\xCA\xFF\x90\x90\x90\x90",nullptr},
	//patch issuetargetOrder
	//{0x1E96A0,3,"\x33\xc0\xc3",nullptr},
	//UnitRemoveItem
	//{0x1FB170,3,"\x33\xc0\xc3",nullptr},
	//IssueTargetOrderById
	//{0x1E96C0,3,"\x33\xc0\xc3",nullptr},
	//IssueNeutralImmediateOrder
	//{0x1E9080,3,"\x33\xc0\xc3",nullptr},
#endif
};
const unsigned int numberOfPatch = sizeof(p) / sizeof(memedit::PatchInfo);
static const char* MsFormat = "%.1f";
static const char* AsFormat = "%0.02f";
static const char* HpMpFormat = "%s\n|CFF00FF00%.02f|r |CFF00BFFF%.02f|r";
static unsigned int storm503, storm578;
static unsigned int sometable;
static float hpRegen, mpRegen;
static unsigned int colorUnit, colorInvisiblesCallJumpBack;

void memedit::Patch(void* dwBaseAddress, const char* szData, size_t iSize)
{
	if (szData == nullptr) return;
	DWORD dwOldProtection = NULL;
	VirtualProtect((LPVOID)dwBaseAddress, iSize, PAGE_EXECUTE_READWRITE, &dwOldProtection);
	memcpy_s(dwBaseAddress, iSize, szData, iSize);
	VirtualProtect((LPVOID)dwBaseAddress, iSize, dwOldProtection, NULL);
}

void memedit::applyPatch()
{
	for (unsigned int i = 0; i < numberOfPatch; i++) {
		p[i].backup = std::make_unique<char[]>(p[i].size);
		memcpy_s(p[i].backup.get(), p[i].size, (void*)(p[i].addr + gameDll), p[i].size);
		Patch((void*)(p[i].addr + gameDll), p[i].content, p[i].size);
	}
}

void memedit::rollBack() {
	for (unsigned int i = 0; i < numberOfPatch; i++) {
		Patch((void*)(p[i].addr + gameDll), p[i].backup.get(), p[i].size);
		p[i].backup = nullptr;
	}
}

void memedit::applyDetour()
{
	storm503 = gameDll + 0x12063A;
	storm578 = gameDll + 0x1205D4;
	sometable = gameDll + 0xBE40A8;
	colorUnit = gameDll + 0x186FC0;
	colorInvisiblesCallJumpBack = gameDll + 0x635FA0;
	PlantDetourCall((BYTE*)gameDll + 0x38D59A, (BYTE*)showMoveSpeed, 5);
	PlantDetourCall((BYTE*)gameDll + 0x38C83A, (BYTE*)showAttackSpeed, 5);
	PlantDetourCall((BYTE*)gameDll + 0x3BBD02, (BYTE*)getHpRegen, 6);
	PlantDetourCall((BYTE*)gameDll + 0x3BBE98, (BYTE*)getMpRegen, 6);
	PlantDetourCall((BYTE*)gameDll + 0x3B7DDC, (BYTE*)hookShowHeroStatus, 6);
	PlantDetourCall((BYTE*)gameDll + 0x3709C8, (BYTE*)colorInvisibles, 5);
	PlantDetourCall((BYTE*)gameDll + 0x3BD5B4, (BYTE*)hpBarHook, 5);
}

void __declspec(naked) memedit::showMoveSpeed()
{
	_asm
	{
		FLD  DWORD PTR SS : [ESP + 0x78]
		SUB  ESP, 8
		FSTP QWORD PTR SS : [ESP]
		PUSH MsFormat
		PUSH 16
		PUSH EAX
		CALL DWORD PTR DS : [storm578]
		ADD  ESP, 0x14
		JMP	DWORD PTR DS : [storm503]
	}
}

void __declspec(naked) memedit::showAttackSpeed()
{
	_asm
	{
		FLD  DWORD PTR SS : [ESP + 0x78]
		SUB  ESP, 8
		FSTP QWORD PTR SS : [ESP]
		PUSH AsFormat
		PUSH 16
		PUSH EAX
		CALL DWORD PTR DS : [storm578]
		ADD  ESP, 0x14
		JMP	DWORD PTR DS : [storm503]
	}
}

void __declspec(naked) memedit::getHpRegen()
{
	_asm {
		lea eax, ss: [ebp - 0xD8]
		push eax
		push ecx
		mov  ecx, dword ptr ds : [ecx + 0xa0]
		mov  eax, [sometable]
		mov  eax, [eax]
		mov  eax, dword ptr ds : [eax + 0x0c]
		mov  ecx, dword ptr ds : [ecx * 8 + eax + 4]
		mov  ecx, dword ptr ds : [ecx + 0x7c]
		mov  hpRegen, ecx
		pop  ecx
		pop  eax
		ret
	}
}

void __declspec(naked) memedit::getMpRegen()
{
	_asm {
		add ecx, 0xB8
		push eax
		push ecx
		mov  ecx, dword ptr ds : [ecx + 8]
		mov  eax, [sometable]
		mov  eax, [eax]
		mov  eax, dword ptr ds : [eax + 0x0c]
		mov  ecx, dword ptr ds : [ecx * 8 + eax + 4]
		mov  ecx, dword ptr ds : [ecx + 0x7c]
		mov  mpRegen, ecx
		pop  ecx
		pop  eax
		ret
	}
}

void __declspec(naked) memedit::hookShowHeroStatus()
{
	_asm {
		push ecx
		lea  ecx, [ebp - 0x44]
		fld  mpRegen
		fld  hpRegen
		sub  esp, 0x10
		fstp qword ptr ss : [esp]
		fstp qword ptr ss : [esp + 8]
		push ecx
		push HpMpFormat
		push 0x40
		push ecx
		CALL DWORD PTR DS : [storm578]
		add  esp, 0x20
		pop  ecx
		mov  esi, dword ptr ds : [ebx + 0x134]
		retn
	}
}

void __declspec(naked) memedit::hpBarHook()
{
	__asm
	{
		PUSH ECX
		//edi = ADDRESS OF UNIT
		//edx = vtable of object
		PUSH 4
		PUSH 0
		call PlayerLocal
		push eax
		MOV  EAX, DWORD PTR DS : [EDI]
		MOV  EAX, DWORD PTR DS : [EAX + 0xFC]
		MOV  ECX, EDI							//this call
		CALL EAX
		CMP  AL, 1
		POP ECX
		JE   next								//visible
		mov	 edx, dword ptr ss : [esp + 0x4]
		mov  dword ptr ds : [edx] , 0xFFC7C7C7
		jmp  epilogue
	next :
		mov edx, dword ptr ss : [esp + 0x4]
	epilogue :
		movzx eax, byte ptr ds : [edx + 0x3]
		mov byte ptr ds : [ecx + 0x68] , al
		movzx eax, byte ptr ds : [edx + 0x2]
		mov byte ptr ds : [ecx + 0x6B] , al
		movzx eax, byte ptr ds : [edx + 0x1]
		mov byte ptr ds : [ecx + 0x6A] , al
		movzx eax, byte ptr ds : [edx]
		mov byte ptr ds : [ecx + 0x69] , al
		mov eax, dword ptr ds : [ecx]
		call dword ptr ds : [eax + 0x24]
		ret 0x4
	}
}

void __declspec(naked) memedit::colorInvisibles()
{
	__asm
	{
		push eax
		MOV  AL, BYTE PTR DS : [EBX + 0x5F]
		CMP  AL, 1
		JNZ  Finish
		push ecx
		push edx
		PUSH EBX
		MOV  DWORD PTR DS : [ESP] , 0xFFFF0000
		MOV  ECX, DWORD PTR DS : [EBX + 0x28]
		XOR  EDX, EDX
		call dword ptr ds : [colorUnit]
		pop edx
		pop ecx
	Finish:
		pop eax
		jmp dword ptr ds : [colorInvisiblesCallJumpBack]
	}
}

