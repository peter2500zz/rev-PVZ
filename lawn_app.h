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
}
