#pragma once
#include "models/GameModel.h"
#include "configs/models/LevelConfig.h"
/// <summary>
/// 关卡GameModel生成器
/// 生成游戏关卡的数据model
/// </summary>
class GameModelFromLevelGenerator
{
public:
	/// <summary>
	/// 通过LevelConfig生成GameModel
	/// </summary>
	/// <param name="config">关卡配置</param>
	/// <returns>游戏数据model</returns>
	static GameModel generateGameModel(const LevelConfig& config) {
		int id = 0;
		GameModel gameModel;
		//拷贝不改变原来的配置
		auto playFieldCardConfigs = config.playfield;
		//以y轴从大到小进行排序
		std::sort(playFieldCardConfigs.begin(), playFieldCardConfigs.end(),
			[](const CardConfig& a, const CardConfig& b) {
				return a.position.y > b.position.y;
			});
	
		int big_y = config.playfield.front().position.y;
		int zOrder = 1;
		for (const auto& cardConfig : playFieldCardConfigs) {
			if (big_y != cardConfig.position.y) {
				big_y = cardConfig.position.y;
				zOrder++;
			}
			auto model = CardModel(id++, cardConfig.face,
				cardConfig.suit,
				cardConfig.position, true, false,zOrder);
			gameModel.pushPlayField(model);
		}
		//拷贝不改变原来的配置
		auto stackCardConfigs = config.stack;
		//以x轴从大到小进行排序
		std::sort(stackCardConfigs.begin(), stackCardConfigs.end(),
			[](const CardConfig& a, const CardConfig& b) {
				return a.position.x < b.position.x;
			});
		zOrder = 1;
		for (const auto& cardConfig : config.stack) {
			auto model = CardModel(id++, cardConfig.face,
				cardConfig.suit,
				cardConfig.position, true, true, zOrder++);
			gameModel.pushStackArea(model);
		}
		return gameModel;
	};
};

