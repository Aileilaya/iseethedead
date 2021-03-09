#pragma once
#include <unordered_map>
#include <memory>
#include <vector>
/*
	draw mini map at 3BA960
*/
struct UnitLine {
	uint32_t unitHandle;
	void* targetUnit = nullptr;
	int x, y;
	float fx, fy;
	unsigned int color;
};

struct Unit {
	unsigned int character;
	unsigned int color;
};
struct MmapLoc
{
	int X, Y;
};

struct Loc
{
	float x, y;
	float unk = 1.0;
};

class MiniMapHack final {
private:
	std::unordered_map<void*, UnitLine> lines;
	std::unordered_map<void*, Unit> units;
	std::unordered_map<int, bool> restore;
	uint32_t* miniMapBackup = nullptr;
	uint32_t* gameMiniMap = nullptr;
	float xMult = 0, yMult = 0, unk = 0;
	int unk2 = 0, unk3 = 0;
	int minX = 0, minY = 0, maxX = 0, maxY = 0;
	MmapLoc LocationToMinimap(float x, float y);
	void draw_line(void* unit, UnitLine& obj);
	uint32_t CoordToMinimap(float Loc, DWORD offst);
	void draw_line(int x0, int y0, int x1, int y1, uint32_t c);
	void draw_unit(void*, Unit&);
	void DrawPixel(int x, int y, uint32_t color);
	void ConvertMmap(MmapLoc& loc);
	void Refresh();
	void CalMiniMapLoc(const Loc& main, Loc& mini);
	void RestorMiniMap();
	static signed int* ConvertCoord1(signed int* a1, signed int* a2, DWORD* a3);
	static uint32_t ConvertCoord2(int*);
public:
	static void DetourUpdateMiniMap();
	typedef void(__fastcall* convert1)(float*, float*, uint32_t);
	typedef uint32_t(__fastcall* convert2)(int*);
	MiniMapHack();
	~MiniMapHack();
	void addLine(void* unit, float x, float y, unsigned int color);
	void addLine(void* unit, void* targetUnit, unsigned int color);
	void delLine(void* unit);
	void addUnit(void* unit, unsigned int cha, unsigned int color);
	void delUnit(void* unit);
	void Clear();
	void DrawMiniMap();
};