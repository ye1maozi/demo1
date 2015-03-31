#include "dataMgr.h"
#include "character/Player/player.h"
#include "character/Player/AIplayer.h"
#include "atkMgr.h"
#include "Utility/LSLog.h"
#include "Utility/bitArray.h"
dataMgr* dataMgr::_instance = NULL;
dataMgr* dataMgr::getInstance()
{
	if(NULL == _instance)
	{
		_instance = new dataMgr();
		_instance->init();
	}
	return _instance;
}
bool dataMgr::init()
{
	selfPlayer = NULL;
	isContinue = false;
	return true;
}
BasicChar* dataMgr::getCharByName( std::string name)
{
	for(BasicChar* cha :curPlayerList)
	{
		if(name == cha->getName())
		{
			return cha;
		}
	}
	return NULL;
}

void dataMgr::initPlayer()
{
	curPlayerList.clear();

	if(selfPlayer != NULL)
		CC_SAFE_RELEASE_NULL(selfPlayer);


	selfPlayer = player::create("public/player.png");
	AIplayer* ai1 = AIplayer::create("public/ai.png");
	if(isContinue )
	{
		isContinue = false;
		LSLog::info("asdad");
		Data data = CCUserDefault::getInstance()->getDataForKey("data");
		if(!data.isNull())
		{
			LSLog::info("in");
			bitArray* readbuff = new bitArray(data.getBytes(),data.getSize()) ;
			LSLog::info("copy end");
			int n = readbuff->read_int(4);
			LSLog::info("n :%d",n);
			for(int i=0;i<n;++i)
			{
				int hp =readbuff->read_int(8);
				int mp =readbuff->read_int(8);
				std::string sss = readbuff->read_str();
				LSLog::info("hp : %d",hp);
				LSLog::info("mp : %d",mp);
				LSLog::info("str: %s",sss.c_str());

				// todo ÐÞ¸Ä
				if(selfPlayer->getName() == sss)
				{
					selfPlayer->setMP(mp);
					selfPlayer->setHP(hp);
				}
				else
				{
					ai1->setMP(mp);
					ai1->setHP(hp);
				}
			}
			LSLog::info("bbbbbbbbbbbbbb");
			delete readbuff;
			LSLog::info("aaaaaa");
		}
	}
	else
	{

	}
	curPlayerList.pushBack(selfPlayer);
	curPlayerList.pushBack(ai1);
	auto scene = Director::getInstance()->getRunningScene();
	scene->addChild(selfPlayer);
	selfPlayer->setPosition(500,400);
	scene->addChild(ai1);
	ai1->setPosition(500,1600);

}

Vector<BasicChar*> dataMgr::getAIList()
{
	return curPlayerList;
}
void dataMgr::setMpByName(const std::string name,int mp)
{
	BasicChar* cha = getCharByName(name);
	cha->setMP(mp);
}
void dataMgr::setHpByName(const std::string name,int hp)
{
	BasicChar* cha = getCharByName(name);
	cha->setHP(hp);
}
void dataMgr::clearPlayer()
{
	LSLog::info("clearplayer");
	curPlayerList.clear();
	atkMgr::getInstance()->clearAll();
}
