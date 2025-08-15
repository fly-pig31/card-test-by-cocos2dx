#pragma once
#include "cocos2d.h"
#include "models/GameModel.h"
#include "models/UndoModel.h"
#include "managers/UndoManager.h"
#include "services/GameModelFromLevelGenerator.h"
#include "configs/models/CardResConfig.h"
#include "configs/loaders/LevelConfigLoader.h"
#include "PlayFieldController.h"
#include "StackController.h"
/// <summary>
/// 向前声明GameView
/// </summary>
class GameView;
/// <summary>
/// 关卡游戏控制器
/// </summary>
class GameController :public cocos2d::Node {
private:
	PlayFieldController* _playFieldController = nullptr;
	StackController* _stackController = nullptr;
public:
	static GameController* create();
	void startGame(int levelId);

protected:
	GameModel _gameModel;
public:
	virtual inline GameModel getGameModel(void) const {
		return _gameModel;
	}
	virtual inline void setGameModel(GameModel var) {
		_gameModel = var;
	};
	CC_SYNTHESIZE(GameView*, _gameView, GameView);
	CC_SYNTHESIZE(UndoModel, _undoModel, UndoModel);
	CC_SYNTHESIZE_RETAIN(UndoManager*, _undoManager, UndoManager);
	void undoOperation();
};