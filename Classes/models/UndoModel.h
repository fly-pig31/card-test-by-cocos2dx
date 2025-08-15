#pragma once
#include "cocos2d.h"
#include "CardModel.h"

USING_NS_CC;
#pragma once
#include "cocos2d.h"
#include "CardModel.h"

USING_NS_CC;

/// <summary>
/// 回退模型类，负责存储卡牌操作的历史记录
/// 提供添加记录、获取最近记录、删除记录等基础功能
/// </summary>
class UndoModel
{
public:
	/// <summary>
	/// 添加一条卡牌操作记录（将卡牌状态存入历史）
	/// </summary>
	/// <param name="model">需要记录的卡牌模型</param>
	void push(const CardModel& model) {
		_model.push_back(model);
	}

	/// <summary>
	/// 移除并返回最近一次的记录（用于回退）
	/// </summary>
	/// <returns>最近一次记录的卡牌模型</returns>
	CardModel undo() {
		auto model = _model.back();
		_model.pop_back();
		CCLOG("UndoModel::undo model id=%d,position=(%.1f,%.1f)", model.getId(), model.getPosition().x, model.getPosition().y);
		return model;
	}

	/// <summary>
	/// 获取当前记录的数量
	/// </summary>
	/// <returns>记录数量</returns>
	int size()const noexcept {
		return _model.size();
	}

	/// <summary>
	/// 查看最近一次记录（不删除）
	/// </summary>
	/// <returns>最近一次记录的卡牌模型的常量引用</returns>
	const CardModel& peek() const {
		return _model.back();
	}

private:
	// 存储卡牌操作历史的双端队列（支持高效的尾部插入和删除）
	std::deque<CardModel> _model;
};