#include "PlayFieldController.h"

void PlayFieldController::setUp(GameModel& model)
{
	_playFieldView = PlayFieldView::create();
	_playFieldView->setOnClickCallBack([this, &model](int playFiledsIndex,int tagId) {
		moveToStackTop(model, playFiledsIndex, tagId);
		});
	//this->addChild(_playFieldView);
}

bool PlayFieldController::moveToStackTop(GameModel& model,int playFiledsIndex,int tagId)
{
	if (tagId != model.getPlayFieldPile().at(playFiledsIndex).cards.back().getId()) {
		CCLOG("Unable to move card");
		_playFieldView->unMatched(tagId);
		return false;
	};
	//数据操作
	auto& cards = model.getPlayFieldPile().at(playFiledsIndex).cards;
	auto& topCard = model.getStackArea().topCard;
	auto targetCard = cards.back();
	if (std::abs(topCard.getFace() - targetCard.getFace())!=1) {
		CCLOG("top card face % and face %d not match!", topCard.getFace(), targetCard.getFace());
		_playFieldView->unMatched(tagId);
		return false;
	}
	//记录回退数据
	_undoManager->record(targetCard);
	//手牌顶部数量++
	model.getStackArea().topNums++;
	//置换堆顶的牌
	topCard = targetCard;
	CCLOG("update top card face to %d", topCard.getFace());
	//从牌堆中弹出移动的卡
	cards.pop_back();
	//视图操作
	_playFieldView->moveToStackTop(playFiledsIndex, model.getStackArea().topNums);
	return true;
}

bool PlayFieldController::moveUndo(const CardModel&model)
{
	//视图操作
	_playFieldView->moveUndo(model);
	return true;
}

