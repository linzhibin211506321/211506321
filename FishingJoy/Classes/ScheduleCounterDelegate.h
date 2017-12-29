//倒计时处理器接口，提供一个纯虚函数和虚函数由派生类实现。
#pragma once
class ScheduleCounterDelegate
{
public:
	virtual void scheduleTimeUp() = 0;
	virtual void setScheduleNumber(int number){
		return;
	}
};
