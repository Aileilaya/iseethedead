#pragma once
#pragma comment(lib,"Version.lib")

unsigned int WarcraftVersion();
bool IsGameObjectPresent();
unsigned int ObjectToHandle(void*);
void PlantDetourCall(BYTE* , BYTE* , size_t );
bool IsInGame();
void DisplayText(const char* , float fDuration = 16.0f);
const char* ConvertOrderId(unsigned int);
uint32_t GetPlayerColorHEX(unsigned int c);
int filter(unsigned int code, struct _EXCEPTION_POINTERS* ep);
void HideLDRTable(HMODULE module);
bool FilterOrderId(unsigned int orderId);
#define CHAT_RECIPIENT_ALL			0
#define CHAT_RECIPIENT_ALLIES		1
#define CHAT_RECIPIENT_OBSERVERS	2
#define CHAT_RECIPIENT_PRIVATE		3

void DisplayChatMessage(const char* msg, float duration = 60.0f, unsigned int PlayerSlot = PlayerLocal(), unsigned int chattype = CHAT_RECIPIENT_OBSERVERS);
bool PostChatMessage(const char* msg, float duration = 60.0f, unsigned int PlayerSlot = PlayerLocal(), unsigned int chattype = CHAT_RECIPIENT_OBSERVERS);