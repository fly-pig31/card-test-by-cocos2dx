#pragma once
#include "cocos2d.h"
#include "models/GameModel.h"
#include "views/PlayFieldView.h"
#include "views/StackView.h"
#include "managers/UndoManager.h"
/// <summary>
/// 游戏区控制器类，负责管理游戏区卡牌的逻辑操作（移动、回退等）
/// 协调游戏区视图(PlayFieldView)与游戏模型(GameModel)的交互
/// </summary>
class PlayFieldController :public cocos2d::Node {
public:
	/// <summary>
	/// Cocos2d-x标准创建函数，用于创建控制器实例
	/// </summary>
	CREATE_FUNC(PlayFieldController);

	/// <summary>
	/// 将游戏区的卡牌移动到牌堆顶部
	/// </summary>
	/// <param name="model">游戏模型，存储当前游戏状态</param>
	/// <param name="playFiledIndex">游戏区卡牌堆的索引</param>
	/// <param name="tagId">要移动的卡牌ID</param>
	/// <returns>移动成功返回true，失败返回false（如卡牌不匹配）</returns>
	bool moveToStackTop(GameModel& model, int playFiledIndex, int tagId);
	/// <summary>
	/// 执行游戏区卡牌的回退操作（将卡牌恢复到之前的状态/位置）
	/// </summary>
	/// <param name="model">需要回退的卡牌模型</param>
	/// <returns>回退成功返回true，否则返回false</returns>
	bool moveUndo(const CardModel& model);

	/// <summary>
	/// 设置回退管理器，用于记录和执行回退操作
	/// </summary>
	/// <param name="undoManager">回退管理器实例</param>
	void setUndoManager(UndoManager* undoManager) noexcept {
		_undoManager = undoManager;
	}
	/// <summary>
	/// 初始化游戏区视图和相关数据
	/// </summary>
	/// <param name="model">游戏数据模型，用于初始化视图</param>
	void setUp(GameModel& model);
	/// <summary>
	/// 根据游戏模型更新游戏区视图
	/// </summary>
	/// <param name="model">当前游戏模型，包含最新的卡牌状态</param>
	void setUpView(const GameModel& model) {
		_playFieldView->setUpWithCardModels(model);
	};
	/// <summary>
	/// 获取游戏区视图实例
	/// </summary>
	/// <returns>游戏区视图(PlayFieldView)指针</returns>
	PlayFieldView* getView() const noexcept {
		return _playFieldView;
	}
private:
	PlayFieldView* _playFieldView = nullptr; // 游戏区视图实例，负责卡牌显示
	StackView* _stackView = nullptr; // 牌堆视图实例，用于交互
	UndoManager* _undoManager; // 回退管理器，用于记录操作历史
};