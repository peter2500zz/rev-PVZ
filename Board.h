#pragma once
#include "coin.h"
#include "zombie.h"

struct Board;

namespace board
{
	// 我自己实现的函数

	/// 获取当前关卡的阳光
	/// @param board 当前关卡
	/// @return 阳光指针
	uint32_t* get_sun(Board* board);

	/// <summary>
	/// 在僵尸数组中分配一个僵尸\n
	/// 不会初始化僵尸
	/// </summary>
	/// <param name="board">当前关卡</param>
	/// <returns>僵尸实例</returns>
	Zombie* alloc_zombie(Board* board);

	// 实现的自带函数
	Coin* AddCoin(Board* board, uint32_t x, uint32_t y, CoinType coin_type, CoinMotion coin_motion);
	uint32_t PixelToGridXKeepOnBoard(Board* board, uint32_t theX, uint32_t theY);
	uint32_t PixelToGridYKeepOnBoard(Board* board, uint32_t theX, uint32_t theY);
}
