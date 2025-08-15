#include "StackView.h"

bool StackView::init()
{
	if (!Layer::init())
	{
		return false;
	}
}

void StackView::setUpWithCardModels(const GameModel& models)
{
	//���������Ԫ��
	this->removeAllChildren();
	this->_stackNums = models.getStackArea().deck.size();
	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const Vec2 origin = Director::getInstance()->getVisibleOrigin();
	const auto layer = LayerColor::create(
		Color4B(128, 0, 128, 255), // ��ɫ (RGB: 128,0,128)
		visibleSize.width,
		visibleSize.height / 3
	);
	this->addChild(layer, INT_MIN);
	this->setPosition(origin);

	//this->drawBorder(visibleSize);
	//����deck
	auto deck = models.getStackArea().deck;
	for (auto& model : deck) {
		addCardView(model);
	}
}

void StackView::addCardView(const CardModel& model)
{
	auto cardView = CardView::create(model);
	_cardTagIds.push(model.getId());
	if (cardView) {
		//���õ���ص�
		cardView->setCallBack(_onClickCallback);
		this->getParent()->addChild(cardView, model.getZOrder(), model.getId());
	}
	else
	{
		CCLOG("PlayFieldView::addCardView Error: addCardView Failed");
	}
}

void StackView::moveToStackTop(int zOrder)
{
	if (_cardTagIds.empty()) {
		CCLOG("Stack empty");
		return;
	}
	const auto card = dynamic_cast<CardView*>(this->getParent()->getChildByTag(_cardTagIds.top()));
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
		MoveTo::create(0.3f, targetPos),
		callback, nullptr));
	card->setClickable(false);
	_cardTagIds.pop();
}
void StackView::moveUndo(const CardModel& model)
{
	_cardTagIds.push(model.getId());

	const auto card = dynamic_cast<CardView*>(this->getParent()->getChildByTag(_cardTagIds.top()));
	card->setClickable(true);
	const auto originPos = card->getPosition();
	const Vec2 targetPos = this->getParent()->convertToNodeSpace(model.getPosition());
	// ����ص�����
	auto callback = CallFunc::create([=]() {
		CCLOG("undo Moved CardView: (%.1f, %.1f) -> (%.1f, %.1f)",
		originPos.x, originPos.y, card->getPosition().x, card->getPosition().y);

		});

	card->setLocalZOrder(_cardTagIds.size());
	// �����������У��ƶ� + �ص�
	card->runAction(Sequence::create(
		MoveTo::create(0.3f, targetPos),
		callback, nullptr));
}
void StackView::drawBorder(const Size& visibleSize)
{
	//����DrawNode���Ʊ߿�
	auto drawNode = DrawNode::create();
	float borderWidth = 5.0f; // �߿���
	Color4F borderColor = Color4F::RED; // �߿���ɫ

	//���ƾ��α߿򣨿���Layer��ê�㣩
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




