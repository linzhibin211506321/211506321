//����ʵ�ִ����̨����̨�л���ť��
#include "CannonLayer.h"
#include "PersonalAudioEngine.h"

CannonLayer::CannonLayer(void)
{
}

CannonLayer::~CannonLayer(void)
{
}

bool CannonLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	_weapon = Weapon::create((CannonType)0);//ͨ��Weapon ::create()����������Weapon�Ķ���ֵ��_weapon��
	this->addChild(_weapon,1);
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();//ͨ��������CCDirector�ĳ�Ա����getWinSize()��ȡ��Ӧ�ó���Ĵ��ڴ�С��
	_weapon->setPosition(ccp(winSize.width/2 - 18, 0));//������λ�����õ���ײ�����λ�á�

	//�����������̨�Ĳ˵��
	_addMenuItem = CCMenuItemImage::create(
		"ui_button_66-ipadhd.png",
		"ui_button_66-ipadhd.png",
		this, menu_selector(CannonLayer::switchCannonCallback));

	//������������̨�Ĳ˵��
	_subMenuItem = CCMenuItemImage::create(
		"ui_button_64-ipadhd.png",
		"ui_button_64-ipadhd.png",
		this, menu_selector(CannonLayer::switchCannonCallback));

	//���ڲ˵�������ꡣ
	CCMenu* menu = CCMenu::create(_subMenuItem, _addMenuItem, NULL);
	menu->alignItemsHorizontallyWithPadding(120);
	addChild(menu,0);
	menu->setPosition(ccp(winSize.width/2-20, _addMenuItem->getContentSize().height/2));
	return true;
}

//�л���ǰ����̨���͡�
void CannonLayer::switchCannonCallback(cocos2d::CCObject* sender)
{
	CannonOperate operate = k_Cannon_Operate_Up;
	if((CCMenuItemImage*)sender == _subMenuItem)
	{
		operate = k_Cannon_Operate_Down;
	}
	_weapon->changeCannon(operate);
	PersonalAudioEngine::sharedEngine()->playEffect("bgm_button.aif");//�л���̨ʱ����Ч
}

//��ת��̨�����ڿڶ�׼targe�ķ���
void CannonLayer::aimAt(CCPoint target)
{
	_weapon->aimAt(target);//��ת��̨��
}
//�ӵ���׼targe�ķ���
bool CannonLayer::shootTo(CCPoint target)
{
	return _weapon->shootTo(target);//�����ӵ���
}
