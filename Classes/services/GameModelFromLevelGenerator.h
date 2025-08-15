#pragma once
#include "models/GameModel.h"
#include "configs/models/LevelConfig.h"
/// <summary>
/// �ؿ�GameModel������
/// ������Ϸ�ؿ�������model
/// </summary>
class GameModelFromLevelGenerator
{
public:
	/// <summary>
	/// ͨ��LevelConfig����GameModel
	/// </summary>
	/// <param name="config">�ؿ�����</param>
	/// <returns>��Ϸ����model</returns>
	static GameModel generateGameModel(const LevelConfig& config) {
		int id = 0;
		GameModel gameModel;
		//�������ı�ԭ��������
		auto playFieldCardConfigs = config.playfield;
		//��y��Ӵ�С��������
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
		//�������ı�ԭ��������
		auto stackCardConfigs = config.stack;
		//��x��Ӵ�С��������
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

