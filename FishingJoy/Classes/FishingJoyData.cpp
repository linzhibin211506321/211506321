#include "FishingJoyData.h"

USING_NS_CC;

#define IS_BEGINER "_isBeginer"//�Ƿ�Ϊ��ѧ��
#define GOLD "_gold" //��ҵ�����
#define SOUND "_soundVolume" //��Ч�Ĵ�С
#define MUSIC "_musicVolume" //�������ֵĴ�С


static FishingJoyData* _sharedFishingJoyData = NULL;

FishingJoyData::FishingJoyData(void)
{
}


FishingJoyData::~FishingJoyData(void)
{
	this->flush();
}

FishingJoyData* FishingJoyData::sharedFishingJoyData()
{
	if(NULL == _sharedFishingJoyData)
	{
		_sharedFishingJoyData = new FishingJoyData();
		_sharedFishingJoyData -> init();
	}
	return _sharedFishingJoyData;
}

//����CCUserDefault�������洢�ڴ����ļ��е����ݡ�
bool FishingJoyData::init()
{
	_isBeginer = CCUserDefault::sharedUserDefault()->getBoolForKey(IS_BEGINER, true);
	if (_isBeginer)
	{
		this -> reset();
		this -> flush();
		this -> setIsBeginer(false);
	}
	else
	{
		CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();
		this -> setGold(userDefault -> getIntegerForKey(GOLD));
		this -> setMusicVolume(userDefault -> getFloatForKey(MUSIC));
		this -> setSoundVolume(userDefault -> getFloatForKey(SOUND));
	}
	return true;
}

//����������Ϊ��ʼ��ʱ�����ݡ�
void FishingJoyData::reset()
{
	this -> setMusicVolume(0.8f);
	this -> setSoundVolume(0.8f);
	this -> setGold(200);
	this -> setIsBeginer(false);
}

//����ǰ��̬���ݵ�ֵ���浽xml�ļ��С�
void FishingJoyData::flush()
{
	CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();
	
	userDefault -> setBoolForKey(IS_BEGINER, _isBeginer);
	userDefault -> setIntegerForKey(GOLD, _gold);
	userDefault -> getFloatForKey(MUSIC, _musicVolume);
	userDefault -> getFloatForKey(SOUND, _soundVolume);

	userDefault -> flush();
}

//���½����ֵ��
void FishingJoyData::alterGold(int golds)
{
	int num = getGold();
	num += golds;
	this->setGold(num);
	flush();
}
//�ͷŸõ�������
void FishingJoyData::purge()
{
	CC_SAFE_RELEASE_NULL(_sharedFishingJoyData);
}
