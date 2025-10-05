#pragma once
#include "board.h"
#include "widget_manager.h"

struct LawnApp;

inline LawnApp* theLawnApp = nullptr;

namespace lawn_app
{
	// 我自己实现的函数
	inline LawnApp* from_base_address(uintptr_t base_address)
	{
		return *reinterpret_cast<LawnApp**>(base_address);
	}

	inline Board* get_Board(LawnApp* lawn_app)
	{
		return *reinterpret_cast<Board**>(reinterpret_cast<uintptr_t>(lawn_app) + 0x768);
	}

	inline WidgetManager* get_WidgetManager(LawnApp* lawn_app)
	{
		return *reinterpret_cast<WidgetManager**>(reinterpret_cast<uintptr_t>(lawn_app) + 0x320);
	}

	inline std::pair<uint32_t, uint32_t> window_size(LawnApp* lawn_app)
	{
		uint32_t w = *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(lawn_app) + 0xC0);
		uint32_t h = *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(lawn_app) + 0xC4);

		return { w, h };
	}
}
