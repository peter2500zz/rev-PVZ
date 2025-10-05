#include "pch.h"
#include "hook.h"

#include "graphics.h"

#include "coin.h"
#include "lawn_app.h"
#include "plant.h"
#include "widget_manager.h"
#include "zombie.h"


namespace
{
	// 僵尸绘制
	MID_HOOK post_zombie_draw_origin = nullptr;

	void __stdcall post_zombie_draw(Zombie* zombie, Graphics* g)
	{
		// 在Rust版本里必须要创建新的克隆才能正常绘制
		// C++这里不知道为什么不需要
		//Graphics* g_1 = graphics::Create(g);

		// 攻击判定
		Color green = color::green();
		graphics::SetColor(g, green);
		graphics::DrawRect(g, zombie->atk_x, zombie->atk_y, zombie->atk_w, zombie->atk_h);
		green.a = 0xFF / 8;
		graphics::SetColor(g, green);
		graphics::FillRect(g, zombie->atk_x, zombie->atk_y, zombie->atk_w, zombie->atk_h);
		// 碰撞箱
		graphics::SetColor(g, color::red());
		graphics::DrawRect(g, zombie->hit_x, zombie->hit_y, zombie->hit_w, zombie->hit_h);

		graphics::SetFont(g, *reinterpret_cast<Font**>(0x006A7224));

		graphics::SetColor(g, color::cyan());

		std::string attr;

		attr.append("[ ");
		attr.append(std::to_string(zombie->zombie_type));
		attr.append(" ] ");
		attr.append("state: ");
		attr.append(std::to_string(zombie->born_wave_or_stand));

		graphics::DrawStringWordWrapped(g, 0, 0, attr);

		std::string hp = "[ 0 ] ";

		hp.append(std::to_string(zombie->hp));
		hp.append("/");
		hp.append(std::to_string(zombie->hp_max));

		uint32_t height = 0;
		graphics::SetColor(g, color::invisible());
		height += graphics::DrawStringWordWrapped(g, 0, zombie->hit_y + zombie->hit_h, hp);

		graphics::SetColor(g, color::red());
		height += graphics::DrawStringWordWrapped(g, 0, zombie->hit_y + zombie->hit_h + height, hp);

		if (zombie->acc1_hp_max)
		{
			std::string acc1_hp = "[ 1 ] ";

			acc1_hp.append(std::to_string(zombie->acc1_hp));
			acc1_hp.append("/");
			acc1_hp.append(std::to_string(zombie->acc1_hp_max));

			height += graphics::DrawStringWordWrapped(g, 0, zombie->hit_y + zombie->hit_h + height, acc1_hp);
		}

		if (zombie->acc2_hp_max)
		{
			std::string acc2_hp = "[ 2 ] ";

			acc2_hp.append(std::to_string(zombie->acc2_hp));
			acc2_hp.append("/");
			acc2_hp.append(std::to_string(zombie->acc2_hp_max));

			height += graphics::DrawStringWordWrapped(g, 0, zombie->hit_y + zombie->hit_h + height, acc2_hp);
		}

		//graphics::DrawLine(g, 0, 0, zombie->hit_x, zombie->hit_y);

		// 如果克隆了记得清理
		//graphics::destructor(g_1);
	}

	__declspec(naked) void post_zombie_draw_helper()
	{
		__asm {
			push ebp
			push ebx
			call post_zombie_draw

			jmp post_zombie_draw_origin
		}
	}

	// 掉落物绘制
	MID_HOOK pre_coin_draw_origin = nullptr;

	void __stdcall pre_coin_draw(Coin* coin, Graphics* g)
	{
		if (!coin->collected )
		{
			graphics::SetColor(g, color::yellow());

			auto [w, h] = lawn_app::window_size(theLawnApp);
			auto [mx, my] = widget_manager::mouse_pos(theWidgetManager);

			uint32_t x = static_cast<uint32_t>(coin->x) + (coin->hitbox_width / 2);
			uint32_t y = static_cast<uint32_t>(coin->y) + (coin->hitbox_height / 2);

			if (x >= w) mx = w - 1;
			if (mx >= w) x = w - 1;
			if (y >= h) y = h - 1;
			if (my >= h) my = h - 1;

			graphics::DrawLine(
				g, 
				x,
				y,
				mx,
				my
			);
		}
	}

	__declspec(naked) void pre_coin_draw_helper()
	{
		__asm {
			push[esp + 4]
			push ebp
			call pre_coin_draw

			jmp pre_coin_draw_origin
		}
	}


	MID_HOOK post_coin_draw_origin = nullptr;

	void __stdcall post_coin_draw(Coin* coin, Graphics* g)
	{
		graphics::SetColor(g, color::yellow());
		graphics::DrawRect(g, static_cast<uint32_t>(coin->x), static_cast<uint32_t>(coin->y), coin->hitbox_width, coin->hitbox_height);
	}

	__declspec(naked) void post_coin_draw_helper() {
		__asm {
			push ecx

			push [esp + 4]
			push ebp
			call post_coin_draw

			pop ecx

			jmp post_coin_draw_origin
		}
	}

	MID_HOOK post_plant_draw_origin = nullptr;

	void __stdcall post_plant_draw(Plant* plant, Graphics* g)
	{
		// 受击区域
		graphics::SetColor(g, color::red());
		graphics::DrawRect(g, 0, 0, plant->hurt_w, plant->hurt_h);

		graphics::SetFont(g, *reinterpret_cast<Font**>(0x006A7224));

		graphics::SetColor(g, color::cyan());

		std::string attr;

		attr.append("[ ");
		attr.append(std::to_string(plant->plant_type));
		attr.append(" ] ");
		attr.append("cool: ");
		attr.append(std::to_string(plant->fire_or_produce_cd));

		graphics::DrawStringWordWrapped(g, 0, 0, attr);

		std::string hp;

		hp.append(std::to_string(plant->hp));
		hp.append("/");
		hp.append(std::to_string(plant->hp_max));

		graphics::SetColor(g, color::invisible());
		uint32_t height = graphics::DrawStringWordWrapped(g, 0, plant->hurt_h, hp);
		graphics::SetColor(g, color::red());
		graphics::DrawStringWordWrapped(g, 0, plant->hurt_h + height, hp);
	}

	__declspec(naked) void post_plant_draw_helper()
	{
		__asm {
			push eax

			push [ebp + 0xC]
			push ebx
			call post_plant_draw

			pop eax

			jmp post_plant_draw_origin
		}
	}
}

void draw::hook()
{
	// 僵尸绘制
	MH_CreateHook(
		POST_ZOMBIE_DRAW,
		&post_zombie_draw_helper,
		reinterpret_cast<LPVOID*>(&post_zombie_draw_origin)
	);
	MH_EnableHook(POST_ZOMBIE_DRAW);

	// 掉落物绘制
	MH_CreateHook(
		PRE_COIN_DRAW,
		&pre_coin_draw_helper,
		reinterpret_cast<LPVOID*>(&pre_coin_draw_origin)
	);
	MH_EnableHook(PRE_COIN_DRAW);

	MH_CreateHook(
		POST_COIN_DRAW,
		&post_coin_draw_helper,
		reinterpret_cast<LPVOID*>(&post_coin_draw_origin)
	);
	MH_EnableHook(POST_COIN_DRAW);

	// 植物绘制
	MH_CreateHook(
		POST_PLANT_DRAW,
		&post_plant_draw_helper,
		reinterpret_cast<LPVOID*>(&post_plant_draw_origin)
	);
	MH_EnableHook(POST_PLANT_DRAW);
}
