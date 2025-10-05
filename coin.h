#pragma once

struct Coin
{
	uintptr_t LawnApp;             // 0x00 [指针] 基址
	uintptr_t Board;               // 0x04 [指针] 当前游戏信息和对象

	uint32_t image_x_delta;        // 0x08 图像X坐标变化量
	uint32_t image_y_delta;        // 0x0C 图像Y坐标变化量
	uint32_t hitbox_width;         // 0x10 判定宽度
	uint32_t hitbox_height;        // 0x14 判定高度

	BOOL     invisible;            // 0x18 [逻辑值] true 则物品隐形

	uint32_t row;                  // 0x1C 所在行数
	uint32_t layer;                // 0x20 图层
	float_t  x;                    // 0x24 [浮点] X 坐标
	float_t  y;                    // 0x28 [浮点] Y 坐标
	float_t  vx;                   // 0x2C [浮点] X 速度
	float_t  vy;                   // 0x30 [浮点] Y 速度
	float_t  scale;                // 0x34 [浮点] 大小

	BOOL     disappear_flag_a;     // 0x38 [逻辑值]
	BOOL     disappear_flag_b;     // 0x3C [逻辑值]

	uint32_t collect_to_x_24;      // 0x40 收集后变为 [24]（X）
	uint32_t collect_to_y_28;      // 0x44 收集后变为 [28]（Y）
	uint32_t y_target;             // 0x48 物品要移动到的 Y 坐标
	uint32_t life_time;            // 0x4C 物品已存在时间

	BOOL     collected;            // 0x50 [逻辑值] true 则被收集

	uint32_t vanish_countdown;     // 0x54 消失计时
	uint32_t item_type;            // 0x58 物品类型
	uint32_t motion_state;         // 0x5C 物品运动状态
	uint32_t anim_id;              // 0x60 动画附件ID
	uint32_t target_distance;      // 0x64 目标距离
	uint32_t plant_card_type;      // 0x68 植物卡牌类型

	uint8_t  garden_pot_blob[0x5C];// 0x6C..0xC7 花园盆栽内容（原始字节块，未解析）

	BOOLEAN  has_halo;             // 0xC8 [逻辑值] true 则有光环
	BOOLEAN  halo;                 // 0xC9 [逻辑值] [C8] 光环
	BOOLEAN  on_ground;            // 0xCA [逻辑值] 是否落地
	uint8_t  _pad3[1];             // 0xCB

	uint32_t falling_time;         // 0xCC 落下时间
	uint32_t _reserved_d0;         // 0xD0 保留（未文档化）
	uint32_t item_id;              // 0xD4 物品ID（结构为 [序列号, 编号] 各 2 字节）
};

enum class CoinType : DWORD
{
	SilverCoin = 1,   // 银币
	GoldCoin = 2,   // 金币
	Diamond = 3,   // 钻石
	Sun = 4,   // 太阳
	SmallSun = 5,   // 小太阳
	LargeSun = 6,   // 大太阳
	SeedPacket = 7,   // 植物卡片
	Trophy = 8,   // 奖杯
	Shovel = 9,   // 铲子
	Almanac = 10,  // 图鉴
	Key = 11,  // 钥匙
	Vase = 12,  // 花瓶
	WateringCan = 13,  // 洒水壶
	Sandwich = 14,  // 三明治
	Note = 15,  // 便条/遗书
	VanishPlaceholder = 16,  // 立即消失（占位）
	SeedlingGift = 17,  // 花苗礼盒
	CoinBag = 18,  // 金币袋
	GiftBoxPersistent = 19,  // 礼盒（不消失）
	CoinBagPersistent = 20,  // 金币袋（不消失）
	SilverTrophy = 21,  // 银奖杯
	GoldTrophy = 22,  // 金奖杯
	Chocolate = 23,  // 巧克力
	ChocolatePersistent = 24,  // 巧克力（不消失）
	GiftBoxMiniGames = 25,  // 礼品盒（小游戏）
	GiftBoxPuzzle = 26,  // 礼品盒（解密模式）
	GiftBoxSurvival = 27,  // 礼品盒（生存模式）
};

enum class CoinMotion : DWORD
{
	DropFromXY = 0,   // 从坐标落下
	SlowDropFromXY = 1,   // 从坐标缓慢落下
	PopFromBack = 2,   // 从后方跳出
	FastPopFromBack = 3,   // 从后方快速跳出
	CollectImmediately = 4,   // 直接收集
	AutoCollectLater = 5,   // 稍后自动收集
	PopFromRight = 6,   // 从屏幕右侧蹦出
	SpawnInSeedSlot = 7,   // 在卡槽栏生成
};

namespace coin
{

}


#include "board.h"
