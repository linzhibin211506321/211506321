#include "FishJoyData.h"
#include "StaticData.h"
USING_NS_CC;
#define IS_BEGINER "isBeginer"
#define MUSIC		"music"
#define SOUND		"sound"
#define GOLD		"gold"

static FishJoyData* _sharedFishJoyData = NULL;

FishJoyData* FishJoyData::sharedFishJoyData()
{
    if(_sharedFishJoyData == NULL){
        _sharedFishJoyData = new FishJoyData();
        _sharedFishJoyData->init();
    }
    return _sharedFishJoyData;
}

void FishJoyData::destoryIntance(){
	CC_SAFE_DELETE(_sharedFishJoyData);
}

FishJoyData::FishJoyData()
{
    
}
FishJoyData::~FishJoyData()
{
    this->flush();
}
bool FishJoyData::init()
{
    _isBeginner = CCUserDefault::sharedUserDefault()->getBoolForKey(IS_BEGINER,true);
    if(_isBeginner == true){
        this->reset();
        this->flush();
    }else{
      CCUserDefault *userDefault = CCUserDefault::sharedUserDefault();
	  this->setGold(userDefault->getIntegerForKey(GOLD));
	  this->setisMusic(userDefault->getBoolForKey(MUSIC));
	  this->setisSound(userDefault->getBoolForKey(SOUND));

    }
    return true;
}
void FishJoyData::reset()
{
    this->setGold(700);
    this->setIsBeginner(true);
    this->setisMusic(true);
    this->setisSound(true);
    this->flush();
}
void FishJoyData::alterGold(int golds)
{
	int num = getGold();
	num+=golds;
	setGold(num);
	flush();
}
void FishJoyData::flush()
{
	CCUserDefault *userDefault = CCUserDefault::sharedUserDefault();
	userDefault->setBoolForKey(IS_BEGINER,_isBeginner);
	userDefault->setIntegerForKey(GOLD,_gold);
	userDefault->setBoolForKey(MUSIC,_isMusic);
	userDefault->setBoolForKey(SOUND,_isSound);
	userDefault->flush();
}
