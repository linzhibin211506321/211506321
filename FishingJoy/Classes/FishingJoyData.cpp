#include "FishingJoyData.h"

USING_NS_CC;

#define IS_BEGINER "_isBeginer"//是否为初学者
#define GOLD "_gold" //金币的数量
#define SOUND "_soundVolume" //音效的大小
#define MUSIC "_musicVolume" //背景音乐的大小


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

//利用CCUserDefault来操作存储在磁盘文件中的数据。
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

//将数据重设为初始化时的数据。
void FishingJoyData::reset()
{
	this -> setMusicVolume(0.8f);
	this -> setSoundVolume(0.8f);
	this -> setGold(200);
	this -> setIsBeginer(false);
}

//将当前动态数据的值保存到xml文件中。
void FishingJoyData::flush()
{
	CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();
	
	userDefault -> setBoolForKey(IS_BEGINER, _isBeginer);
	userDefault -> setIntegerForKey(GOLD, _gold);
	userDefault -> getFloatForKey(MUSIC, _musicVolume);
	userDefault -> getFloatForKey(SOUND, _soundVolume);

	userDefault -> flush();
}

//更新金币数值。
void FishingJoyData::alterGold(int golds)
{
	int num = getGold();
	num += golds;
	this->setGold(num);
	flush();
}
//释放该单件对象。
void FishingJoyData::purge()
{
	CC_SAFE_RELEASE_NULL(_sharedFishingJoyData);
}
