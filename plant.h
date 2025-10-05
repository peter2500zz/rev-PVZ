#pragma once

struct Plant
{
    uintptr_t LawnApp;            // 0x00 [指针]=基址
    uintptr_t Board;              // 0x04 [指针]=当前游戏信息和对象

    uint32_t x_i;                 // 0x08 植物横坐标（整数）
    uint32_t y_i;                 // 0x0C 植物纵坐标（整数）
    uint32_t hurt_w;              // 0x10 植物判定长度
    uint32_t hurt_h;              // 0x14 植物判定高度
    BOOL     visible;             // 0x18 [逻辑值] 为 true 时可见

    uint32_t row;                 // 0x1C 所在行数
    uint32_t layer;               // 0x20 图像图层
    uint32_t plant_type;          // 0x24 植物类型（模仿植物为被模仿类型）
    uint32_t col;                 // 0x28 所在列数
    uint32_t jitter_time;         // 0x2C 无动画抖动时间
    uint32_t jitter_index;        // 0x30 无动画抖动帧索引
    uint32_t jitter_frame_time;   // 0x34 无动画抖动帧时间
    uint32_t jitter_frame_count;  // 0x38 无动画抖动帧计数
    uint32_t state;               // 0x3C 植物状态

    uint32_t hp;                  // 0x40 当前血量
    uint32_t hp_max;              // 0x44 血值上限
    uint32_t sub_type;            // 0x48 植物子类型
    uint32_t disappear_cd;        // 0x4C 植物消失倒计时
    uint32_t ash_ice_clover_cd;   // 0x50 灰烬/冰核/三叶草生效倒计时
    uint32_t attr_cd;             // 0x54 属性倒计时
    uint32_t fire_or_produce_cd;  // 0x58 触发发射/生产物品倒计时
    uint32_t fire_or_produce_interval; // 0x5C 触发发射/生产物品时间间隔

    uint8_t  _rect_unused[0x10];  // 0x60~6F [废弃] 植物矩形（占位16字节）
    uint8_t  _atk_rect_unused[0x10]; // 0x70~7F [废弃] 植物攻击矩形（占位16字节）

    uint32_t cannon_crosshair_x_minus47; // 0x80 炮准心横坐标-47
    uint32_t cannon_crosshair_y;  // 0x84 炮准心纵坐标
    uint32_t row_dup;             // 0x88 所在行（另一处保存）
    uint32_t particle_system_id;  // 0x8C 粒子系统ID
    uint32_t bullet_spawn_cd;     // 0x90 子弹生成倒计时
    uint32_t body_anim_id;        // 0x94 植物本体动画ID
    uint32_t pea_head_anim_id;    // 0x98 豌豆头/三线射手上方头 动画ID
    uint32_t threepeater_mid_anim_id; // 0x9C 三线射手中间头 动画ID
    uint32_t threepeater_low_anim_id; // 0xA0 三线射手下方头 动画ID
    uint32_t blink_anim_id;       // 0xA4 眨眼动画ID
    uint32_t potato_mine_flash_anim_id; // 0xA8 土豆雷闪灯 动画ID
    uint32_t mushroom_sleep_anim_id;    // 0xAC 蘑菇睡觉 zzz 动画ID
    uint32_t blink_cd;            // 0xB0 眨眼倒计时
    uint32_t being_eaten_50cs_cd; // 0xB4 被啃 50cs 倒计时
    uint32_t glow_cd;             // 0xB8 发光倒计时
    uint32_t flash_cd;            // 0xBC 闪光倒计时

    float_t  image_x_offset_f;    // 0xC0 [浮点] 图像向右偏移坐标
    float_t  image_y_offset_f;    // 0xC4 [浮点] 图像向下偏移坐标
    float_t  absorb_item_x;       // 0xC8 [浮点] 吸收物品横坐标
    float_t  absorb_item_y;       // 0xCC [浮点] 吸收物品纵坐标
    float_t  absorb_target_dx;    // 0xD0 [浮点] 吸收物品目标位置横向偏移
    float_t  absorb_target_dy;    // 0xD4 [浮点] 吸收物品目标位置纵向偏移

    uint32_t magnet_first_item;   // 0xD8 磁力菇吸取物品类型/吸金磁第1物品
    uint8_t  _magnet_rest4[0x4C]; // 0xDC~0x127 吸金磁其余4个物品（占位）

    uint32_t attack_target_zombie_id; // 0x12C 攻击目标僵尸ID
    uint32_t mushroom_cd;         // 0x130 蘑菇倒计时
    uint32_t bungee_grab_state;   // 0x134 蹦极抓住状态(0/1/2)
    int32_t  imitator_info;       // 0x138 是否为模仿植物/被模仿的植物类型（非模仿为 -1）
    int32_t  direction;           // 0x13C 方向（-1 右，1 左）

    uint8_t  toggling_0_1;        // 0x140 [1字节] 0/1 之间变换
    BOOLEAN  disappeared;         // 0x141 [逻辑值] true 则植物消失
    BOOLEAN  squashed;            // 0x142 [逻辑值] true 则植物压扁
    BOOLEAN  sleeping;            // 0x143 [逻辑值] true 则植物睡着
    BOOLEAN  on_board;            // 0x144 [逻辑值] true 则在 Board 上
    BOOLEAN  glowing;             // 0x145 [逻辑值] true 则发亮
    uint8_t  _pad1[2];            // 0x146..147

    uint32_t plant_id;            // 0x148 植物ID([序列号,编号] 各2字节)
};
