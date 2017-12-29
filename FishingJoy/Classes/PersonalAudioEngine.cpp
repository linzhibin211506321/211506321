//完成背景音乐和按钮等相关音效资源的预加载，并提供调节音效的相关接口
#include "PersonalAudioEngine.h"
#include "FishingJoyData.h"

PersonalAudioEngine::PersonalAudioEngine(void)
{
}


PersonalAudioEngine::~PersonalAudioEngine(void)
{
}

static PersonalAudioEngine* _sharedEngine = NULL;

PersonalAudioEngine* PersonalAudioEngine::sharedEngine()
{
	if(_sharedEngine==NULL){
		_sharedEngine = new PersonalAudioEngine();
		_sharedEngine->init();
	}
	return _sharedEngine;
}

bool PersonalAudioEngine::init()
{
	this->preloadBackgroundMusic("music_1.mp3");
	this->preloadEffect("bgm_button.aif");
	this->preloadEffect("bgm_fire.aif");
	this->preloadEffect("bgm_net.mp3");

	this->setBackgroundMusicVolume(FishingJoyData::sharedFishingJoyData()->getMusicVolume());
	this->setEffectsVolume(FishingJoyData::sharedFishingJoyData()->getSoundVolume());

	return true;
}

//调节背景音乐的声音大小
void PersonalAudioEngine::setBackgroundMusicVolume(float volume)
{
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volume);
	FishingJoyData::sharedFishingJoyData()->setMusicVolume(volume);
}
//调节音效的大小
void PersonalAudioEngine::setEffectsVolume(float volume)
{
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(volume);
	FishingJoyData::sharedFishingJoyData()->setSoundVolume(volume);
}

void PersonalAudioEngine::purge()
{

}
