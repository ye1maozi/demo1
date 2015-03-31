#include "Utility.h"
#include "dataMgr.h"
#include "character/BasicChar.h"
#include <iostream>
#include "Utility/LSLog.h"
USING_NS_CC;

Utility* Utility::_instance = NULL;

Utility* Utility::getInstance()
{
	if(NULL == _instance)
	{
		_instance = new Utility();
		_instance->init();
	}
	return _instance;
}
bool Utility::init()
{
	return true;
}

bool Utility::IsPlayMusic()
{
	return CCUserDefault::getInstance()->getBoolForKey("music",true);
}
bool Utility::IsPlayAudio()
{
	return CCUserDefault::getInstance()->getBoolForKey("audio",true);
}
void Utility::setMusic(bool v)
{
	CCUserDefault::getInstance()->setBoolForKey("music",v);
	CCUserDefault::getInstance()->flush();
}
void Utility::setAudio(bool v)
{
	CCUserDefault::getInstance()->setBoolForKey("music",v);
	CCUserDefault::getInstance()->flush();
}
void Utility::SavePlayInfo()
{
	LSLog::info("SavePlayInfo");
	Vector<BasicChar*> plist = dataMgr::getInstance()->getCurList();
	bitArray* bitarr =new bitArray();
	int n1 = plist.size();
	bitarr->init(n1*100);

	bitarr->write_int(n1,4);
	for(BasicChar* cha :plist)
	{
		int hp  = cha->getHP();
		bitarr->write_int(hp,8);
		int mp = cha->getMP();
		bitarr->write_int(mp,8);
		std::string s = cha->getName();
		bitarr->write_str(s);
	}
	Data* data = new Data();

	data->copy((unsigned char*)(bitarr->getByteArray()),bitarr->getSize());
	CCUserDefault::getInstance()->setDataForKey("data",*data);
	CCUserDefault::getInstance()->flush();
	delete data;
	delete bitarr;
	LSLog::info("SavePlayInfo1");
//	bitArray readbuff = bitarr;
//	int n = readbuff.read_int(4);
//	for(int i=0;i<n;++i)
//	{
//		int rhp =readbuff.read_int(8);
//		int rmp =readbuff.read_int(8);
//		std::string sss = readbuff.read_str();
//	}
}
