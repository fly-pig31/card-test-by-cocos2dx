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
	//���ݲ���
	auto& cards = model.getPlayFieldPile().at(playFiledsIndex).cards;
	auto& topCard = model.getStackArea().topCard;
	auto targetCard = cards.back();
	if (std::abs(topCard.getFace() - targetCard.getFace())!=1) {
		CCLOG("top card face % and face %d not match!", topCard.getFace(), targetCard.getFace());
		_playFieldView->unMatched(tagId);
		return false;
	}
	//��¼��������
	_undoManager->record(targetCard);
	//���ƶ�������++
	model.getStackArea().topNums++;
	//�û��Ѷ�����
	topCard = targetCard;
	CCLOG("update top card face to %d", topCard.getFace());
	//���ƶ��е����ƶ��Ŀ�
	cards.pop_back();
	//��ͼ����
	_playFieldView->moveToStackTop(playFiledsIndex, model.getStackArea().topNums);
	return true;
}

bool PlayFieldController::moveUndo(const CardModel&model)
{
	//��ͼ����
	_playFieldView->moveUndo(model);
	return true;
}

