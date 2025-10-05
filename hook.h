#pragma once

using MID_HOOK = void (*)();

// 生命周期相关
const LPVOID POST_LAWNAPP_CONSTRUCTOR = reinterpret_cast<LPVOID>(0x0044EDB6);
const LPVOID POST_LAWNAPP_DESTRUCTOR = reinterpret_cast<LPVOID>(0x0044F19C);
const LPVOID POST_WIDGETMANAGER_CONSTRUCTOR = reinterpret_cast<LPVOID>(0x005385D4);
const LPVOID POST_WIDGETMANAGER_DESTRUCTOR = reinterpret_cast<LPVOID>(0x00538650);
// 绘图相关
const LPVOID POST_ZOMBIE_DRAW = reinterpret_cast<LPVOID>(0x0052E49F);
const LPVOID PRE_COIN_DRAW = reinterpret_cast<LPVOID>(0x0043183C);
const LPVOID POST_COIN_DRAW = reinterpret_cast<LPVOID>(0x00431F0F);
const LPVOID POST_PLANT_DRAW = reinterpret_cast<LPVOID>(0x00466091);
const LPVOID POST_BOARD_DRAW = reinterpret_cast<LPVOID>(0x0041AE39);
// 控件相关
const LPVOID PRE_BOARD_KEYDOWN = reinterpret_cast<LPVOID>(0x0041B820);

namespace draw
{
	void hook();
}

namespace startup
{
	void hook();
}

namespace classlifetime
{
	void hook();
}
