#include "GameController.h"
#include "controllers/PlayFieldController.h"
#include "controllers/StackController.h"
GameController* GameController::create()
{
	GameController* pRet = new(std::nothrow) GameController();
	if (pRet) {
		//以第一关卡开始
		pRet->startGame(1);
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

/// <summary>
/// 通过关卡id来启动游戏
/// </summary>
/// <param name="levelId">关卡id</param>
void GameController::startGame(int levelId) {
	CCLOG("GameController::startGame level ", levelId, "start");
	auto config = LevelConfigLoader::loadLevelConfig(levelId);
	_gameModel = GameModelFromLevelGenerator::generateGameModel(config);
	// 创建GameView并添加到父节点
	_gameView = GameView::create();
	// 初始化PlayFieldController
	_playFieldController = PlayFieldController::create();
	//视图初始化
	_playFieldController->setUp(_gameModel);
	_stackController = StackController::create();
	//视图初始化
	_stackController->setUp(_gameModel);
	// 初始化UndoManager
	_undoManager = UndoManager::create();
	_stackController->setUndoManager(_undoManager);
	_playFieldController->setUndoManager(_undoManager);

	// 更新模型到视图
	_gameView->setup(_gameModel);
	_gameView->setPosition(Vec2::ZERO);
	_gameView->setUndoCallback([this] {
		undoOperation();
		});
	// 初始化各子控制器的视图
	_gameView->addChild(_stackController->getView(), 0, "stack");
	_gameView->addChild(_playFieldController->getView(), 0, "playField");
	_stackController->setUpView(_gameModel);
	_playFieldController->setUpView(_gameModel);

	CCLOG("PlayFieldView GlobalZ: %d, StackView GlobalZ: %d",
		_playFieldController->getView()->getGlobalZOrder(), _stackController->getGlobalZOrder());

	// 创建游戏视图
	this->addChild(_stackController);
	this->addChild(_playFieldController);

	this->addChild(_undoManager);
	this->addChild(_gameView);
	//移动最初的卡牌
	_stackController->moveToStackTop(_gameModel,_gameModel.getStackArea().deck.back().getId());
}

void GameController::undoOperation()
{
	if (!_undoManager->canUndo()) {
		CCLOG("Info: can not undo,undo data is empty.");
		return;
	}
	auto undoCardModel =_undoManager->undo();
	//还原牌堆顶
	_gameModel.getStackArea().topCard = _undoManager->peek();
	CCLOG("update top card face to %d", _gameModel.getStackArea().topCard);
	_gameModel.getStackArea().topNums--;
	if (undoCardModel.isInStack()) {
		_gameModel.pushStackArea(undoCardModel);
		//视图操作
		_stackController->moveUndo(undoCardModel);
	}
	else
	{
		_gameModel.pushPlayFieldByIndex(undoCardModel);
		//视图操作
		_playFieldController->moveUndo(undoCardModel);
	}

}

