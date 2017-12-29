#include "Fish.h"

enum{
	k_Action_Animate = 0,
	k_Action_MoveTo
};
Fish::Fish(void)
{
}

Fish::~Fish(void)
{
}

Fish* Fish::create(FishType type)
{
	Fish* fish = new Fish;
	if (fish && fish->init(type))
	{
		fish->autorelease();
		return fish;
	}
	else
	{
		CC_SAFE_DELETE(fish);
		return NULL;
	}
}
//指定鱼的类型，并为其精灵指定动作
bool Fish::init(FishType type)
{
	do 
	{
		if (!CCNode::init())
		{
			return false;
		}
		if (type < k_Fish_Type_SmallFish || type >= k_Fish_Type_Count)
		{
			type = k_Fish_Type_SmallFish;
		}
		setType(type);
		CCString* animationName = CCString::createWithFormat("fish_animation_%02d", _type + 1);
		//4.	从动画缓冲区里面找到该动画名字对应的动画
		CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName(animationName->getCString());
		CC_BREAK_IF(!animation);
		CCAnimate* animate = CCAnimate::create(animation);
		_fishSprite = CCSprite::create();
		addChild(_fishSprite);

		_fishSprite->runAction(CCRepeatForever::create(animate));//给精灵对象执行动作
		return true;
	} while (0);
	return false;
}
//获得鱼的得分，即捕到某种鱼可以获得的金币数
int Fish::getScore(void)
{
	return 0;
}
//int Fish::getSpeed(void)
int Fish::getSpeed(void)
{
	return 300;
}
//获取当前鱼所在的区域。
CCRect Fish::getCollisionArea()
{
	CCSize size = _fishSprite->getContentSize();//算出鱼精灵的大小。
	CCPoint pos = getParent()->convertToWorldSpace(getPosition());
	return CCRect(pos.x - size.width / 2, pos.y - size.height/2, size.width, size.height);//构造出矩形并返回。（被捕获到的有效范围）
}

//鱼被捕捉后的动画效果.
void Fish::beCaught(){
	stopActionByTag(k_Action_MoveTo);
	CCCallFunc *callFunc = CCCallFunc::create(this,callfunc_selector(Fish::beCaught_CallFunc));
	CCSequence *sequence = CCSequence::create(CCDelayTime::create(1.0f),callFunc,NULL);//创建出一个延迟对象delayTime。
	CCBlink *blink = CCBlink::create(1.0f, 8);//创建一个闪烁的动作对象。
	CCSpawn *spawn = CCSpawn::create(sequence, blink, NULL);
	_fishSprite->runAction(spawn);
}

//鱼动画展示结束后执行的函数。
void Fish::beCaught_CallFunc()
{
	if(isRunning())
	{
		getParent()->removeChild(this,false);
	}
}

//直线移动，将鱼移动到指定的位置destination。
void Fish::moveTo(CCPoint destination)
{
	CCPoint point = getParent() ->convertToWorldSpace(this->getPosition());
	float duration = ccpDistance(destination, point) / getSpeed();
	CCMoveTo* moveTo = CCMoveTo::create(duration ,destination);//移动。
	CCCallFunc* callfunc = CCCallFunc::create(this, callfunc_selector(Fish::moveEnd));
	CCFiniteTimeAction *sequence = CCSequence::create(moveTo, callfunc, NULL);
	sequence->setTag(k_Action_MoveTo);
	this->runAction(sequence);
}

//鱼移动结束后将鱼从鱼层中删除。
void Fish::moveEnd(){
	if (isRunning())
	{
		this->stopActionByTag(k_Action_MoveTo);
		getParent()->removeChild(this,false);
	}
}

CCSize Fish::getSize(){
	return _fishSprite->displayFrame()->getRect().size;
}