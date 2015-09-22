#pragma once

class CTimer
{
public:
	static CTimer * GetInstance(void);

	unsigned long	GetTimeMSec(void);
	unsigned long	GetTime(void);
	float			GetFps(void);

	void Initialize(void);
	void Update(void);

protected:
	CTimer(void);
	~CTimer(void);
private:
	unsigned long currentTime;
	unsigned long lastTime;

	static CTimer * singleton;	
};





