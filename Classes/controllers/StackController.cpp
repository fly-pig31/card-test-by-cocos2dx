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
	//���ݲ���
	auto& area = model.getStackArea();
	//��¼��������
	_undoManager->record(area.deck.back());
	//���ƶ�������++
	area.topNums++;
	//�û��Ѷ�����
	area.topCard = area.deck.back();
	CCLOG("update top card face to %d",area.topCard.getFace());
	//��������������
	area.deck.pop_back();
	//��ͼ����
	_stackView->moveToStackTop(area.topNums);
	return true;
}

bool StackController::moveUndo(const CardModel& model)
{
	//��ͼ����
	_stackView->moveUndo(model);
	return true;
}
