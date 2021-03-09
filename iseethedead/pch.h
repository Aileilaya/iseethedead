// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H
#pragma comment(lib,"detours.lib")

//#define LIMITED
#include "spdlog/sinks/basic_file_sink.h"
extern std::shared_ptr<spdlog::logger> logger;
extern unsigned int gameDll;
extern unsigned int localplayer;
extern unsigned int localplayerslot;
extern unsigned int hIsee;
extern HWND hWnd;
// 添加要在此处预编译的标头
#include <stdlib.h>
#include <stdint.h>
#include <Windows.h>    
#include <memory>
#include <unordered_map>
#include "player.h"
#include "detours.h"
#include "jassString.h"
#include "framework.h"
#include "tools.h"
#include "Jass.h"
#include "memedit.h"
#include "string.h"
#endif //PCH_H