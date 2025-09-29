// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "dllmain.h"

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

// 目标函数真实签名（务必匹配！）
using TargetFn = char(*)(int, int, int);
// 原函数指针
static TargetFn gOriginal = nullptr;


__declspec(naked) void hook_func()
{
	__asm {
		//push ebp        // 保存基址指针
		//mov ebp, esp    // 设置新的栈帧
		// 保存可能被修改的非易失寄存器

        // 减半阳光消耗
        shr ebx, 1

        // theAmount
		push ebx
        // this
		push edi

		call gOriginal

		// 恢复寄存器
		pop edi
		pop ebx

		//leave
		ret
	}
}



void at_attach()
{
    if (MH_Initialize() == MH_OK)
    {
        LPVOID target = reinterpret_cast<LPVOID>(0x0041BA60);

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


