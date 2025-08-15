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
/// 游戏主控制器类，统筹整个游戏的逻辑流程
/// 协调游戏区控制器、牌堆控制器、回退管理器等模块的交互
/// </summary>
class GameController :public cocos2d::Node {
private:
	PlayFieldController* _playFieldController = nullptr; // 游戏区控制器实例
	StackController* _stackController = nullptr; // 牌堆控制器实例

public:
	/// <summary>
	/// 创建游戏主控制器实例
	/// </summary>
	/// <returns>GameController实例指针</returns>
	static GameController* create();

	/// <summary>
	/// 开始指定关卡的游戏
	/// </summary>
	/// <param name="levelId">关卡ID，用于加载对应关卡配置</param>
	void startGame(int levelId);

protected:
	GameModel _gameModel; // 游戏数据模型，存储当前游戏的所有状态（卡牌、位置等）

public:
	/// <summary>
	/// 获取当前游戏模型（只读）
	/// </summary>
	/// <returns>当前游戏模型的常量引用</returns>
	virtual inline GameModel getGameModel(void) const {
		return _gameModel;
	}

	/// <summary>
	/// 设置游戏模型（更新游戏状态）
	/// </summary>
	/// <param name="var">新的游戏模型</param>
	virtual inline void setGameModel(GameModel var) {
		_gameModel = var;
	};

	/// <summary>
	/// 游戏视图访问器（Cocos2d-x宏，自动生成get/set方法）
	/// 用于获取和设置游戏主视图
	/// </summary>
	CC_SYNTHESIZE(GameView*, _gameView, GameView);

	/// <summary>
	/// 回退模型访问器（Cocos2d-x宏）
	/// 用于获取和设置回退模型（存储回退数据）
	/// </summary>
	CC_SYNTHESIZE(UndoModel, _undoModel, UndoModel);

	/// <summary>
	/// 回退管理器访问器（Cocos2d-x宏，带内存管理）
	/// 用于获取和设置回退管理器
	/// </summary>
	CC_SYNTHESIZE_RETAIN(UndoManager*, _undoManager, UndoManager);

	/// <summary>
	/// 执行上一步操作的回退
	/// </summary>
	void undoOperation();
};