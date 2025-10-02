#pragma once

struct WidgetManager;

inline WidgetManager* theWidgetManager = nullptr;

namespace widget_manager
{
	// 我自己实现的函数
	inline std::pair<uint32_t, uint32_t> mouse_pos(WidgetManager* wm)
	{
		uint32_t x = *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(wm) + 0xE0);
		uint32_t y = *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(wm) + 0xE4);

		return { x, y };
	}
}
