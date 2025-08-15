#include "StackController.h"

void StackController::setUp(GameModel& model)
{
	_stackView = StackView::create();
	_stackView->setOnClickCallBack([this, &model](int playFiledsIndex,int tagId) {
		moveToStackTop(model, tagId);
		});

	//this->addChild(_stackView);
}

bool StackController::moveToStackTop(GameModel& model,int tagId)
{
	if (tagId != model.getStackArea().deck.back().getId()) {
		CCLOG("Unable to move card");
		return false;
	}
	//数据操作
	auto& area = model.getStackArea();
	//记录回退数据
	_undoManager->record(area.deck.back());
	//手牌顶部数量++
	area.topNums++;
	//置换堆顶的牌
	area.topCard = area.deck.back();
	CCLOG("update top card face to %d",area.topCard.getFace());
	//弹出手牌区的牌
	area.deck.pop_back();
	//视图操作
	_stackView->moveToStackTop(area.topNums);
	return true;
}

bool StackController::moveUndo(const CardModel& model)
{
	//视图操作
	_stackView->moveUndo(model);
	return true;
}
