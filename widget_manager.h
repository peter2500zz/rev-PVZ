#pragma once

struct WidgetManager;

namespace widget_manager
{
	// 我自己实现的函数
	std::pair<uint32_t, uint32_t> mouse_pos(WidgetManager* wm);
}
