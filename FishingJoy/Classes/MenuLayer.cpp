#include "MenuLayer.h"
#include "GameScene.h"
USING_NS_CC;

bool MenuLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	this->createBackground();
	this->createMenu();
	return true;
}

//创建出菜单的背景层，用来遮挡住游戏主界面
void MenuLayer::createBackground()
{
	CCLayerColor* colorBackground = CCLayerColor::create(ccc4(0, 0, 0, 128));//创建出一个CCLayerColor的对象（黑色半透明）
	this->addChild(colorBackground);
}
void MenuLayer::createMenu()
{
	int fontSize = 32;
	CCString* fontName = CCString::create("Thonburi");

	CCMenuItemLabel* resume = CCMenuItemLabel::create(CCLabelTTF::create("Resume", fontName->getCString(), fontSize), this, menu_selector(MenuLayer::resume));

	CCMenuItemLabel* mainMenu = CCMenuItemLabel::create(CCLabelTTF::create("Main Menu", fontName->getCString(), fontSize), this, menu_selector(MenuLayer::mainMenu));

	//将soundOn和soundOff创建出来，然后再用CCMenuItemToggle::createWithTarget将这两个菜单项关联起来。
	CCMenuItemLabel* soundOn = CCMenuItemLabel::create(CCLabelTTF::create("Sound On", fontName->getCString(), fontSize));
	CCMenuItemLabel* soundOff = CCMenuItemLabel::create(CCLabelTTF::create("Sound Off", fontName->getCString(), fontSize));
	_sound = CCMenuItemToggle::createWithTarget(this, menu_selector(MenuLayer::sound), soundOff, soundOn, NULL);
	//将soundOn和soundOff创建出来，然后再用CCMenuItemToggle::createWithTarget将这两个菜单项关联起来。
	CCMenuItemLabel* musicOn = CCMenuItemLabel::create(CCLabelTTF::create("Music On", fontName->getCString(), fontSize));
	CCMenuItemLabel* musicOff = CCMenuItemLabel::create(CCLabelTTF::create("Music Off", fontName->getCString(), fontSize));
	_music = CCMenuItemToggle::createWithTarget(this, menu_selector(MenuLayer::music), musicOff, musicOn, NULL);

	CCMenuItemLabel* reset = CCMenuItemLabel::create(CCLabelTTF::create("Reset", fontName->getCString(), fontSize), this, menu_selector(MenuLayer::reset));

	CCMenu* menu = CCMenu::create(resume, mainMenu, _sound, _music, reset, NULL);
	menu->alignItemsVerticallyWithPadding(10);
	this->addChild(menu);
}
//响应菜单 
void MenuLayer::resume(cocos2d::CCObject* pSender)
{
	GameScene* gameScene = (GameScene*)this->getParent();
	gameScene->resume();
}

void MenuLayer::mainMenu(cocos2d::CCObject* pSender)
{
}
void MenuLayer::sound(cocos2d::CCObject* pSender)
{
}
void MenuLayer::music(cocos2d::CCObject* pSender)
{
}
void MenuLayer::reset(cocos2d::CCObject* pSender)
{
}
void MenuLayer::setSoundAndMusicVolume(float soundVolume, float musicVolume)
{
	bool soundFlag = soundVolume>0;
	bool musicFlag = musicVolume>0;
	_sound->setSelectedIndex(soundFlag);
	_music->setSelectedIndex(musicFlag);
}
