#include "ProgressBar.h"

enum{
	k_Progress_Action = 0
};

//��̬��Ա����������ProgressBar����.
ProgressBar* ProgressBar::create(ProgressDelegate* target, CCSprite *sprite) //target:Э�����;sprite������������ʱ��ʾ��ͼƬ��
{
	ProgressBar* pg = new ProgressBar();
	pg->autorelease();
	pg->init(target, sprite);
	return pg;
}

//���������浽��Ӧ�����ݳ�Ա�С�
bool ProgressBar::init(ProgressDelegate* target, CCSprite *sprite)
{
	CCProgressTimer::initWithSprite(sprite);
	this->setTarget(target);
	this->setType(kCCProgressTimerTypeBar);
	this->setMidpoint(CCPointMake(0, 0.5));
	this->setSpeed(1.0f);
	this->setBarChangeRate(CCPointMake(1, 0));
	return true;
}

//�����������ľ��롣
void ProgressBar::progressBy(float delta)
{
	float maxPercentage = 100.0f;//�������ٷֱ�
	bool isFinished = false;
	float nextPercentage = delta + this->getPercentage();
	if(nextPercentage >= maxPercentage){
		nextPercentage = maxPercentage;
		isFinished = true;
	}
	CCArray* actions = CCArray::createWithCapacity(2);
	float duration = delta/this->getSpeed();
	CCProgressTo* to = CCProgressTo::create(duration, nextPercentage);
	actions->addObject(to);

	if(isFinished){
		CCCallFunc* callfunc = CCCallFunc::create(this, callfunc_selector(ProgressBar::loadingFinished));
		actions->addObject(callfunc);
	}
	CCSequence* seq = CCSequence::create(actions);
	CCCallFunc* updateCallFunc = CCCallFunc::create(this, callfunc_selector(ProgressBar::updatePercentage));
	updateCallFunc->setDuration(duration);
	CCSpawn* spawn = CCSpawn::createWithTwoActions(seq, updateCallFunc);
	spawn->setTag(k_Progress_Action);
	this->runAction(spawn);
}

//�����������ñ���ͼƬ��
void ProgressBar::setBackground(CCNode* bg)
{
	this->removeChild(_background,true);
	_background = bg;
	CCSize size = this->getSprite()->getContentSize();
	_background->setPosition(CCPointMake(size.width*0.5, size.height*0.46));
	this->addChild(_background, -1);
}

//�����������ñ���ͼƬ��
void ProgressBar::setForeground(CCNode* fg)
{	
	this->removeChild(_foreground,true);
	_foreground = fg;
	CCSize size = this->getSprite()->getContentSize();
	_foreground->setPosition(CCPointMake(size.width*0.5, size.height*0.5));
	this->addChild(_foreground, 1);
}

void ProgressBar::updatePercentage()
{
	_target->progressPercentageSetter(this->getPercentage());
}

void ProgressBar::loadingFinished()
{
	_target->loadingFinished();
}

void ProgressBar::progressTo(float destination)
{
	float delta = destination-this->getPercentage();
	this->progressBy(delta);
}
