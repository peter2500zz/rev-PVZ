#include "pch.h"
#include "hook.h"


namespace at_window_show
{
	using post_func_sign = void (*)();
	post_func_sign post_func_origin = nullptr;

	void __fastcall post_window_show()
	{
		// 如果窗口出来了这里大概是拿得到句柄的
		HWND hwnd = FindWindowA(nullptr, "Plants vs. Zombies");

		if (hwnd != nullptr)
		{
			// LOL
			SetWindowTextA(hwnd, "Plants vs. Zombies (hooked)");
		}

		// 管你这那的叫一声再说
		MessageBeep(MB_ICONINFORMATION);

		post_func_origin();
	}


	void hook()
	{
		LPVOID post_window_show_point = reinterpret_cast<LPVOID>(0x0055230E);

		MH_CreateHook(
			post_window_show_point,
			&post_window_show,
			reinterpret_cast<LPVOID*>(&post_func_origin)
		);
		MH_EnableHook(post_window_show_point);
	}
}

void startup::hook()
{
	at_window_show::hook();
}


