#include "FishLayer.h"


FishLayer::FishLayer(void)
{
}

FishLayer::~FishLayer(void)
{
}

bool FishLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	return true;
}