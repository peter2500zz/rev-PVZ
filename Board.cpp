#include "pch.h"
#include "board.h"

uint32_t* board::get_sun(Board* board) {
	return reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(board) + 0x5560);
}


Coin* board::AddCoin(Board* board, uint32_t x, uint32_t y, CoinType coin_type, CoinMotion coin_motion) {
	using AddCoin = Coin * (__thiscall*)(Board* board, uint32_t x, uint32_t y, CoinType coin_type, CoinMotion coin_motion);

	AddCoin fn = reinterpret_cast<AddCoin>(0x40CB10);

	return fn(board, x, y, coin_type, coin_motion);
}

