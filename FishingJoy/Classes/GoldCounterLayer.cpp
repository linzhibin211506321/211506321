//����ǰ�����ֵͨ���ýڵ������װ��չʾ��
#include "GoldCounterLayer.h"
#include "Counter.h"
#include "StaticData.h"
#define NUM_COUNTER 8//���Ľ��λ��

//�����ṩ�����ִ���GoldCounterLayer����
GoldCounterLayer* GoldCounterLayer::create(int number)
{
    GoldCounterLayer* gold = new GoldCounterLayer();

	if (gold && gold->init(number))
	{
		gold->autorelease();
		return gold;
	}
	else
	{
		CC_SAFE_DELETE(gold);
		return NULL;
	}
}

//���ݵ�ǰ�Ľ������ɶ�����ʾ��
bool GoldCounterLayer::init(int number)
{	
	//��ʼ��ʧ��
	if(!CCNode::init())
	{
		return false;
	}
    CCTexture2D * texture = CCTextureCache::sharedTextureCache()->addImage("ui_text_01-ipadhd.png");
	CCSize textureSize = texture->getContentSize();
    
    for(int i = 0 ;i < NUM_COUNTER;i++){
        CCArray* array = CCArray::createWithCapacity(10);
		float digitSize = textureSize.width/ 10;
        for(int j = 0;j < 10;j++){
            int x = digitSize * j;
			CCSprite *sprite = CCSprite::createWithTexture(texture,CCRect(x,0,digitSize,textureSize.height));
			array->addObject(sprite);
        }
        Counter* counter = Counter::create(array);
		addChild(counter,0,i);
        counter->setPosition(i * digitSize,0);
    }
    setNumber(number);
    return true;
}

//��number���õ�_number�С�
void GoldCounterLayer::setNumber(int number, int ceiling /*=999999*/)
{
	//ȷ��number��ֵҪ����0����С��ceiling��
    if (number > ceiling)
    {
		number = ceiling;
    }
	if (number < 0)
	{
		number = 0;
	}
	for (int i = NUM_COUNTER -1; i >=0; i--)
	{
		Counter * counter = (Counter *)getChildByTag(i);
		counter->setDigit((number % 10));
		number/=10;
	}
}