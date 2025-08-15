#pragma once
#include "cocos2d.h"
#include "CardView.h"
#include "models/GameModel.h"
#include "ui/CocosGUI.h"
#include "views/PlayFieldView.h"
#include "views/StackView.h"
USING_NS_CC;

class GameController; // ǰ������

class GameView : public Layer {
public:
	CREATE_FUNC(GameView);

	void setup(const GameModel& model);
	void setUndoCallback(std::function<void()> callback) {
		_undoCallback = callback;
	}
	// ���˰�ť
	void createUndoButton();

private:
	bool init()override;
	GameController* _controller = nullptr;
	std::function<void()> _undoCallback;
};