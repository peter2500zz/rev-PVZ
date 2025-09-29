// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "dllmain.h"

#include "board.h"


BOOL APIENTRY DllMain(
    HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        at_attach();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

// 目标函数签名
typedef void (__thiscall *TargetFn)(void*, int);

// 原函数指针
static TargetFn gOriginal = nullptr;

/// 按下按键前的钩子
/// @param _this 类
/// @param edx 使用fastcall代替thiscall的占位符
/// @param keycode 按下按键的键码
void __fastcall hook_func(void* _this, void* edx, int keycode)
{
    uintptr_t p0 = *reinterpret_cast<uintptr_t*>(0x6A9EC0);
    Board board = *reinterpret_cast<Board*>(p0 + 0x768);

    DWORD* sun = board::get_sun(board);

	switch (keycode)
	{
	case 65:
        debug(fmt::format(L"{}", *sun).c_str());
        break;

    default:
        break;
	}

    *sun = 100;

    gOriginal(_this, keycode);
}

void at_attach()
{
    if (MH_Initialize() == MH_OK)
    {
        LPVOID target = reinterpret_cast<LPVOID>(0x41B820);

        MH_CreateHook(
            target,
            &hook_func,
            reinterpret_cast<LPVOID*>(&gOriginal)
        );
        MH_EnableHook(target);
    }

    // 如果窗口出来了这里大概是拿得到句柄的
    HWND hwnd = FindWindowA(nullptr, "Plants vs. Zombies");

    if (hwnd != nullptr) {
        // LOL
        SetWindowTextA(hwnd, "Plants vs. Zombies (hooked)");
    }

    // 管你这那的叫一声再说
    MessageBeep(MB_ICONINFORMATION);
}


