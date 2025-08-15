#pragma once
#include "cocos2d.h"
#include "models/GameModel.h"
#include "views/PlayFieldView.h"
#include "views/StackView.h"
#include "managers/UndoManager.h"
USING_NS_CC;
/// <summary>
/// 桌面区控制器
/// </summary>
class PlayFieldController :public cocos2d::Node {
public:
	CREATE_FUNC(PlayFieldController);
	/// <summary>
	/// 移动手牌区的牌到手牌区顶
	/// </summary>
	bool moveToStackTop(GameModel& model, int playFiledIndex,int tagId);
	/// <summary>
	/// 回退移动操作
	/// </summary>
	/// <param name="model"></param>
	/// <returns></returns>
	bool moveUndo(const CardModel& model);
	/// <summary>
	/// 设置回退管理器
	/// </summary>
	/// <param name="undoManager"></param>
	void setUndoManager(UndoManager* undoManager) noexcept {
		_undoManager = undoManager;
	}
	/// <summary>
	/// 初始化视图和控制器
	/// </summary>
	/// <param name="model">关卡游戏数据模型</param>
	void setUp(GameModel& model);
	void setUpView(const GameModel& model) {
		_playFieldView->setUpWithCardModels(model);
	};
	PlayFieldView* getView() const noexcept {
		return _playFieldView;
	}
private:
	PlayFieldView* _playFieldView = nullptr;
	StackView* _stackView = nullptr;
	UndoManager* _undoManager;
};

