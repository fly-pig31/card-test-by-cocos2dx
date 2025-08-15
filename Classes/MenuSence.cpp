#include "MenuSence.h"
#include "SimpleAudioEngine.h"
#include "GameSence.h"
USING_NS_CC;
cocos2d::Scene* MenuScene::createScene()
{
    return MenuScene::create();
}
// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
bool MenuScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 1. ����"startGame"���ֱ�ǩ��Ϊ��ť
    auto startLabel = Label::createWithTTF("startGame", "fonts/Marker Felt.ttf", 36);

    // 2. �����˵���
    auto startItem = MenuItemLabel::create(startLabel, CC_CALLBACK_1(MenuScene::menuStartCallback, this));

    // 3. ����������ɫ�仯Ч��
    startItem->setColor(Color3B(200, 200, 200)); // ��ʼ��ɫ

    // 4. ����λ��
    startItem->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    // 5. �����˵�����Ӱ�ť
    auto menu = Menu::create(startItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // 6. ��ӵ������Ч��
    auto scaleAction = Sequence::create(
        ScaleTo::create(0.8f, 1.1f),
        ScaleTo::create(0.8f, 1.0f),
        nullptr
    );
    startLabel->runAction(RepeatForever::create(scaleAction));

    return true;
}

void MenuScene::menuStartCallback(cocos2d::Ref* pSender)
{
    //�����л�
    auto scene = GameScene::createScene();
    Director::getInstance()->pushScene(scene);
}
