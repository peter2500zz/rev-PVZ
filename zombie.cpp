#include "pch.h"
#include "zombie.h"


uint32_t* zombie::get_hit_x(Zombie* zombie)
{
	return reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(zombie) + 0x8C);
}

uint32_t* zombie::get_hit_y(Zombie* zombie)
{
	return reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(zombie) + 0x90);
}

uint32_t* zombie::get_hit_w(Zombie* zombie)
{
	return reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(zombie) + 0x94);
}

uint32_t* zombie::get_hit_h(Zombie* zombie)
{
	return reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(zombie) + 0x98);
}

void zombie::ZombieInitialize(Zombie* zombie, uint32_t theRow, ZombieType theZombieType, BOOL theVariant, Zombie* theParentZombie, uint32_t theFromWave)
{
	__asm {
		push theFromWave
		push theParentZombie
		push theVariant
		push theZombieType
		push zombie
		mov eax, theRow

		mov edx, 0x00522580
		call edx
	}
}

void zombie::RiseFromGrave(Zombie* zombie, uint32_t theCol, uint32_t theRow)
{
	__asm {
		push ebx

		push theRow
		mov ebx, zombie
		mov eax, theCol

		mov edx, 0x00531C90
		call edx

		pop ebx
	}
}

