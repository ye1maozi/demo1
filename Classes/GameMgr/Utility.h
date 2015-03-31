#pragma once
#include "cocos2d.h"
#include "Utility/bitArray.h"
class BasicChar;
USING_NS_CC;
class Utility
{
public:

	
	static Utility* getInstance();

	bool SaveGame();//todo 本地 /网络 数据库 /xml 接口实现
	//loadGame();

	
	bool IsPlayMusic();
	bool IsPlayAudio();

	void setMusic(bool v);
	void setAudio(bool v);

	void SavePlayInfo();
	Vector<BasicChar*> getPlayInfo();
private:
	static Utility* _instance;

	 bool init();



};

