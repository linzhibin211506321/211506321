//封装渔网的类，提供渔网对象的创建。
#include "FishNet.h"


FishNet::FishNet(void)
{
}

FishNet::~FishNet(void)
{
}

//渔网对象创建后所进行的初始化工作。
bool FishNet::init()
{
	if(!CCNode::init())
	{
		return false;
	}
	CCString *fileName=CCString::createWithFormat("weapon_net_%03d.png",1);
	_fishNetSprite = CCSprite::createWithSpriteFrameName(fileName->getCString());
	_fishNetSprite->setAnchorPoint(ccp(0.5, 0.5));
	addChild(_fishNetSprite);
	return true;
}
float FishNet::getSpeed(int type)
{
	float speed=650;
	switch(type)
	{
	case 0:
		speed=650;
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

//将渔网在指定的位置显示。
void FishNet::showAt(CCPoint pos,int type)//Pos：渔网要显示的位置。type：炮台的类型。
{
	setVisible(true);
	setPosition(pos);
	CCString *fishNetFrameName = CCString::createWithFormat("weapon_net_%03d.png", type + 1);
	this->_fishNetSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fishNetFrameName->getCString()));
	stopAllActions();
	CCSequence *sequence = CCSequence::create(CCDelayTime::create(1), CCHide::create(),NULL);

	CCParticleSystemQuad *particle = (CCParticleSystemQuad *)getUserObject();
	particle->setPosition(pos);
	particle->resetSystem();
	runAction(sequence);
}

//获取当前渔网所在的区域。
CCRect FishNet::getCollisionArea()
{
	CCSize size = _fishNetSprite->getContentSize();//先求出鱼网当前的位置并转换为世界坐标。
	CCPoint pos = getParent()->convertToWorldSpace(getPosition());//算出鱼网精灵的大小。
	return CCRect(pos.x - size.width / 2, pos.y - size.height/2, size.width, size.height);//构造出矩形并返回。
}