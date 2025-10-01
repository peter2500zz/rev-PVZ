#include "pch.h"
#include "board.h"

uint32_t* board::get_sun(Board* board) {
	return reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(board) + 0x5560);
}

Zombie* board::alloc_zombie(Board* board)
{
	DWORD* zombie_array = reinterpret_cast<DWORD*>(reinterpret_cast<uintptr_t>(board) + 0x90);

	Zombie* aZombie;

	__asm {
		push esi

		mov esi, zombie_array

		mov edx, 0x0041DDA0
		call edx

		mov aZombie, eax

		pop esi
	}

	return aZombie;
}


Coin* board::AddCoin(Board* board, uint32_t x, uint32_t y, CoinType coin_type, CoinMotion coin_motion) {
	using AddCoin = Coin * (__thiscall*)(Board* board, uint32_t x, uint32_t y, CoinType coin_type, CoinMotion coin_motion);

	AddCoin fn = reinterpret_cast<AddCoin>(0x0040CB10);

	return fn(board, x, y, coin_type, coin_motion);
}

uint32_t board::PixelToGridXKeepOnBoard(Board* board, uint32_t theX, uint32_t theY)
{
	uint32_t aGridX;

	__asm {
		push ebx
		push esi

		mov ebx, board
		mov esi, theX
		mov eax, theY

		mov edx, 0x0041C530
		call edx

		mov aGridX, eax

		pop esi
		pop ebx
	}

	return aGridX;
}

uint32_t board::PixelToGridYKeepOnBoard(Board* board, uint32_t theX, uint32_t theY)
{
	uint32_t aGridY;

	__asm {
		push ebx
		push edi

		mov ebx, board
		mov edi, theY
		mov eax, theX

		mov edx, 0x0041C650
		call edx
		mov aGridY, eax

		pop edi
		pop ebx
	}

	return aGridY;
}

