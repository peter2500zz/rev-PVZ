#include "pch.h"
#include "board.h"

DWORD* board::get_sun(Board board)
{
	return reinterpret_cast<DWORD*>(board + 0x5560);
}

