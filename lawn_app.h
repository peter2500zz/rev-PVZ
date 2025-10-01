#pragma once
#include "board.h"
#include "widget_manager.h"

struct LawnApp;

namespace lawn_app
{
	// 我自己实现的函数
	LawnApp* from_base_address(uint32_t base_address);
	Board* get_board(LawnApp* lawn_app);
	WidgetManager* get_widget_manager(LawnApp* lawn_app);
}
