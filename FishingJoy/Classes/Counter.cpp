//金币展示。
//用来展示数字用的组件类，由调用者将数字传入，本类完成数字的展示。一个对象表示一位数字。
#include "Counter.h"

//定义一个枚举类型表示动作的类型。
enum{
    k_Counter_Action = 0
};

//根据提供的数字创建Counter对象。
Counter* Counter::create(CCArray* presenters, int digit/* = 0 */)
{
	CCAssert(digit>=0 && digit<=10,"金币数字只能为0至9之间的数字");
    Counter *counter = new Counter;
	if (counter && counter->init(presenters,digit) )
	{   
		counter->autorelease();
		return counter;
	}
	else
	{
		CC_SAFE_DELETE(counter);
		return NULL;
	}

}
bool Counter::init(CCArray* presenters, int digit/* = 0 */)
{
	if (!CCNode::init())
	{
		return false;
	}
    _presenters = CCNode::create();
	//CCSize size = ((CCNode *) presenters->objectAtIndex(0))->getContentSize();
	//   for (int i = 0; i < 10; i++) {
	//       CCNode* node = (CCNode*)presenters->objectAtIndex(i);
	//       int y = node->getContentSize().height*i;
	//       node->setPosition(CCPointMake(0, y));
	//       _presenters->addChild(node, 0, i);
	//	_presenters->addChild(node,0,i);
	//	node->setPosition(ccp(0,size,height * i));
	//   }
	CCObject *obj = NULL;
	int i = 0;
	CCARRAY_FOREACH(presenters,obj)
	{
		CCNode *node = (CCNode *)obj;
		_presenters->addChild(node,0,i);
		node->setPosition(ccp(0,node->getContentSize().height * i));
		i++;
	}
    this->addChild(_presenters);
    setDigit(digit);
    return true;
}
//修改数据成员_digit的值。
void Counter::setDigit(int digit)
{
    if(_digit != digit)
	{
        _digit = digit;
        animation();
    }
}
int Counter::getDigit()
{
    return _digit;
}

//改变数字时播放滚动动画。
void Counter::animation()
{
	CCNode *node = (CCNode *)_presenters->getChildByTag(_digit);
    CCPoint position = node->getPosition();
    _presenters->stopActionByTag(k_Counter_Action);
    CCMoveTo* moveTo = CCMoveTo::create(0.5f, ccp(0, -position.y));
	moveTo->setTag(k_Counter_Action);
    _presenters->runAction(moveTo);
}

//显示指定的数字。
void Counter::visit()
{
    glEnable(GL_SCISSOR_TEST);//开始遮罩效果。
    CCSize size = ((CCNode *)_presenters->getChildByTag(_digit))->getContentSize();//找到当前要显示的数字对应的图片。
    CCPoint position = getParent()->convertToWorldSpace(getPosition());
    glScissor((position.x - size.width / 2) * 0.4, (position.y - size.height / 2) * 0.4, size.width* 0.4, size.height* 0.4);//设置遮罩区域。
    CCNode::visit();//显示数字。
    glDisable(GL_SCISSOR_TEST);
}