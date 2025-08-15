#pragma once
#include "models/CardModel.h"

struct CardConfig {
    CardFaceType face;
    CardSuitType suit;
    cocos2d::Vec2 position;
};

struct LevelConfig {
    std::vector<CardConfig> playfield;
    std::vector<CardConfig> stack;
};

