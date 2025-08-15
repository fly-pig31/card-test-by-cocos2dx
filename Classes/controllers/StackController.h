#pragma once
#include "cocos2d.h"
#include "models/GameModel.h"
#include "views/StackView.h"
#include "views/PlayFieldView.h"
#include <managers/UndoManager.h>
USING_NS_CC;
/// <summary>
/// 牌堆控制器类，负责管理牌堆区域的卡牌逻辑操作（移动、回退等）
/// 协调牌堆视图(StackView)与游戏模型(GameModel)的交互
/// </summary>
class StackController :public cocos2d::Node
{
public:
	/// <summary>
	/// Cocos2d-x标准创建函数，用于创建牌堆控制器实例
	/// </summary>
	CREATE_FUNC(StackController);

	/// <summary>
	/// 初始化牌堆控制器和视图
	/// </summary>
	/// <param name="model">游戏数据模型，用于初始化视图</param>
	void setUp(GameModel& model);

	/// <summary>
	/// 根据游戏模型更新牌堆视图
	/// </summary>
	/// <param name="model">当前游戏模型，包含最新的牌堆状态</param>
	void setUpView(const GameModel& model) {
		_stackView->setUpWithCardModels(model);
	}

	/// <summary>
	/// 获取牌堆视图实例
	/// </summary>
	/// <returns>牌堆视图(StackView)指针</returns>
	StackView* getView() const noexcept {
		return _stackView;
	}

	/// <summary>
	/// 将牌堆中的卡牌移动到牌堆顶部
	/// </summary>
	/// <param name="model">游戏模型，存储当前游戏状态</param>
	/// <param name="tagId">要移动的卡牌ID</param>
	/// <returns>移动成功返回true，失败返回false</returns>
	bool moveToStackTop(GameModel& model, int tagId);

	/// <summary>
	/// 执行牌堆卡牌的回退操作（将卡牌恢复到之前的状态/位置）
	/// </summary>
	/// <returns>回退成功返回true，否则返回false</returns>
	bool moveUndo(const CardModel& model);

	/// <summary>
	/// 设置回退管理器，用于记录和执行回退操作
	/// </summary>
	/// <param name="undoManager">回退管理器实例</param>
	void setUndoManager(UndoManager* undoManager) noexcept {
		_undoManager = undoManager;
	}

private:
	PlayFieldView* _playFieldView = nullptr; // 游戏区视图（用于跨区域交互）
	StackView* _stackView = nullptr; // 牌堆视图实例，负责牌堆显示
	UndoManager* _undoManager; // 回退管理器，用于记录操作历史
};