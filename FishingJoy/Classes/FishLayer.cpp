#include "FishLayer.h"
#include <ctime>

//#define FISH_MAX_COUNT 50

enum{
	k_Direction_Left = 0,
	k_Direction_Right,
	k_Direction_Count
};


FishLayer::FishLayer(void)
{
}

bool FishLayer::init()
{
	do 
	{
		if (!CCLayer::init())
		{
			return false;
		}
		_fishes = CCArray::createWithCapacity(FISH_MAX_COUNT);
		CC_SAFE_RETAIN(_fishes);
		for(int i = 0; i < FISH_MAX_COUNT; i++){
			int type = CCRANDOM_0_1() * k_Fish_Type_Count - 1;
			Fish* fish = Fish::create((FishType)type);
			_fishes->addObject(fish);
		}
		srand((unsigned)time(0));
		this->schedule(schedule_selector(FishLayer::addFish), 2.0f);
		return true;
	} while (0);
	return false;
}

//����������ѡ�������������������ڷŵ������е�ĳ��λ��
void FishLayer::addFish(float delta)
{
		int CountToAdd = CCRANDOM_0_1() * 8 + 1;//��ʾ�˴�Ҫ���ɵ��������
		int count = 0;
		CCObject* obj;

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();//��ô��ڴ�С�����ұ�����winSize��
		CCARRAY_FOREACH(_fishes, obj)
		{
			Fish* fish = (Fish*)obj;
			if(fish->isRunning())
			{
				continue;
			}
			resetFish(fish);
			count++;
			if(count == CountToAdd )
			{
				break;
			}
		}
}

//�����λ�ý����������ã��������ƶ���Ŀ��λ�á�
void FishLayer::resetFish(Fish* fish)
{
	int direction = CCRANDOM_0_1() * k_Direction_Count;
	float startX=0, startY=0, endX=0, endY=0;//��ʼ�ͽ���ʱ�������
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();//��ô��ڴ�С�����ұ�����winSize��
	CCSize fishSize = fish->getSize();
	if (direction == k_Direction_Left)
	{
		startX = winSize.width + fishSize.width ;
		fish->setRotation(0);
		endY = -fishSize.width/2;
	}
	else
	{
		startX = -fishSize.width ;
		endX = winSize.width + fishSize.width / 2;
		fish->setRotation(180);
	}
	endY = CCRANDOM_0_1() * (winSize.height - fishSize.height) + fishSize.height / 2;
	startY = CCRANDOM_0_1() * (winSize.height - fishSize.height) + fishSize.height;
	addChild(fish);
	fish->setPosition(ccp(startX,startY));
	fish->moveTo(ccp(endX,endY));
}

FishLayer::~FishLayer(void)
{
}


