#include "MainMenuScene.h"


USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();

	auto background = Sprite::create("HelloWorld.png");
 
	background->setPosition(Point((visibleSize.width /2), (visibleSize.height /2)));
 
	addChild(background, 0);

	auto menuTitle = MenuItemImage::create("Game_Title.png", "Game_Title.png");
 
	auto playItem = MenuItemImage::create("Play_Button.png", "Play_Button(Click).png", CC_CALLBACK_1(MainMenuScene::goToGameScene, this));
 
	auto menu = Menu::create(menuTitle, playItem, NULL);
 
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
	this->addChild(menu, 1);

    return true;
}

void MainMenuScene::goToGameScene(Ref *pSender) {
	 auto scene = GameScene::createScene();
 
	 Director::getInstance()->replaceScene(scene);
}


