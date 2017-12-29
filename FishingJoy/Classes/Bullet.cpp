#include "Bullet.h"
#include "FishNet.h"

//����һ������ö�����ͱ�ʾ�ӵ����ƶ�������
enum{
	k_Bullet_Action = 0
};

Bullet::Bullet(void)
{
}

Bullet::~Bullet(void)
{
}

bool Bullet::init()//�ӵ����󴴽��������еĳ�ʼ��������
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

//������̨�����ͻ���ӵ����ٶȡ�
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

//�ӵ����н���ʱ�����Ĵ���
void Bullet::end()
{
	stopActionByTag(k_Bullet_Action);//ֹͣ�ӵ����ƶ�������
	this->setVisible(false);//���ӵ���Ϊ���ɼ�
	FishNet *fishNet = (FishNet *)getUserObject();
	fishNet->showAt(getPosition(),getTag());
}

//�ӵ��ķ��д���
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

	float duration = ccpDistance(targetInWorldSpace, startInWorldSpace) / getSpeed(type);//���������ʱ�䡣

	CCMoveTo* moveTo = CCMoveTo::create(duration, targetInNodeSpace);
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Bullet::end));
	CCSequence* sequence = CCSequence::create(moveTo, callFunc, NULL);
	sequence->setTag(k_Bullet_Action);
	runAction(sequence);
}

//��ȡ��ǰ�ڵ���λ�á�
CCPoint Bullet::getCollosionPoint()
{
	return getParent()->convertToWorldSpace(getPosition());
}