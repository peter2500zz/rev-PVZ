#pragma once

struct Coin;

enum class CoinType : DWORD {
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

enum class CoinMotion : DWORD {
	DropFromXY = 0,   // 从坐标落下
	SlowDropFromXY = 1,   // 从坐标缓慢落下
	PopFromBack = 2,   // 从后方跳出
	FastPopFromBack = 3,   // 从后方快速跳出
	CollectImmediately = 4,   // 直接收集
	AutoCollectLater = 5,   // 稍后自动收集
	PopFromRight = 6,   // 从屏幕右侧蹦出
	SpawnInSeedSlot = 7,   // 在卡槽栏生成
};

