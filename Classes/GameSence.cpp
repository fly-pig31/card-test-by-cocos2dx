#include "GameSence.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "controllers/GameController.h"
using namespace cocos2d;
cocos2d::Scene* GameScene::createScene()
{
	return GameScene::create();
}
static void problemLoading(const char* filename) noexcept
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto gameController = GameController::create();
	if (!gameController) {
		problemLoading("Failed to create GameController.");
		return false;
	}
	this->addChild(gameController);

	return true;
}
/// <summary>
/// 弹出当前场景
/// </summary>
/// <param name="pSender"></param>
void GameScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}