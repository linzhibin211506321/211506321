#include "Cannon.h"
#include <cmath>
USING_NS_CC;
using namespace std;
//f
Cannon::Cannon(void)
{
}

Cannon::~Cannon(void)
{
}

Cannon* Cannon::create(CannonType type)//根据炮台的类型创造出炮台对象，并加载炮台资源到内存中。
{
	Cannon* cannon = new Cannon();
	if(cannon && cannon->init(type))//完成炮台对象的动作初始化。
	{
		cannon->autorelease();
		return cannon;
	}
	else
	{
		CC_SAFE_DELETE(cannon);
		return NULL;
	}
}

bool Cannon::init(CannonType type)
{
	if(!CCNode::init()){
		return false;
	}
	_cannonSprites = CCArray::createWithCapacity(k_Cannon_Count);
	for(int i = k_Cannon_Type_1; i < k_Cannon_Count; i++)
	{	
		CCString* fileName = CCString::createWithFormat("actor_cannon1_%d1.png", i+1);
		CCSprite* cannonSprite = CCSprite::createWithSpriteFrameName(fileName->getCString());
		_cannonSprites->addObject(cannonSprite);
		cannonSprite->setAnchorPoint(ccp(0.5,0.26));//设置炮台的锚点坐标
	}
	CC_SAFE_RETAIN(_cannonSprites);
	setType(type);
	return true;
}

CannonType Cannon::getType()
{
	return _type;
}

void Cannon::setType(CannonType var)//根据传入参数type设置炮台类型。
{
	if(_type == var)
	{
		return;
	}
	if(var < k_Cannon_Type_1)
	{
		var = (CannonType)(k_Cannon_Count-1);
	}else if(var >= k_Cannon_Count)
	{
		var = k_Cannon_Type_1;
	}
	removeChildByTag(_type);//再调整后，将之前的炮台精灵从节点中移除。
	CCSprite* sprite = (CCSprite*) _cannonSprites->objectAtIndex(var);
	addChild(sprite,0,var);
	_type = var;
}

CCSize Cannon::getSize()
{
	CCSprite* cannonSprite = (CCSprite*) _cannonSprites->objectAtIndex(_type);
	return cannonSprite->getContentSize();
}
float Cannon::getFireRange()//根据炮台的类型计算出炮台的射程。
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	double temp = pow(winSize.width, 2) + pow(winSize.height, 2);
	double result = sqrt(temp);
	return result/7*(_type+1);
}

//选择炮台，让炮口对准targe的方向
void Cannon::aimAt(CCPoint target)
{
	if(target.y < 0)
	{
		target.y = 0.0f;
	}
	CCPoint location = getParent()->convertToWorldSpace(getPosition());//1.	获取炮台当前位置
	float angle = ccpAngleSigned(ccpSub(target, location), CCPointMake(0, 1));//算出要偏移的角度
	this->setRotation(CC_RADIANS_TO_DEGREES(angle));//改变炮台的朝向。
}
