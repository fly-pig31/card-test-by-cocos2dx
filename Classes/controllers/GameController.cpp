#include "GameController.h"
#include "controllers/PlayFieldController.h"
#include "controllers/StackController.h"
GameController* GameController::create()
{
	GameController* pRet = new(std::nothrow) GameController();
	if (pRet) {
		//�Ե�һ�ؿ���ʼ
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
/// ͨ���ؿ�id��������Ϸ
/// </summary>
/// <param name="levelId">�ؿ�id</param>
void GameController::startGame(int levelId) {
	CCLOG("GameController::startGame level ", levelId, "start");
	auto config = LevelConfigLoader::loadLevelConfig(levelId);
	_gameModel = GameModelFromLevelGenerator::generateGameModel(config);
	// ����GameView����ӵ����ڵ�
	_gameView = GameView::create();
	// ��ʼ��PlayFieldController
	_playFieldController = PlayFieldController::create();
	//��ͼ��ʼ��
	_playFieldController->setUp(_gameModel);
	_stackController = StackController::create();
	//��ͼ��ʼ��
	_stackController->setUp(_gameModel);
	// ��ʼ��UndoManager
	_undoManager = UndoManager::create();
	_stackController->setUndoManager(_undoManager);
	_playFieldController->setUndoManager(_undoManager);

	// ����ģ�͵���ͼ
	_gameView->setup(_gameModel);
	_gameView->setPosition(Vec2::ZERO);
	_gameView->setUndoCallback([this] {
		undoOperation();
		});
	// ��ʼ�����ӿ���������ͼ
	_gameView->addChild(_stackController->getView(), 0, "stack");
	_gameView->addChild(_playFieldController->getView(), 0, "playField");
	_stackController->setUpView(_gameModel);
	_playFieldController->setUpView(_gameModel);

	CCLOG("PlayFieldView GlobalZ: %d, StackView GlobalZ: %d",
		_playFieldController->getView()->getGlobalZOrder(), _stackController->getGlobalZOrder());

	// ������Ϸ��ͼ
	this->addChild(_stackController);
	this->addChild(_playFieldController);

	this->addChild(_undoManager);
	this->addChild(_gameView);
	//�ƶ�����Ŀ���
	_stackController->moveToStackTop(_gameModel,_gameModel.getStackArea().deck.back().getId());
}

void GameController::undoOperation()
{
	if (!_undoManager->canUndo()) {
		CCLOG("Info: can not undo,undo data is empty.");
		return;
	}
	auto undoCardModel =_undoManager->undo();
	//��ԭ�ƶѶ�
	_gameModel.getStackArea().topCard = _undoManager->peek();
	CCLOG("update top card face to %d", _gameModel.getStackArea().topCard);
	_gameModel.getStackArea().topNums--;
	if (undoCardModel.isInStack()) {
		_gameModel.pushStackArea(undoCardModel);
		//��ͼ����
		_stackController->moveUndo(undoCardModel);
	}
	else
	{
		_gameModel.pushPlayFieldByIndex(undoCardModel);
		//��ͼ����
		_playFieldController->moveUndo(undoCardModel);
	}

}

