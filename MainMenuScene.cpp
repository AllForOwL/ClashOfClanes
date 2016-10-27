#include "MainMenuScene.h"
#include "GameScene.h"
#include "GameOverScene.h"

USING_NS_CC;

Scene *MainMenuScene::createScene()
{
	auto scene = Scene::create();

	auto layer = MainMenuScene::create();

	scene->addChild(layer);

	return scene;
}

bool MainMenuScene::init()
{
	if (!Layer::init())	// if layer not create exit from function
	{
		return false;
	}

	Size _visibleSize = Director::getInstance()->getVisibleSize();

	this->setColor(Color3B(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0));

	auto _itemStartGame = MenuItemFont::create("Start game", CC_CALLBACK_1(MainMenuScene::GoToGameScene, this));

	auto menu = Menu::create(_itemStartGame, NULL);
	menu->setPosition(_visibleSize.width / 2, _visibleSize.height / 2 + 50);
	this->addChild(menu);

	return true;
}

void MainMenuScene::GoToGameScene(cocos2d::Ref* ref)
{
	auto _gameScene = GameScene::createScene();

	srand(time(NULL));
	auto reScene = TransitionFade::create(2.0f, _gameScene, Color3B(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0));
	Director::getInstance()->replaceScene(reScene);
}