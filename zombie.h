#pragma once

struct Zombie;

enum ZombieType : DWORD
{
	ZOMBIE_NORMAL = 0,   // 普通僵尸 / Browncoat
	ZOMBIE_FLAG = 1,   // 旗手僵尸
	ZOMBIE_CONEHEAD = 2,   // 路障僵尸
	ZOMBIE_POLE_VAULTER = 3,   // 撑杆跳僵尸
	ZOMBIE_BUCKETHEAD = 4,   // 铁桶僵尸
	ZOMBIE_NEWSPAPER = 5,   // 读报僵尸
	ZOMBIE_SCREEN_DOOR = 6,   // 铁门僵尸
	ZOMBIE_FOOTBALL = 7,   // 橄榄球僵尸
	ZOMBIE_DANCING = 8,   // （早期名 Disco / 后期名 Dancer）
	ZOMBIE_BACKUP_DANCER = 9,   // 伴舞僵尸
	ZOMBIE_DUCKY_TUBE = 10,  // 漂浮泳圈僵尸
	ZOMBIE_SNORKEL = 11,  // 潜水僵尸
	ZOMBIE_ZOMBONI = 12,  // 冰车僵尸（Zomboni）
	ZOMBIE_BOBSLED = 13,  // 冰道雪橇队
	ZOMBIE_DOLPHIN_RIDER = 14,  // 海豚骑士僵尸
	ZOMBIE_JACK_IN_THE_BOX = 15,  // 玩偶匣僵尸
	ZOMBIE_BALLOON = 16,  // 气球僵尸
	ZOMBIE_DIGGER = 17,  // 矿工僵尸
	ZOMBIE_POGO = 18,  // 弹跳杆僵尸
	ZOMBIE_YETI = 19,  // 雪人僵尸（隐藏）
	ZOMBIE_BUNGEE = 20,  // 蹦极僵尸
	ZOMBIE_LADDER = 21,  // 梯子僵尸
	ZOMBIE_CATAPULT = 22,  // 投石车僵尸
	ZOMBIE_GARGANTUAR = 23,  // 巨人僵尸（Gargantuar）
	ZOMBIE_IMP = 24,  // 小鬼（Imp）
	ZOMBIE_DR_ZOMBOSS = 25,  // 终局 Boss：僵博（Dr. Zomboss）

	// 小游戏（Zombotany/2）等扩展型单位（按常见实现继续顺序编号）：
	ZOMBIE_PEA_SHOOTER = 26,  // 豌豆僵尸（Zombotany）
	ZOMBIE_WALLNUT = 27,  // 坚果僵尸
	ZOMBIE_TALLNUT = 28,  // 高坚果僵尸
	ZOMBIE_GATLING_PEA = 29,  // 多重豌豆僵尸（Zombotany 2）

	ZOMBIE_COUNT
};

namespace zombie
{
	// 我自己实现的函数

	// hitbox相关
	inline uint32_t* get_hit_x(Zombie* zombie) { return reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(zombie) + 0x8C); }
	inline uint32_t* get_hit_y(Zombie* zombie) { return reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(zombie) + 0x90); }
	inline uint32_t* get_hit_w(Zombie* zombie) { return reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(zombie) + 0x94); }
	inline uint32_t* get_hit_h(Zombie* zombie) { return reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(zombie) + 0x98); }

	// 实现的自带函数
	inline void ZombieInitialize(
		Zombie* zombie,
		uint32_t theRow,
		ZombieType theZombieType,
		BOOL theVariant,
		Zombie* theParentZombie,
		uint32_t theFromWave
	)
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

	inline void RiseFromGrave(Zombie* zombie, uint32_t theCol, uint32_t theRow)
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
}
