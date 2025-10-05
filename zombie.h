#pragma once

struct Zombie
{
    uintptr_t LawnApp;            // 0x00 [指针]=基址
    uintptr_t Board;              // 0x04 [指针]=当前游戏信息和对象

    uint32_t image_x;             // 0x08 图像的横坐标
    uint32_t image_y;             // 0x0C 图像的纵坐标
    uint32_t hurt_width_base;     // 0x10 受伤判定宽度基准
    uint32_t hurt_height_base;    // 0x14 受伤判定高度基准
    BOOL     visible;             // 0x18 [逻辑值] 为 false 时隐形

    uint32_t row;                 // 0x1C 所在行数
    uint32_t layer;               // 0x20 图像图层
    uint32_t zombie_type;         // 0x24 僵尸类型
    uint32_t zombie_state;        // 0x28 僵尸状态
    float_t  x;                   // 0x2C [浮点] 横坐标
    float_t  y;                   // 0x30 [浮点] 纵坐标
    float_t  v_rel_or_aquarium_speed; // 0x34 [浮点] 相对速度/水族馆合速度
    uint32_t accum_38;            // 0x38 不断增大直到 > [40]*[44] 后变回 0
    uint32_t brains_countdown_init; // 0x3C 喊 brains 的倒计时初值 [500,1500)
    uint32_t jitter_timer;        // 0x40 无动画抖动帧计时
    uint32_t jitter_countdown;    // 0x44 无动画抖动帧倒计时
    uint32_t jitter_index;        // 0x48 无动画抖动帧索引
    uint32_t last_jitter_index;   // 0x4C 上一个无动画抖动帧索引

    BOOLEAN  has_tongue;          // 0x50 [逻辑值] 是否有舌头
    BOOLEAN  eating;              // 0x51 [逻辑值] 啃食时为 true
    uint8_t  _pad1[2];            // 0x52..53

    uint32_t flash_countdown;     // 0x54 僵尸闪光倒计时
    uint32_t acc2_glow_countdown; // 0x58 2类饰品发光倒计时
    uint32_t acc2_jitter_countdown; // 0x5C 2类饰品抖动倒计时
    uint32_t life_time;           // 0x60 僵尸已存在时间
    uint32_t motion_state;        // 0x64 僵尸运动状态
    uint32_t attr_countdown;      // 0x68 属性倒计时
    int32_t  born_wave_or_stand;  // 0x6C 出生波/站立状态（可为 -2,-3,-4）
    uint32_t drop_item_flag;      // 0x70 0 时不掉落物品
    uint32_t disappear_countdown; // 0x74 僵尸消失倒计时

    BOOL     ice_car_dying;       // 0x78 [逻辑值] 冰车正在死亡

    uint32_t ladder_col;          // 0x7C 爬的梯子所在列
    uint32_t bungee_or_boss_col;  // 0x80 蹦极/僵王左侧蹦极/砸车左上格列
    float_t  y_offset;            // 0x84 [浮点] 纵向偏移
    BOOL     bungee_blocked_by_umbrella; // 0x88 [逻辑值] 蹦极被保护伞挡

    uint32_t hit_x;               // 0x8C 中弹判定横坐标
    uint32_t hit_y;               // 0x90 中弹判定纵坐标
    uint32_t hit_w;               // 0x94 中弹判定横向宽度
    uint32_t hit_h;               // 0x98 中弹判定纵向高度
    uint32_t atk_x;               // 0x9C 攻击判定横坐标
    uint32_t atk_y;               // 0xA0 攻击判定纵坐标
    uint32_t atk_w;               // 0xA4 攻击判定横向宽度
    uint32_t atk_h;               // 0xA8 攻击判定纵向高度

    uint32_t slow_countdown;      // 0xAC 减速倒计时
    uint32_t butter_countdown;    // 0xB0 黄油固定倒计时
    uint32_t freeze_countdown;    // 0xB4 冻结倒计时

    BOOLEAN  charmed;             // 0xB8 [逻辑值] 被魅惑
    BOOLEAN  blown_away;          // 0xB9 [逻辑值] 被吹走
    BOOLEAN  not_dying;           // 0xBA [逻辑值] 非濒死
    BOOLEAN  hand_intact;         // 0xBB [逻辑值] 没断手
    BOOLEAN  has_handheld_or_snowman_left; // 0xBC [逻辑值] 手持物/雪人向左走
    BOOLEAN  in_water;            // 0xBD [逻辑值] 在水中
    uint8_t  ladder_shadow_follow; // 0xBE [1字节] 上梯子时影子跟随
    BOOLEAN  garlic;              // 0xBF [逻辑值] 吃到大蒜

    uint32_t garlic_eaten_countdown; // 0xC0 吃完大蒜倒计时
    uint32_t acc1_type;           // 0xC4 1类饰品类型
    uint32_t hp;                  // 0xC8 当前本体血量
    uint32_t hp_max;              // 0xCC 本体上限
    uint32_t acc1_hp;             // 0xD0 1类饰品当前血量
    uint32_t acc1_hp_max;         // 0xD4 1类饰品血量上限
    uint32_t acc2_type;           // 0xD8 2类饰品
    uint32_t acc2_hp;             // 0xDC 2类饰品当前血量
    uint32_t acc2_hp_max;         // 0xE0 2类饰品血量上限
    uint32_t balloon_hp;          // 0xE4 气球当前血量
    uint32_t balloon_hp_max;      // 0xE8 气球血量上限

    BOOL     disappeared;         // 0xEC [逻辑值] 消失

    uint32_t sled_leader_or_dancer_id;   // 0xF0 雪橇队领头/舞王ID
    uint32_t sled_second_or_back1_or_bungee1; // 0xF4
    uint32_t sled_third_or_back2_or_bungee2;  // 0xF8
    uint32_t sled_fourth_or_back3_or_bungee3; // 0xFC
    uint32_t dancer_back4_id;     // 0x100 舞王第四只伴舞ID

    BOOL     have_unique_sample;  // 0x104 [逻辑值] haveUniqueSample

    uint32_t particle_x;          // 0x108 粒子X坐标
    uint32_t particle_y;          // 0x10C 粒子Y坐标
    uint32_t bullet_hit_anim_id;  // 0x110 受到子弹攻击的动画附件ID
    uint32_t boss_misc_counter;   // 0x114 僵王放僵尸/舞王召唤/水族馆产阳光/篮球剩余
    uint32_t body_anim_id;        // 0x118 僵尸本体动画ID
    float_t  size;                // 0x11C [浮点] 大小
    float_t  y_offset_delta_or_angle; // 0x120 [浮点] 纵向偏移速度/角度(弧度)
    uint32_t boss_speed;          // 0x124 僵王运动速度
    uint32_t bungee_holding_plant; // 0x128 蹦极手里的植物
    uint32_t boss_damage_phase;   // 0x12C 根据损伤度判断是否放蹦极或砸车
    uint32_t boss_row_misc;       // 0x130 放僵尸/砸车/跺脚偏上行 的行数
    uint32_t boss_bungee_or_smash_cd; // 0x134 放蹦极或砸车倒计时
    uint32_t boss_stamp_cd;       // 0x138 跺脚倒计时
    uint32_t boss_stretch_head_cd; // 0x13C 伸头倒计时
    uint32_t boss_ice_fireball_anim_id; // 0x140 冰火球动画ID(无则0)
    uint32_t head_or_flag_anim_id; // 0x144 植物僵尸头部/旗帜动画ID
    uint32_t boss_fireball_row;   // 0x148 冰/火球的行数
    uint32_t ball_type;           // 0x14C 球的类型(冰球为0)
    uint32_t crushed_anim_id;     // 0x150 被小推车碾压时动画ID
    uint32_t last_portal_x;       // 0x154 上一次穿过传送门的X坐标
    uint32_t zombie_id;           // 0x158 僵尸ID([序列号,编号])
};

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
