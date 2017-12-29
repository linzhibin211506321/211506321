#include "Bullet.h"
#include "FishNet.h"

//定义一个无名枚举类型表示子弹的移动动作。
enum{
	k_Bullet_Action = 0
};

Bullet::Bullet(void)
{
}

Bullet::~Bullet(void)
{
}

bool Bullet::init()//子弹对象创建后所进行的初始化工作。
{
	if(!CCNode::init())
	{
		return false;
	}
	CCString* fileName = CCString::createWithFormat("weapon_bullet_%03d.png", 1);
	_bulletSprite = CCSprite::createWithSpriteFrameName(fileName->getCString());
	_bulletSprite->setAnchorPoint(ccp(0.5,1.0));
	this->addChild(_bulletSprite);
	return true;
}

//根据炮台的类型获得子弹的速度。
float Bullet::getSpeed(int type)
{
	float speed = 650;
	switch(type)
	{
	case 0:
		speed = 650;
		break;
	case 1:
		speed = 650;
		break;
	case 2:
		speed = 470;
		break;
	case 3:
		speed = 450;
		break;
	case 4:
		speed = 660;
		break;
	case 5:
		speed = 420;
		break;
	case 6:
		speed = 400;
		break;
	default:
		break;
	}
	return speed;
}

//子弹飞行结束时所做的处理。
void Bullet::end()
{
	stopActionByTag(k_Bullet_Action);//停止子弹的移动动作。
	this->setVisible(false);//将子弹设为不可见
	FishNet *fishNet = (FishNet *)getUserObject();
	fishNet->showAt(getPosition(),getTag());
}

//子弹的飞行处理。
void Bullet::flyTo(CCPoint targetInWorldSpace, int type)
{
	CCPoint startInNodeSpace = CCPointZero;
	CCPoint startInWorldSpace = this->getParent()->convertToWorldSpace(startInNodeSpace);
	CCPoint targetInNodeSpace = this->getParent()->convertToNodeSpace(targetInWorldSpace);

	this->setPosition(startInNodeSpace);
	this->setVisible(true);

	float angle = ccpAngleSigned(ccpSub(targetInWorldSpace, startInWorldSpace), CCPointMake(0, 1));
	this->setRotation(CC_RADIANS_TO_DEGREES(angle));
	this->setTag(type);
	CCString* bulletFrameName = CCString::createWithFormat("weapon_bullet_%03d.png", type + 1);
	_bulletSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(bulletFrameName->getCString()));

	float duration = ccpDistance(targetInWorldSpace, startInWorldSpace) / getSpeed(type);//计算出飞行时间。

	CCMoveTo* moveTo = CCMoveTo::create(duration, targetInNodeSpace);
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Bullet::end));
	CCSequence* sequence = CCSequence::create(moveTo, callFunc, NULL);
	sequence->setTag(k_Bullet_Action);
	runAction(sequence);
}

//获取当前炮弹的位置。
CCPoint Bullet::getCollosionPoint()
{
	return getParent()->convertToWorldSpace(getPosition());
}