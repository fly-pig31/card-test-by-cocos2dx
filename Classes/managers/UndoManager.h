
#pragma once
#include "cocos2d.h"
#include "models/UndoModel.h"
#include "models/GameModel.h"
#include "views/GameView.h"

USING_NS_CC;
/// <summary>
/// 回退管理器类，负责记录卡牌操作历史并执行回退操作
/// 统一管理游戏中的所有回退逻辑，协调回退模型与控制器的交互
/// </summary>
class UndoManager : public Node {
public:
	/// <summary>
	/// Cocos2d-x标准创建函数，用于创建回退管理器实例
	/// </summary>
	CREATE_FUNC(UndoManager);

	/// <summary>
	/// 执行上一步操作的回退
	/// </summary>
	/// <returns>回退后的卡牌模型（恢复到操作前的状态）</returns>
	CardModel undo();

	/// <summary>
	/// 记录卡牌操作（将当前卡牌状态存入回退历史）
	/// </summary>
	/// <param name="model">需要记录的卡牌模型（操作后的状态）</param>
	void record(const CardModel& model);

	/// <summary>
	/// 检查是否可以执行回退操作（是否有历史记录）
	/// </summary>
	/// <returns>有可回退的记录返回true，否则返回false</returns>
	bool canUndo()const;

	/// <summary>
	/// 查看最近一次记录的卡牌状态（不执行回退）
	/// </summary>
	/// <returns>最近一次记录的卡牌模型的常量引用</returns>
	const CardModel& peek()const;

protected:
	UndoModel _undoModel; // 回退模型，存储卡牌操作的历史记录
};