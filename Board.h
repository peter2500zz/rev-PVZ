#pragma once
#include "coin.h"

struct Board;

namespace board {
	// 我自己实现的函数
	uint32_t* get_sun(Board* board);

	// 实现的自带函数
	Coin* AddCoin(Board* board, uint32_t x, uint32_t y, CoinType coin_type, CoinMotion coin_motion);
}
