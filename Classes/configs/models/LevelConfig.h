#pragma once
#include "models/CardModel.h"

/// <summary>
/// 单张卡牌的配置信息结构体（用于关卡配置）
/// 存储卡牌的初始属性（面值、花色、位置）
/// </summary>
struct CardConfig {
    CardFaceType face; // 卡牌面值（A、2、...、K）
    CardSuitType suit; // 卡牌花色（梅花、方块、红桃、黑桃）
    cocos2d::Vec2 position; // 卡牌初始位置（世界坐标系）
};

/// <summary>
/// 关卡配置结构体，存储一个关卡的所有初始卡牌信息
/// 分为游戏区卡牌和牌堆卡牌两部分
/// </summary>
struct LevelConfig {
    std::vector<CardConfig> playfield; // 游戏区初始卡牌配置
    std::vector<CardConfig> stack; // 牌堆初始卡牌配置
};
