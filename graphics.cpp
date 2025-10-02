#include "pch.h"
#include "hook.h"

#include "graphics.h"
#include "zombie.h"


namespace
{
	// 僵尸绘制
	static MID_HOOK post_zombie_draw_origin = nullptr;

	void __stdcall post_zombie_draw(Zombie* zombie, Graphics* g)
	{
		// 在Rust版本里必须要创建新的克隆才能正常绘制
		// C++这里不知道为什么不需要
		//Graphics* g_1 = graphics::Create(g);

		uint32_t* x = zombie::get_hit_x(zombie);
		uint32_t* y = zombie::get_hit_y(zombie);
		uint32_t* w = zombie::get_hit_w(zombie);
		uint32_t* h = zombie::get_hit_h(zombie);

		graphics::SetColor(g, color::red());
		graphics::DrawRect(g, *x, *y, *w, *h);
		graphics::DrawLine(g, 0, 0, *x, *y);

		// 如果克隆了记得清理
		//graphics::destructor(g_1);
	}

	__declspec(naked) void post_hook_helper()
	{
		__asm {
			push ebp
			push ebx
			call post_zombie_draw

			jmp post_zombie_draw_origin
		}
	}

}

void draw::hook()
{
	// POST僵尸绘制
	MH_CreateHook(
		POST_ZOMBIE_DRAW,
		&post_hook_helper,
		reinterpret_cast<LPVOID*>(&post_zombie_draw_origin)
	);
	MH_EnableHook(POST_ZOMBIE_DRAW);
}
