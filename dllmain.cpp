// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "dllmain.h"

#include "board.h"
#include "graphics.h"
#include "lawn_app.h"


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
using TargetFn = void(__thiscall*)(Board* board, int keycode);

// 原函数指针
static TargetFn gOriginal = nullptr;

/// 按下按键前的钩子
/// @param _this 类
/// @param edx 使用fastcall代替thiscall的占位符
/// @param keycode 按下按键的键码
void __fastcall hook_func(Board* board, void* edx, int keycode)
{
	LawnApp* app = lawn_app::from_base_address(0x6A9EC0);
	WidgetManager* wm = lawn_app::get_widget_manager(app);
	//Board* board = lawn_app::get_board(app);

	auto [x, y] = widget_manager::mouse_pos(wm);

	uint32_t grid_x = board::PixelToGridXKeepOnBoard(board, x, y);
	uint32_t grid_y = board::PixelToGridYKeepOnBoard(board, x, y);

	switch (keycode)
	{
		// A
	case 65:
	{
		Coin* coin = board::AddCoin(board, x, y, CoinType::Sun, CoinMotion::CollectImmediately);

		break;
	}
	case 90:
	{
		Zombie* zombie = board::alloc_zombie(board);
		zombie::ZombieInitialize(zombie, grid_y, ZombieType::ZOMBIE_NORMAL, false, nullptr, 0);
		zombie::RiseFromGrave(zombie, grid_x, grid_y);

		//debug(fmt::format(L"hitx:{} hity:{} hitw:{} hith:{}", *zombie::get_hit_x(zombie), *zombie::get_hit_y(zombie), *zombie::get_hit_w(zombie), *zombie::get_hit_h(zombie)).c_str());

		break;
	}
	default:
	{
		debug(fmt::format(L"Pressed keycode: {}", keycode).c_str());
		break;
	}
	}

	//*sun = 100;

	gOriginal(board, keycode);
}

using post_draw_zombie = void (*)();

static post_draw_zombie gpost_draw_zombie = nullptr;

void __stdcall helper(Zombie* zombie, Graphics* g)
{
	//Graphics* g_1 = graphics::Create(g);

	uint32_t* x = zombie::get_hit_x(zombie);
	uint32_t* y = zombie::get_hit_y(zombie);
	uint32_t* w = zombie::get_hit_w(zombie);
	uint32_t* h = zombie::get_hit_h(zombie);

	graphics::SetColor(g, color::red());
	graphics::DrawRect(g, *x, *y, *w, *h);
	graphics::DrawLine(g, 0, 0, *x, *y);

	//graphics::destructor(g_1);
}

__declspec(naked) void hf()
{
	__asm {
		pushad
		pushfd

		push ebp
		push ebx
		call helper

		popfd
		popad

		jmp gpost_draw_zombie
	}
}

/// <summary>
/// 当DLL成功附加到程序上的时候就会触发这个函数
/// </summary>
void at_attach()
{
	if (MH_Initialize() == MH_OK)
	{
		LPVOID target = reinterpret_cast<LPVOID>(0x0041B820);

		MH_CreateHook(
			target,
			&hook_func,
			reinterpret_cast<LPVOID*>(&gOriginal)
		);
		MH_EnableHook(target);

		LPVOID draw_zombie = reinterpret_cast<LPVOID>(0x0052E49F);

		MH_CreateHook(
			draw_zombie,
			hf,
			reinterpret_cast<LPVOID*>(&gpost_draw_zombie)
		);
		MH_EnableHook(draw_zombie);
	}

	// 如果窗口出来了这里大概是拿得到句柄的
	HWND hwnd = FindWindowA(nullptr, "Plants vs. Zombies");

	if (hwnd != nullptr)
	{
		// LOL
		SetWindowTextA(hwnd, "Plants vs. Zombies (hooked)");
	}

	// 管你这那的叫一声再说
	MessageBeep(MB_ICONINFORMATION);
}


