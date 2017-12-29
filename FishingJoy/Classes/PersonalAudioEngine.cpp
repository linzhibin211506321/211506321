//��ɱ������ֺͰ�ť�������Ч��Դ��Ԥ���أ����ṩ������Ч����ؽӿ�
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

//���ڱ������ֵ�������С
void PersonalAudioEngine::setBackgroundMusicVolume(float volume)
{
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volume);
	FishingJoyData::sharedFishingJoyData()->setMusicVolume(volume);
}
//������Ч�Ĵ�С
void PersonalAudioEngine::setEffectsVolume(float volume)
{
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(volume);
	FishingJoyData::sharedFishingJoyData()->setSoundVolume(volume);
}

void PersonalAudioEngine::purge()
{

}
