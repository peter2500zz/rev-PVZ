#pragma once
#include "coin.h"
#include "zombie.h"

struct Board;

inline Board* theBoard = nullptr;

namespace board
{
	// 我自己实现的函数

	/// 获取当前关卡的阳光
	/// @param board 当前关卡
	/// @return 阳光指针
	inline uint32_t* get_sun(Board* board)
	{
		return reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(board) + 0x5560);
	}

	/// <summary>
	/// 在僵尸数组中分配一个僵尸\n
	/// 不会初始化僵尸
	/// </summary>
	/// <param name="board">当前关卡</param>
	/// <returns>僵尸实例</returns>
	inline Zombie* alloc_zombie(Board* board)
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

	// 实现的自带函数
	inline Coin* AddCoin(Board* board, uint32_t x, uint32_t y, CoinType coin_type, CoinMotion coin_motion)
	{
		using AddCoin = Coin * (__thiscall*)(Board* board, uint32_t x, uint32_t y, CoinType coin_type, CoinMotion coin_motion);

		AddCoin fn = reinterpret_cast<AddCoin>(0x0040CB10);

		return fn(board, x, y, coin_type, coin_motion);
	}

	inline uint32_t PixelToGridXKeepOnBoard(Board* board, uint32_t theX, uint32_t theY)
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

	inline uint32_t PixelToGridYKeepOnBoard(Board* board, uint32_t theX, uint32_t theY)
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
}
