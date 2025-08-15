#include "PlayFieldView.h"

bool PlayFieldView::init()
{
	if (!Layer::init())
	{
		return false;
	}

}
void PlayFieldView::drawBorder(const Size& visibleSize) {
	//����DrawNode���Ʊ߿�
	auto drawNode = DrawNode::create();
	float borderWidth = 5.0f; // �߿���
	Color4F borderColor = Color4F::RED; // �߿���ɫ

	//���ƾ��α߿�(����Layer��ê��)
	Vec2 vertices[4] = {
		Vec2(0, 0),
		Vec2(visibleSize.width, 0),
		Vec2(visibleSize.width, visibleSize.height),
		Vec2(0, visibleSize.height)
	};
	drawNode->drawPoly(vertices, 4, true, borderColor);

	//��ӵ�Layer
	this->addChild(drawNode, INT_MAX); // ȷ���߿������ϲ�
}
CardView* PlayFieldView::getCardViewByTagId(int tagId) const
{
	auto cardView = dynamic_cast<CardView*>(this->getParent()->getChildByTag(tagId));
	if (!cardView) {
		CCLOG("Error:  PlayFieldView::getCardViewByTagId failed! tagId:%d invaild!", tagId);
	}
	return  cardView;
}
void PlayFieldView::moveToStackTop(int plieIndex, int zOrder)
{
	auto& _cardTagIds = _pileCardTagIds.at(plieIndex);
	//����Ƿ�����
	if (_cardTagIds.empty()) {
		CCLOG("PlayField empty");
		return;
	}
	const auto card = getCardViewByTagId(_cardTagIds.top());

	//card->setGlobalZOrder(zOrder);
	card->setLocalZOrder(zOrder);
	const auto originPos = card->getPosition();
	const Vec2 targetPos = this->getParent()->convertToNodeSpace(Vec2(700, 350));

	// ����ص�����
	auto callback = CallFunc::create([=]() {
		CCLOG("Moved CardView: (%.1f, %.1f) -> (%.1f, %.1f),zOrder:%d,globalZOrder:%d",
		originPos.x, originPos.y, card->getPosition().x, card->getPosition().y, card->getZOrder(), card->getGlobalZOrder());
		});
	// �����������У��ƶ� + �ص�
	card->runAction(Sequence::create(
		MoveTo::create(0.4f, targetPos),
		callback, nullptr));
	card->setClickable(false);
	_cardTagIds.pop();
}
void PlayFieldView::moveUndo(const CardModel& model)
{
	auto& _cardTagIds = _pileCardTagIds.at(model.getPlayIndex());
	_cardTagIds.push(model.getId());
	const auto card = getCardViewByTagId(_cardTagIds.top());
	card->setClickable(true);
	const auto originPos = card->getPosition();
	const Vec2 targetPos = model.getPosition();
	// ����ص�����
	auto callback = CallFunc::create([=]() {
		CCLOG("Moved CardView: (%.1f, %.1f) -> (%.1f, %.1f)",
		originPos.x, originPos.y, card->getPosition().x, card->getPosition().y);
	card->setLocalZOrder(_cardTagIds.size());
		});

	// �����������У��ƶ� + �ص�
	card->runAction(Sequence::create(
		MoveTo::create(0.3f, targetPos),
		callback, nullptr));
}
void PlayFieldView::unMatched(int tagId) const
{
	getCardViewByTagId(tagId)->shake();
}
void PlayFieldView::setUpWithCardModels(const GameModel& models)
{
	//���������Ԫ��
	this->removeAllChildren();
	_pileCardTagIds.resize(models.getPlayFieldPile().size());

	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const Vec2 origin = Director::getInstance()->getVisibleOrigin();
	const auto layer = LayerColor::create(
		Color4B(139, 69, 19, 255), // ��ɫ (RGB: 139,69,19)
		visibleSize.width,
		visibleSize.height * 2 / 3
	);
	this->setPosition(origin.x, origin.y + visibleSize.height / 3);
	this->addChild(layer, INT_MIN);
	//this->drawBorder(visibleSize);
	auto& cardModels = models.getPlayFieldPile();
	for (auto& items : cardModels) {
		int i = 0;
		for (auto cardModel : items.cards) {
			addCardView(cardModel, i++);
		}
	}
}

void PlayFieldView::addCardView(const CardModel& model, int zOrder)
{
	auto cardView = CardView::create(model);
	if (cardView) {
		CCLOG("addCardView CardModel:position:x=%.1f y=%.1f", model.getPosition().x, model.getPosition().y);
		//���õ���ص�
		cardView->setCallBack(_onClickCallback);
		//�洢�ƶ�tagsId;
		_pileCardTagIds.at(model.getPlayIndex()).push(model.getId());
		auto ptr = this->getParent();
		auto gameView = dynamic_cast<GameView*>(this->getParent());
		gameView->addChild(cardView, zOrder, model.getId());
	}
	else
	{
		CCLOG("PlayFieldView::addCardView Error: addCardView Failed");
	}

}
