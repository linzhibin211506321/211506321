//ʵ����ͣ�Ĺ��ܡ�
#include "PanelLayer.h"
#include "GameScene.h"
#include "ScheduleCountDown.h"
PanelLayer::PanelLayer(void)
{

}

PanelLayer::~PanelLayer(void)
{

}

//��ʼ������Ӳ˵���˵�����ң�����ʱ��
bool PanelLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	_goldCounter = GoldCounterLayer::create(0);
	addChild(_goldCounter);
    _goldCounter->setPosition(ccp(50,1200));//������ڵ�λ��

	ScheduleCountDown* countDown = ScheduleCountDown::create(this);
	_scheduleLabel = CCLabelTTF::create("60", "Thonburi", 70);//����ʱ
	_scheduleLabel->addChild(countDown);
	this->addChild(_scheduleLabel);
	_scheduleLabel->setPosition(ccp(50, 1250));//����ʱ���ڵ�λ��

	CCMenuItemSprite* pause = CCMenuItemSprite::create(CCSprite::create("button_other_003-ipadhd.png"), 
							CCSprite::create("button_other_004-ipadhd.png"),
							this, menu_selector(PanelLayer::pause));

	CCMenu* menu = CCMenu::create(pause, NULL);
	this->addChild(menu);

	CCSize pauseSize = pause->getContentSize();
	menu->setPosition(CCPointMake(winSize.width-pauseSize.width*0.5, pauseSize.height*0.5));

	return true;
}

//�ò���ͣ�˵�����Ӧ������
void PanelLayer::pause(CCObject *sender)
{
	GameScene* gameScene = (GameScene*)this->getParent();
	gameScene->pause();
}

//����ָ���ĳ��ȴ����ӷ��������ݵ�data�С�
void PanelLayer::setScheduleNumber(int number)
{
	_scheduleLabel->setString(CCString::createWithFormat("%d",number)->getCString());
}

//����ʱ���ڵ������õĺ�����
void PanelLayer::scheduleTimeUp()
{
	_scheduleLabel->setVisible(false);
	GameScene* gameScene = (GameScene*)this->getParent();
	gameScene->scheduleTimeUp();
}
